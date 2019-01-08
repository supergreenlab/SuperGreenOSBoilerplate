![SuperGreenLab](assets/sgl.png?raw=true "SuperGreenLab")

# SuperGreenOSBoilerplate

tl;dr configuring http/ws/ble/whatnot is a pain in the ass, this boilerplate generates C code from yml through mustache templates to remove the pain and focus on the fun.

SuperGreeOSBoilerplate proposes a way to ease and accelerate esp32 firmware development. By making most widely used features free.
It allows to generate most of the code for ble/http/wifi/ota/etc.. from a configuration file.

Built around the key/value and modules paradigm, it's quite close to what you'd find in a microservice architecture.
It is also higly influenced by drone firmware architectures like Taulabs or Ardupilot.

`Describe all the keys that your system will require to work and communicate with the outside world, write your modules (Sort of arduino sketches) and you're good to go.`

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

For the 2 first step, we'll be using the script called `templates.sh`, which usage is as follows:

```sh

./templates.sh
[Usage] ./templates.sh template_name module_name

```

- `template_name` is either `new_module` or `new_i2c_device`.
- `module_name` is the name of the module of i2c_device we're creating

## Add i2c sensor

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
===
Running ./update_template.sh....
Processing main/component.mk.template: Done
Processing main/init.c.template: Done
Processing main/core/kv/kv.c.template: Done
Processing main/core/kv/kv_helpers_internal.h.template: Done
Processing main/core/kv/kv_helpers_internal.c.template: Done
Processing main/core/kv/kv_helpers.c.template: Done
Processing main/core/kv/keys.h.template: Done
Processing main/core/kv/kv.h.template: Done
Processing main/core/i2c/i2c.c.template: Done
Processing main/core/httpd/httpd_kv_handlers.c.template: Done
Processing main/core/ble/ble_db.h.template: Done
Processing main/core/ble/ble_db.c.template: Done
Processing main/core/include_modules.h.template: Done
Processing main/core/stat_dump/stat_dump.c.template: Done

```

Run the `make` command to ensure that the newly created module did not wreck everything:

```sh
make
Toolchain path: /home/korben/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
Toolchain version: crosstool-ng-1.22.0-80-g6c4433a
Compiler version: 5.2.0
Python requirements from /home/korben/esp-idf/requirements.txt are satisfied.
App "firmware" version: 24fcccf-dirty
CC build/app_update/esp_app_desc.o
AR build/app_update/libapp_update.a
CC build/main/init.o

[..... BLAH .....]

CC build/main/sht1x/sht1x.o      <------ This is our new i2c_device
AR build/main/libmain.a
Generating libapp_update.a.sections_info
Generating libmain.a.sections_info
Generating esp32.common.ld
LD build/firmware.elf
esptool.py v2.6-beta1
To flash all build output, run 'make flash' or:
python2 /home/korben/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xd000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/ota_data_initial.bin 0x1000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/bootloader/bootloader.bin 0x10000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/firmware.bin 0x8000 /home/korben/SuperGreenLab/SuperGreenOSBoilerplate/build/partitions.bin
```

Good.

Now we have a new directory under `main/sht1x/` containing two files `sht1x.c` and `sht1x.h`, let's get there and open the files with your favorite code editor.

They look something like this:

sth1x.h
```c
/*
 * GPL HEADER
 */

#ifndef NEW_I2C_DEVICE_H_
#define NEW_I2C_DEVICE_H_

void init_sht1x();
void loop_sht1x(int sda, int sck);

#endif
```

sht1x.c
```c
/*
 * GPL HEADER
 */

#include <stdlib.h>
#include "sht1x.h"
#include "driver/i2c.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#define NEW_I2C_DEVICE_ADDR 0x42

void init_sht1x() {
  ESP_LOGI(SGO_LOG_EVENT, "@NEW_I2C_DEVICE Initializing sht1x i2c device\n");
  // TODO: write you setup code here
}

void loop_sht1x(int sda, int sck) {
  // start_i2c();
  // TODO: write you i2c device read code here
  // stop_i2c();
}
```

## Create first module

## Compile

## Cloud, Logs and MQTT

## Quick start

