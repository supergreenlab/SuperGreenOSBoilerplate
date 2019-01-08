![SuperGreenLab](assets/sgl.png?raw=true "SuperGreenLab")

# SuperGreenOSBoilerplate

SuperGreeOSBoilerplate proposes a way to ease and accelerate esp32 firmware development. By making most widely used features free.
It allows to generate most of the code for ble/http/wifi/ota/etc.. from a configuration file.

Built around the key/value and modules paradigm, it's quite close to what you'd find in a microservice architecture.
It is also higly influenced by drone firmware architectures like Taulabs or Ardupilot.

`Describe all the keys that your system will require to work and communicate with the outside world, write your modules (Sort of arduino sketches) and you're good to go.`

tl;dr configuring http/ws/ble/whatnot is a pain in the ass, this boilerplate generates C code from yml through mustache templates to remove the pain and focus on the fun.

## Features

- Key-value architecture
- Over-the-air update
- Statistic reports
- Bluetooth LE interface
- HTTP interface
- Mesh network (TODO)
- All logs redirected to MQTT
- Comes with a [cloud backend](http://github.com/SuperGreenCloud/)

# How to use

## Hardware

Based on [esp-idf](https://github.com/espressif/esp-idf) from espressif, and FreeRTOS.

Only runs on esp32.

I've mostly been woking with either:

- [Espressif ESP32 Development Board - Developer Edition](https://www.adafruit.com/product/3269)  
  Simple, but does not allow to flash the actual SuperGreenDriver.
- [Espressif ESP32 WROVER KIT - V3](https://www.adafruit.com/product/3384)  
  this one allows to debug through xtensa-esp32-elf-gdb and to flash the actual SuperGreenDriver.

![ESP32 WROVER KIT](assets/esp32.png?raw=true "ESP32 WROVER KIT")

## Workstation setup

Follow the [get-started guide from espressif](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/).

# Quickstart

## Basic concept

## Add i2c sensor

## Create first module

## Compile

## Cloud, Logs and MQTT

## Quick start

