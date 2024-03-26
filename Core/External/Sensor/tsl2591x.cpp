#include "tsl2591x.h"

void TSL2591X::init() {
    enable();

    set_gain(MEDIUM_AGAIN);
    set_integral_time(ATIME_200MS);
    write_byte(PERSIST_REGISTER, 0x01);

    disable();

    initialized = true;
}

bool TSL2591X::is_available() {
    return HAL_I2C_IsDeviceReady(&hi2c1, TSL2591X_ADDRESS, 1u, 10u) == HAL_OK;
}

bool TSL2591X::is_configured() {
    return initialized;
}

bool TSL2591X::get_device_id() {
    return read_byte(WHO_AM_I);
};

void TSL2591X::enable() {
    write_byte(ENABLE_REGISTER, ENABLE_AIEN | ENABLE_POWERON | ENABLE_AEN | ENABLE_NPIEN);
}

void TSL2591X::disable() {
    write_byte(ENABLE_REGISTER, ENABLE_POWEROFF);
}

void TSL2591X::reset() {
    write_byte(CONTROL_REGISTER, SRESET);
}

uint16_t TSL2591X::read_lux() {
    enable();

    uint8_t externalIntegralTime = get_integral_time();

    for (uint8_t i = 0; i < externalIntegralTime + 2; i++) {
        HAL_Delay(100);
    }

    uint16_t channel0 = read_channel0();
    uint16_t channel1 = read_channel1();
    disable();

    enable();
    write_byte(0xE7, 0x13);
    disable();

    uint16_t maxCounts;

    if (externalIntegralTime == ATIME_100MS) {
        maxCounts = MAX_COUNT_100MS;
    } else {
        maxCounts = MAX_COUNT;
    }

    uint8_t externalGain;

    if (channel0 >= maxCounts || channel1 >= maxCounts) {
        externalGain = get_gain();

        if (externalGain == LOW_AGAIN) {
            return 0;
        }

        externalGain = ((externalGain >> 4) - 1) << 4;

        set_gain(externalGain);

        channel0 = 0;
        channel1 = 0;
        while (channel0 <= 0 || channel1 <= 0) {
            channel0 = read_channel0();
            channel1 = read_channel1();
        }

        HAL_Delay(100);
    }

    double gain = 1.0;

    externalGain = get_gain();

    if (externalGain == MEDIUM_AGAIN) {
        gain = 25.0;
    } else if (externalGain == HIGH_AGAIN) {
        gain = 428.0;
    } else if (externalGain == MAX_AGAIN) {
        gain = 9876.0;
    }

    uint16_t lux1 = (int) ((channel0 - (2 * channel1)) / (((100 * externalIntegralTime + 100) * gain) / LUX_DF));

    if (lux1 <= 0) {
        return 0;
    }

    return lux1;
}

uint32_t TSL2591X::read_full() {
    uint32_t result;

    enable();

    result = (read_channel1() << 16) | read_channel0();

    disable();

    return result;
}

uint16_t TSL2591X::read_infrared() {
    uint16_t result;

    enable();

    result = read_channel0();

    disable();

    return result;
}

uint32_t TSL2591X::read_visible() {
    enable();

    uint16_t channel1 = read_channel1();
    uint16_t channel0 = read_channel0();

    disable();

    return ((channel1 << 16) | channel0) - channel1;
}

void TSL2591X::invoke_raw_interrupt_threshold(uint16_t low, uint16_t high) {
    enable();

    write_byte(AILTL_REGISTER, low & 0xFF);
    write_byte(AILTH_REGISTER, low >> 8);

    write_byte(AIHTL_REGISTER, high & 0xFF);
    write_byte(AIHTH_REGISTER, high >> 8);

    write_byte(NPAILTL_REGISTER, 0);
    write_byte(NPAILTH_REGISTER, 0);

    write_byte(NPAIHTL_REGISTER, 0xff);
    write_byte(NPAIHTH_REGISTER, 0xff);

    disable();
}

void TSL2591X::invoke_lux_interrupt(uint16_t low, uint16_t high) {
    double gain = 1.0;

    uint8_t externalGain = get_gain();

    if (externalGain == MEDIUM_AGAIN) {
        gain = 25.0;
    } else if (externalGain == HIGH_AGAIN) {
        gain = 428.0;
    } else if (externalGain == MAX_AGAIN) {
        gain = 9876.0;
    }

    uint8_t externalIntegralTime = get_integral_time();

    double cpl = ((100 * externalIntegralTime + 100) * gain) / LUX_DF;

    uint16_t channel1 = read_channel1();

    uint16_t highLux = (int) (cpl * high) + 2 * channel1 - 1;
    uint16_t lowLux = (int) (cpl * low) + 2 * channel1 + 1;

    enable();

    write_byte(AILTL_REGISTER, lowLux & 0xFF);
    write_byte(AILTH_REGISTER, lowLux >> 8);

    write_byte(AIHTL_REGISTER, highLux & 0xFF);
    write_byte(AIHTH_REGISTER, highLux >> 8);

    write_byte(NPAILTL_REGISTER, 0);
    write_byte(NPAILTH_REGISTER, 0);

    write_byte(NPAIHTL_REGISTER, 0xff);
    write_byte(NPAIHTH_REGISTER, 0xff);

    disable();
}

uint16_t TSL2591X::read_channel0() {
    return read_word(CHAN0_LOW);
}

uint16_t TSL2591X::read_channel1() {
    return read_word(CHAN1_LOW);
}

uint8_t TSL2591X::get_integral_time() {
    return read_byte(CONTROL_REGISTER) & 0x07;
}

void TSL2591X::set_integral_time(uint8_t src)  {
    if (src < 0x06) {
        uint8_t control = read_byte(CONTROL_REGISTER);
        control &= 0xf8;
        control |= src;
        write_byte(CONTROL_REGISTER, control);
    }
}

uint8_t TSL2591X::get_gain() {
    return read_byte(CONTROL_REGISTER) & 0x30;
}

void TSL2591X::set_gain(uint8_t src) {
    if (src == LOW_AGAIN || src == MEDIUM_AGAIN || src == HIGH_AGAIN || src == MAX_AGAIN) {
        uint8_t control = read_byte(CONTROL_REGISTER);
        control &= 0xCf;
        control |= src;
        write_byte(CONTROL_REGISTER, control);
    }
}

uint8_t TSL2591X::read_byte(uint8_t src) {
    return read_byte_i2c(src | COMMAND_BIT);
}

uint16_t TSL2591X::read_word(uint8_t src) {
    return read_word_i2c(src | COMMAND_BIT);
}

void TSL2591X::write_byte(uint8_t src, uint8_t value) {
    write_byte_i2c(src | COMMAND_BIT, value);
}

void TSL2591X::write_byte_i2c(uint8_t command, uint8_t value) {
    uint8_t buffer[1] = {value};

    HAL_I2C_Mem_Write(
            &hi2c1, TSL2591X_ADDRESS, command, I2C_MEMADD_SIZE_8BIT, buffer, 1, I2C_TIMEOUT);
}

int TSL2591X::read_byte_i2c(uint8_t command) {
    uint8_t buffer[1] = {0};

    HAL_I2C_Mem_Read(
            &hi2c1, TSL2591X_ADDRESS + 1, command, I2C_MEMADD_SIZE_8BIT, buffer, 1, I2C_TIMEOUT);

    return buffer[0];
}

int TSL2591X::read_word_i2c(uint8_t command) {
    uint8_t buffer[2] = {0, 0};

    HAL_I2C_Mem_Read(&hi2c1, TSL2591X_ADDRESS + 1, command, I2C_MEMADD_SIZE_8BIT, buffer, 2, I2C_TIMEOUT);

    return ((buffer[1] << 8) | (buffer[0] & 0xff));
}

