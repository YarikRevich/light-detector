# light-detector

[![Build](https://github.com/YarikRevich/ResourceTracker/actions/workflows/build.yml/badge.svg)](https://github.com/YarikRevich/ResourceTracker/actions/workflows/build.yml)
![STM32](https://img.shields.io/badge/stm32-blue)
[![StandWithUkraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/badges/StandWithUkraine.svg)](https://github.com/vshymanskyy/StandWithUkraine/blob/main/docs/README.md)

## General Information

A driver-like application, which allows to communicate with **TSL2591X** light sensor, based on **STM32L476RG** embedded system.

Includes following features:
* Retrieve latest sensor data(**raw**, **full**, **infrared**, **visible**)
* Retrieve meta information from the internal board state
* Modify settings for the light sensor.

![](./Docs/Examples/high-level-design.png)

## Setup

All setup related operations are processed via **Makefile** placed in the root directory.

First of all connect your board to the serial port.

In order to build **IOC** project it's required to **CubeMX** to generate **ELF** upload it with the help of
**STM Programmer**.

> If **ProtocolBuffers** files need to be regenerated it's required to execute the following command:
```shell
make generate
```

## Scripts

### CLI

Detailed documentation can be found [here](./Scripts/cli/README.md)
