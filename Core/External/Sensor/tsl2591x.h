#ifndef LIGHT_DETECTOR_SENSOR_H
#define LIGHT_DETECTOR_SENSOR_H

#include "i2c.h"
#include <stdint.h>
#include <stdio.h>

#define TSL2591X_ADDRESS       (0x29<<1)

#define COMMAND_BIT           (0xA0)

#define ENABLE_REGISTER       (0x00)
#define ENABLE_POWERON        (0x01)
#define ENABLE_POWEROFF       (0x00)
#define ENABLE_AEN            (0x02)
#define ENABLE_AIEN           (0x10)
#define ENABLE_NPIEN          (0x80)

#define CONTROL_REGISTER      (0x01)
#define SRESET                (0x80)

#define LOW_AGAIN             (0X00)
#define MEDIUM_AGAIN          (0X10)
#define HIGH_AGAIN            (0X20)
#define MAX_AGAIN             (0x30)

#define ATIME_100MS           (0x00)
#define ATIME_200MS           (0x01)
#define ATIME_300MS           (0x02)
#define ATIME_400MS           (0x03)
#define ATIME_500MS           (0x04)
#define ATIME_600MS           (0x05)

#define AILTL_REGISTER        (0x04)
#define AILTH_REGISTER        (0x05)
#define AIHTL_REGISTER        (0x06)
#define AIHTH_REGISTER        (0x07)
#define NPAILTL_REGISTER      (0x08)
#define NPAILTH_REGISTER      (0x09)
#define NPAIHTL_REGISTER      (0x0A)
#define NPAIHTH_REGISTER      (0x0B)

#define PERSIST_REGISTER      (0x0C)

#define CHAN0_LOW             (0x14)
#define CHAN0_HIGH            (0x15)
#define CHAN1_LOW             (0x16)
#define CHAN1_HIGH            (0x14)

#define LUX_DF                (762.0)

#define MAX_COUNT_100MS       (36863)
#define MAX_COUNT             (65535)

void I2C_WriteByte(uint8_t Cmd, uint8_t value);
int I2C_ReadByte(uint8_t Cmd);
int I2C_ReadWord(uint8_t Cmd);

void TSL2591X_Init();
void TSL2591X_Reset();

uint16_t TSL2591X_ReadLux();
void TSL2591X_SetRawInterruptThreshold(uint16_t low, uint16_t high);
void TSL2591X_SetLuxInterrupt(uint16_t low, uint16_t high);
uint32_t TSL2591X_ReadFull();
uint16_t TSL2591X_ReadInfrared();
uint32_t TSL2591X_ReadVisible();
#endif // LIGHT_DETECTOR_SENSOR_H
