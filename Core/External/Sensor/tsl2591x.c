#include "tsl2591x.h"

void I2C_WriteByte(uint8_t command, uint8_t value) {
    uint8_t buffer[1] = {value};

    HAL_I2C_Mem_Write(
            &hi2c1, TSL2591X_ADDRESS, command, I2C_MEMADD_SIZE_8BIT, buffer, 1, I2C_TIMEOUT);
}

int I2C_ReadByte(uint8_t command) {
    uint8_t buffer[1] = {0};

    HAL_I2C_Mem_Read(
            &hi2c1, TSL2591X_ADDRESS+1, command, I2C_MEMADD_SIZE_8BIT, buffer, 1, I2C_TIMEOUT);

    return buffer[0];
}

int I2C_ReadWord(uint8_t command) {
    uint8_t buffer[2] = {0, 0};

    HAL_I2C_Mem_Read(&hi2c1, TSL2591X_ADDRESS+1, command, I2C_MEMADD_SIZE_8BIT, buffer, 2, I2C_TIMEOUT);

    return ((buffer[1] << 8) | (buffer[0] & 0xff));
}

static uint8_t TSL2591X_ReadByte(uint8_t src) {
    return I2C_ReadByte(src | COMMAND_BIT);
}

static uint16_t TSL2591X_ReadWord(uint8_t src) {
    return I2C_ReadWord(src | COMMAND_BIT);
}

static void TSL2591X_WriteByte(uint8_t src, uint8_t Value) {
    I2C_WriteByte(src | COMMAND_BIT, Value);
}

void TSL2591X_Enable() {
    TSL2591X_WriteByte(ENABLE_REGISTER, ENABLE_AIEN | ENABLE_POWERON | ENABLE_AEN | ENABLE_NPIEN);
}

void TSL2591X_Disable() {
    TSL2591X_WriteByte(ENABLE_REGISTER,ENABLE_POWEROFF);
}

void TSL2591X_Reset() {
    TSL2591X_WriteByte(CONTROL_REGISTER, SRESET);
}

uint8_t TSL2591X_GetGain(void) {
    uint8_t data;

    data = TSL2591X_ReadByte(CONTROL_REGISTER);

    return data & 0x30;
}


void TSL2591X_SetGain(uint8_t src) {
    if(src == LOW_AGAIN || src == MEDIUM_AGAIN || src == HIGH_AGAIN || src == MAX_AGAIN){
        uint8_t control = TSL2591X_ReadByte(CONTROL_REGISTER);
        control &= 0xCf;
        control |= src;
        TSL2591X_WriteByte(CONTROL_REGISTER, control);
    }
}

uint8_t TSL2591X_GetIntegralTime(){
    uint8_t control = TSL2591X_ReadByte(CONTROL_REGISTER);

    return control & 0x07;
}

void TSL2591X_SetIntegralTime(uint8_t src) {
    if(src < 0x06){
        uint8_t control = TSL2591X_ReadByte(CONTROL_REGISTER);
        control &= 0xf8;
        control |= src;
        TSL2591X_WriteByte(CONTROL_REGISTER, control);
    }
}

uint16_t TSL2591X_ReadChannel0() {
    return TSL2591X_ReadWord(CHAN0_LOW);
}

uint16_t TSL2591X_ReadChannel1() {
    return TSL2591X_ReadWord(CHAN1_LOW);
}

uint16_t TSL2591_ReadLux() {
    TSL2591X_Enable();

    uint8_t externalIntegralTime = TSL2591X_GetIntegralTime();

    for(uint8_t i = 0; i < externalIntegralTime + 2; i++){
        HAL_Delay(100);
    }

    uint16_t channel0 = TSL2591X_ReadChannel0();
    uint16_t channel1 = TSL2591X_ReadChannel1();
    TSL2591X_Disable();

    TSL2591X_Enable();
    TSL2591X_WriteByte(0xE7, 0x13);
    TSL2591X_Disable();

    uint16_t maxCounts;

    if(externalIntegralTime == ATIME_100MS){
        maxCounts = MAX_COUNT_100MS;
    }else{
        maxCounts = MAX_COUNT;
    }

    uint8_t externalGain;

    if (channel0 >= maxCounts || channel1 >= maxCounts){
            externalGain = TSL2591X_GetGain();

            if (externalGain == LOW_AGAIN) {
                return 0;
            }

            externalGain = ((externalGain >> 4) - 1) << 4;

            TSL2591X_SetGain(externalGain);

            channel0 = 0;
            channel1 = 0;
            while(channel0 <= 0 || channel1 <=0){
                channel0 = TSL2591X_ReadChannel0();
                channel1 = TSL2591X_ReadChannel1();
            }

            HAL_Delay(100);
    }

    double gain = 1.0;

    externalGain = TSL2591X_GetGain();

    if(externalGain == MEDIUM_AGAIN){
        gain = 25.0;
    }else if(externalGain == HIGH_AGAIN){
        gain = 428.0;
    }else if(externalGain == MAX_AGAIN){
        gain = 9876.0;
    }

    uint16_t lux1 = (int)((channel0 - (2 * channel1)) / (((100 * externalIntegralTime + 100) * gain) / LUX_DF));

    if (lux1 <= 0) {
        return 0;
    }

    return lux1;
}

void TSL2591X_SetRawInterruptThreshold(uint16_t low, uint16_t high) {
    TSL2591X_Enable();
    TSL2591X_WriteByte(AILTL_REGISTER, low & 0xFF);
    TSL2591X_WriteByte(AILTH_REGISTER, low >> 8);
    
    TSL2591X_WriteByte(AIHTL_REGISTER, high & 0xFF);
    TSL2591X_WriteByte(AIHTH_REGISTER, high >> 8);
    
    TSL2591X_WriteByte(NPAILTL_REGISTER, 0 );
    TSL2591X_WriteByte(NPAILTH_REGISTER, 0 );
    
    TSL2591X_WriteByte(NPAIHTL_REGISTER, 0xff );
    TSL2591X_WriteByte(NPAIHTH_REGISTER, 0xff );
    TSL2591X_Disable();
}

void TSL2591X_SetLuxInterrupt(uint16_t low, uint16_t high) {
    double gain = 1.0;

    uint8_t externalGain = TSL2591X_GetGain();

    if(externalGain == MEDIUM_AGAIN){
        gain = 25.0;
    }else if(externalGain == HIGH_AGAIN){
        gain = 428.0;
    }else if(externalGain == MAX_AGAIN){
        gain = 9876.0;
    }

    uint8_t externalIntegralTime = TSL2591X_GetIntegralTime();

    double cpl = ((100 * externalIntegralTime + 100) * gain) / LUX_DF;

    uint16_t channel1 = TSL2591X_ReadChannel1();

    uint16_t highLux = (int)(cpl * high) + 2 * channel1 - 1;
    uint16_t lowLux = (int)(cpl * low) + 2 * channel1 + 1;
		
    TSL2591X_Enable();
    TSL2591X_WriteByte(AILTL_REGISTER, lowLux & 0xFF);
    TSL2591X_WriteByte(AILTH_REGISTER, lowLux >> 8);
    
    TSL2591X_WriteByte(AIHTL_REGISTER, highLux & 0xFF);
    TSL2591X_WriteByte(AIHTH_REGISTER, highLux >> 8);
    
    TSL2591X_WriteByte(NPAILTL_REGISTER, 0 );
    TSL2591X_WriteByte(NPAILTH_REGISTER, 0 );
    
    TSL2591X_WriteByte(NPAIHTL_REGISTER, 0xff );
    TSL2591X_WriteByte(NPAIHTH_REGISTER, 0xff );
    TSL2591X_Disable();
}

uint32_t TSL2591X_ReadFull() {
    uint32_t result;

    TSL2591X_Enable();
    result = (TSL2591X_ReadChannel1()  << 16) | TSL2591X_ReadChannel0();
    TSL2591X_Disable();

    return result;
}

uint16_t TSL2591X_ReadInfrared() {
    uint16_t result;

    TSL2591X_Enable();
    result = TSL2591X_ReadChannel0();
    TSL2591X_Disable();

    return result;
}

uint32_t TSL2591X_ReadVisible() {
    TSL2591X_Enable();
    uint16_t channel1 = TSL2591X_ReadChannel1();
    uint16_t channel0 = TSL2591X_ReadChannel0();
    TSL2591X_Disable();

    return ((channel1 << 16) | channel0) - channel1;
}

void TSL2591X_Init() {
    TSL2591X_Enable();
    TSL2591X_SetGain(MEDIUM_AGAIN);
    TSL2591X_SetIntegralTime(ATIME_200MS);
    TSL2591X_WriteByte(PERSIST_REGISTER, 0x01);
    TSL2591X_Disable();
}