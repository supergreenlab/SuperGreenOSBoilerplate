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

Install the [mustache](https://mustache.github.io/) template engine (requires ruby):

```sh

gem install mustache

```

Might need to `sudo` that tho.

# Quickstart

As an example we're just going to stream a temp sensor's values to a cloud, for monitoring and alerts.
We'll also blink a led based on said sensor values (the hotter the faster it blinks).
The sensor used here is the sht1x, I'll pass the detail because it's a weird one, but it's i2c compatible, and I have the code here.

This will get us through the main features:
- create a module
- create an i2c device
- intialize the key in the system

First thing first, clone this repo, and run `make` to see if the whole xtensa/esp-idf setup is working:

```sh

git clone git@github.com:supergreenlab/SuperGreenOSBoilerplate.git SuperGreenTemp
cd SuperGreenTemp
make

```

Don't worry if you see a warning about i2c unused variables passing by.

It should end with something like this:

```sh

...
Generating esp32.common.ld
LD build/firmware.elf
esptool.py v2.6-beta1
To flash all build output, run 'make flash' or:
python2 /home/korben/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xd000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/ota_data_initial.bin 0x1000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/bootloader/bootloader.bin 0x10000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/firmware.bin 0x8000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/partitions.bin

```

## Basic concept

Now we're ready to start coding.
We'll start by streaming the temperature to the cloud.

So first step is to create the i2c device. There's a script for that, we'll call our device sth1x:

```sh

./templates.sh new_i2c_device shtx

```

Output should look like this:

```sh

Copying files to main/sht1x
Call mustache for templates/new_i2c_device/new_i2c_device.c.template to main/sht1x/sht1x.c
Call mustache for templates/new_i2c_device/new_i2c_device.h.template to main/sht1x/sht1x.h
Adding i2c device to i2c_devices in config.yml
===
Done

```

## Add i2c sensor

## Create first module

## Compile

## Cloud, Logs and MQTT

## Quick start

