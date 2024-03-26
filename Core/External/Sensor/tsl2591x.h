#ifndef LIGHT_DETECTOR_SENSOR_H
#define LIGHT_DETECTOR_SENSOR_H

#include "i2c.h"
#include <stdint.h>
#include <stdio.h>

#define TSL2591X_ADDRESS       (0x29<<1)

#define WHO_AM_I (0x12)

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

#define I2C_TIMEOUT (0x20)

/**
 * Represents driver implementation for "Waveshare" TSL2591X light sensor.
 */
class TSL2591X {
public:
    /**
     * Initializes light sensor configuration.
     */
    static void init();

    /**
     * Checks if the device is available and thus can be configured.
     *
     * @return result of the check.
     */
    static bool is_available();

    /**
     * Checks if the device has already been configured.
     *
     * @return result of the check.
     */
    static bool is_configured();

    /**
     * Retrieves device id of the sensor.
     *
     * @return read device id.
     */
    static bool get_device_id();

    /**
     * Enables the sensor.
     */
    static void enable();

    /**
     * Disables the sensor.
     */
    static void disable();

    /**
     * Resets light sensor to the default state.
     */
    static void reset();

    /**
     * Reads raw data in LUX format.
     *
     * @return read raw data in LUX format.
     */
    static uint16_t read_lux();

    /**
     * Reads full data from the sensor.
     *
     * @return read full data.
     */
    static uint32_t read_full();

    /**
     * Reads infrared data from the sensor.
     *
     * @return read infrared data.
     */
    static uint16_t  read_infrared();

    /**
     * Reads visible data from the sensor.
     *
     * @return read visible data.
     */
    static uint32_t read_visible();

    /**
     * Sets raw interruption threshold.
     *
     * @param low - given low state.
     * @param high - given high state.
     */
    static void invoke_raw_interrupt_threshold(uint16_t low, uint16_t high);

    /**
     * Sets LUX interruption configurations.
     *
     * @param low - given low state.
     * @param high - given high state.
     */
    static void invoke_lux_interrupt(uint16_t low, uint16_t high);
private:
    /**
     * Indicated that the device has already been initialized.
     */
    static bool initialized;

    /**
    * Reads value from the zero channel.
    *
    * @return read value.
    */
    static uint16_t read_channel0();

    /**
     * Reads value from the first channel.
     *
     * @return read value.
     */
    static uint16_t read_channel1();

    /**
     * Retrieves integral time option from the sensor.
     *
     * @return read value.
     */
    static uint8_t get_integral_time();

    /**
     * Sets integral time option to the sensor.
     *
     * @param src - given value to be set.
     */
    static void set_integral_time(uint8_t src);

    /**
     * Retrieves the value of gain option from the sensor.
     *
     * @return retrieved value.
     */
    static uint8_t get_gain();

    /**
     * Sets the value of gain option to the sensor.
     *
     * @param src - given value to be set.
     */
    static void set_gain(uint8_t src);

    /**
     * Reads combined command by bytes using I2C bone.
     *
     * @param src - given command to be read.
     * @return read value.
     */
    static uint8_t read_byte(uint8_t src);

    /**
     * Reads combined command by word using I2C bone.
     *
     * @param src - given command to be read.
     * @return read value.
     */
    static uint16_t read_word(uint8_t src);

    /**
     * Writes combined command by bytes via I2C bone.
     *
     * @param command - given command to be written.
     * @param value - given value to be written to the given command.
     */
    static void write_byte(uint8_t src, uint8_t value);

    /**
     * Writes raw byte via I2C bone.
     *
     * @param command - given command to be written.
     * @param value - given value to be written to the given command.
     */
    static void write_byte_i2c(uint8_t command, uint8_t value);

    /**
     * Reads raw byte via I2C bone.
     *
     * @param command - given command to be read.
     * @return read byte.
     */
    static int read_byte_i2c(uint8_t command);

    /**
     * Reads raw word via I2C bone.
     *
     * @param command - given command to be read.
     * @return read word.
     */
    static int read_word_i2c(uint8_t command);
};

#endif // LIGHT_DETECTOR_SENSOR_H
