# CLI

[![Build](https://github.com/YarikRevich/ResourceTracker/actions/workflows/build.yml/badge.svg)](https://github.com/YarikRevich/ResourceTracker/actions/workflows/build.yml)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![MacOS](https://img.shields.io/badge/MacOS-8773f5?style=for-the-badge&logo=macos&logoColor=black)
[![StandWithUkraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/badges/StandWithUkraine.svg)](https://github.com/vshymanskyy/StandWithUkraine/blob/main/docs/README.md)

## General Information

Allows to perform communication with serial connected devices.

Includes following features:
* Retrieve latest sensor data(**raw**, **full**, **infrared**, **visible**)
* Retrieve meta information from the internal board state
* Modify settings for the light sensor.

## Setup

All setup related operations are processed via **Makefile** placed in the root directory.

In order to build IOC project it's required to execute the following command. It uses **CubeMX CLI** to generate **ELF** upload file:
```shell
make build
```

Built **ELF** file is intended to be used for manual upload via **STM Programmer**.

If **ProtocolBuffers** files need to be regenerated it's required to execute the following command:
```shell
make generate
```

## Scripts

### CLI

Detailed documentation can be found [here](./Scripts/cli/README.md)

# Use cases