#include "tsl2591x.h"

// uint8_t TSL2591_Gain, TSL2591_Time;

void I2C_WriteByte(uint8_t Cmd, uint8_t value) {
    uint8_t buffer[1] = {value};

    HAL_I2C_Mem_Write(
            &hi2c1, TSL2591X_ADDRESS, Cmd, I2C_MEMADD_SIZE_8BIT, buffer, 1, 0x20);
}

int I2C_ReadByte(uint8_t Cmd) {
    uint8_t buffer[1] = {0};

    HAL_I2C_Mem_Read(
            &hi2c1, TSL2591X_ADDRESS+1, Cmd, I2C_MEMADD_SIZE_8BIT, buffer, 1, 0x20);

    return buffer[0];
}

int I2C_ReadWord(uint8_t Cmd) {
    uint8_t buffer[2] = {0, 0};

    HAL_I2C_Mem_Read(&hi2c1, TSL2591X_ADDRESS+1, Cmd, I2C_MEMADD_SIZE_8BIT, buffer, 2, 0x20);

    return ((buffer[1] << 8) | (buffer[0] & 0xff));
}

static uint8_t TSL2591X_ReadByte(uint8_t src)
{
    return I2C_ReadByte(src | COMMAND_BIT);
}

static uint16_t TSL2591X_ReadWord(uint8_t src)
{
    return I2C_ReadWord(src | COMMAND_BIT);
}

static void TSL2591X_WriteByte(uint8_t src, uint8_t Value)
{
    I2C_WriteByte(src | COMMAND_BIT, Value);
}

void TSL2591X_Enable()
{
    TSL2591X_WriteByte(ENABLE_REGISTER, \
    ENABLE_AIEN | ENABLE_POWERON | ENABLE_AEN | ENABLE_NPIEN);
}

void TSL2591X_Disable()
{
    TSL2591X_WriteByte(ENABLE_REGISTER, \
    ENABLE_POWEROFF);
}

void TSL2591X_Reset()
{
    TSL2591X_WriteByte(CONTROL_REGISTER, SRESET);
}

uint8_t TSL2591X_GetGain(void)
{
    uint8_t data;

    data = TSL2591X_ReadByte(CONTROL_REGISTER);
    TSL2591_Gain = data & 0x30;

    return data & 0x30;
}


void TSL2591X_SetGain(uint8_t src)
{
    if(src == LOW_AGAIN || src == MEDIUM_AGAIN || src == HIGH_AGAIN || src == MAX_AGAIN){
            uint8_t control = TSL2591X_ReadByte(CONTROL_REGISTER);
            control &= 0xCf;
            control |= src;
            TSL2591X_WriteByte(CONTROL_REGISTER, control);
            TSL2591_Gain = src;
    }
}

void TSL2591X_SetIntegralTime(uint8_t src)
{
    if(src < 0x06){
        uint8_t control = TSL2591X_ReadByte(CONTROL_REGISTER);
        control &= 0xf8;
        control |= src;
        TSL2591X_WriteByte(CONTROL_REGISTER, control);
        TSL2591_Time = src;
    }
}

uint16_t TSL2591X_ReadChannel0() {
    return TSL2591X_ReadWord(CHAN0_LOW);
}

uint16_t TSL2591X_ReadChannel1() {
    return TSL2591X_ReadWord(CHAN1_LOW);
}

uint16_t TSL2591_ReadLux() {
    uint16_t max_counts,channel_0,channel_1;

    TSL2591X_Enable();
    for(uint8_t i = 0; i < TSL2591_Time + 2; i++){
        HAL_Delay(100);
    }
    channel_0 = TSL2591X_ReadChannel0();
    channel_1 = TSL2591X_ReadChannel1();
    TSL2591X_Disable();

    TSL2591X_Enable();
    TSL2591X_WriteByte(0xE7, 0x13);
    TSL2591X_Disable();

    uint16_t atime = 100 * TSL2591_Time + 100;
    if(TSL2591_Time == ATIME_100MS){
        max_counts = MAX_COUNT_100MS;
    }else{
        max_counts = MAX_COUNT;
    }

    uint8_t gain_t;
    if (channel_0 >= max_counts || channel_1 >= max_counts){
            gain_t = TSL2591X_GetGain();
            if(gain_t != LOW_AGAIN){
                gain_t = ((gain_t >> 4) - 1) << 4;

                TSL2591X_SetGain(gain_t);

                channel_0 = 0;
                channel_1 = 0;
                while(channel_0 <= 0 || channel_1 <=0){
                    channel_0 = TSL2591X_ReadChannel0();
                    channel_1 = TSL2591X_ReadChannel1();
                }

                HAL_Delay(100);
            }else{
                return 0;
            }
    }
    double again;
    again = 1.0;
    if(TSL2591_Gain == MEDIUM_AGAIN){
        again = 25.0;
    }else if(TSL2591_Gain == HIGH_AGAIN){
        again = 428.0;
    }else if(TSL2591_Gain == MAX_AGAIN){
        again = 9876.0;
    }
    double Cpl;
    uint16_t lux1,lux2=0;
    
    Cpl = (atime * again) / LUX_DF;
    lux1 = (int)((channel_0 - (2 * channel_1)) / Cpl);

    if(lux1 > lux2){
        return lux1;
    } else {
        return lux2;
    }
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
    double again = 1.0;

    if(TSL2591_Gain == MEDIUM_AGAIN){
        again = 25.0;
    }else if(TSL2591_Gain == HIGH_AGAIN){
        again = 428.0;
    }else if(TSL2591_Gain == MAX_AGAIN){
        again = 9876.0;
    }

    double cpl = ((100 * TSL2591_Time + 100) * again) / LUX_DF;

    uint16_t channel1 = TSL2591X_ReadChannel1();

    uint16_t highLux = (int)(cpl * high)+ 2 * channel1 - 1;
    uint16_t lowLux = (int)(cpl * low)+ 2 * channel1 + 1;
		
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