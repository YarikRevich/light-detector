# CLI

[![Build](https://github.com/YarikRevich/ResourceTracker/actions/workflows/build.yml/badge.svg)](https://github.com/YarikRevich/ResourceTracker/actions/workflows/build.yml)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![MacOS](https://img.shields.io/badge/MacOS-8773f5?style=for-the-badge&logo=macos&logoColor=black)
[![StandWithUkraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/badges/StandWithUkraine.svg)](https://github.com/vshymanskyy/StandWithUkraine/blob/main/docs/README.md)

## General Information

Allows to perform operations with serial connected devices.

Includes following features:
* Retrieve latest sensor data(**raw**, **full**, **infrared**, **visible**)
* Retrieve meta information from the internal board state
* Modify settings for the light sensor.

All the operations are perform with the usage of **ProtocolBuffers**.

## Setup
 
First of all connect your board with device installed to serial port. Your board needs to have
already installed software build, which allows communication with TSL2591X device.

![](https://www.waveshare.com/w/A6Y79bcq/Kdy80nYY.php?f=TSL25911-Arduino-WS.jpg&width=900)

All setup related operations are processed via **Makefile** placed in the root directory.

In order to build the project it's required to execute the following command. It generates local **Python** project.
```shell
make install
```

# Use cases

The example below shows how to retrieve a set of all available devices, which can be used to perform other operations.
```shell
$ light-detector-cli get_available_devices

[
  instance(AvailableDevicesDto):
    description: 'STM32 STLink',
    location: '/dev/cu.usbmodem1203',
    manufacturer: 'STMicroelectronics'
]
```

The examples below show all the possible ways to retrieve metadata information from the board. Baud rate is important to be the exact-supported value,
otherwise requests will be ignored.

The next example shows how to the value of gain metadata information from the board.
```shell
$ light-detector-cli get_info --device="/dev/cu.usbmodem1203" --baud_rate="9600" --type="gain"

instance(RetrievedInfoDto):
  data_type: <InfoTypeCompound.GAIN: 'Gain'>,
  device_id: 1,
  nonce: 4,
  value: 16
```

Available **gain** values:
* 0 - low
* 16 - medium
* 32 - high
* 48 - max

The next example shows how to the value of integral time metadata information from the board. 
```shell
$ light-detector-cli get_info --device="/dev/cu.usbmodem1203" --baud_rate="9600" --type="integral_time"

instance(RetrievedInfoDto):
  data_type: <InfoTypeCompound.INTEGRAL_TIME: 'IntegralTime'>,
  device_id: 1,
  nonce: 5,
  value: 1
```

Available **integral time** values:
* 0 - 100ms
* 1 - 200ms
* 2 - 300ms
* 3 - 400ms
* 4 - 500ms
* 5 - 600ms
