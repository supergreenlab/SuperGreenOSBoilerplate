![SuperGreenLab](assets/sgl.png?raw=true "SuperGreenLab")

# SuperGreenOSBoilerplate

tl;dr configuring http/ws/ble/whatnot is a pain in the ass, this boilerplate generates C code from yml through mustache templates to remove the pain and focus on the fun.

SuperGreeOSBoilerplate proposes a way to ease and accelerate esp32 firmware development. By making most widely used features free.
It allows to generate most of the code for ble/http/wifi/ota/etc.. from a configuration file.

Built around the key/value and modules paradigm, it's quite close to what you'd find in a microservice architecture.
It is also higly influenced by drone firmware architectures like Taulabs or Ardupilot.

Describe all the keys that your system will require to work and communicate with the outside world, write your modules (Sort of arduino sketches) and you're good to go.

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

## Creating modules and devices

Now we're ready to start coding.
We'll start by streaming the temperature to the cloud.

For the 2 first step, we'll be using the script called `templates.sh`, which usage is as follows:

```sh

./templates.sh
[Usage] ./templates.sh template_name module_name

```

- `template_name` is either `new_module` or `new_i2c_device`.
- `module_name` is the name of the module of i2c_device we're creating

## Create sht1x i2c device

So first step is to create the i2c device. There's a script for that, we'll call our device sth1x:

### I2C device boilerplate

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

### Generated code

Now we have a new directory under `main/sht1x/` containing two files `sht1x.c` and `sht1x.h`, let's get there and open the files with your favorite code editor.

They look something like this:

sth1x.h
```c
/*
 * GPL HEADER
 */

#ifndef SHT1X_H_
#define SHT1X_H_

void init_sht1x(int sda, int sck);
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

#define SHT1X_ADDR 0x42

void init_sht1x(int sda, int sck) {
  ESP_LOGI(SGO_LOG_EVENT, "@SHT1X Initializing sht1x i2c device\n");
  // TODO: write you setup code here
}

void loop_sht1x(int sda, int sck) {
  // start_i2c();
  // TODO: write you i2c device read code here
  // stop_i2c();
}
```

There are two functions defined, `init_sht1x` and `loop_sht1x`, `loop_sht1x` is called repeatedly every few seconds, depending on how many devices you have (only one i2c device can talk at a time).
The `init_sht1x` method is called once at the very start of the program.

### Driver code

Let's get this straight, and copy those files in the `main/sht1x` directory:

- [sht1x.c](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/core/i2c/sht1x/sht1x.c)
- [sht1x.h](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/core/i2c/sht1x/sht1x.h)
- [sht1x_driver.c](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/core/i2c/sht1x/sht1x_driver.c)
- [sht1x_driver.h](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/core/i2c/sht1x/sht1x_driver.h)

Connect the sht1x sensor as follows:

```

- PWR: 3.3v
- GND: GND
- SDA: 26
- SCL: 27
cf. main/core/i2c/i2c.h (these values can be changed through http)

```

## Create sht1x_temp key in config.yml

Open `config.yml` and go all the down the file.
We'll add a temperature key, of type integer, accessible over ble and wifi, but read-only.
And we want it to be automatically backed in the flash store. So the value stays there even after a reboot.

The end of your `config.yml` should look like this:

```yml
  #
  # Custom keys
  #

  - name: sht1x
    caps_name: SHT1X
    integer: true
    nvs:
      key: SHT1X
    ble:
      uuid: "{0x91,0xb6,0x64,0x14,0xa9,0xba,0x6a,0x30,0x80,0xc1,0x67,0x62,0x25,0xef,0xe0,0xb2}"
      notify: true
    http:
      noop: true
    default: 0

```

Now run the `update.sh` command. And then `make` to see that everything's ok.

## First run

### Tool setup

At that point we want to see our key available over ble and http, right ?

So plug in your esp32, set the right serial port by doing a `make menuconfig` and under `Serial flasher config -> Default serial port` you'll be able to set the port.

Finding the right port depends on your system, on mine (debian) it's /dev/ttyUSBX, X being 0 for small esp32 boards, and should be 1 when using the esp-wrover-kit.

On macosx I had to change the python version used too, explicitely set `python2` under `SDK tool configuration -> Python 2 interpreter`

Now let's run:

```sh

make flash monitor

```

After some uploading, you should see all the esp's logs (in green) appearing on your screen.

### BLE access

Download `LightBlue` on the ios and google stores, and start it.

You should see a device named `🤖🍁`, select it. Now you're connected.

In the characteristics list you should see a bunch of characteristics, those are the default ones, and at the very last, there's our temperature characteristic, it's name starts with `b2e0`, select it.

Now you can press the `read` button, and it should display, `0`, which is the default value we provided in the config.yml file, under the `default` key, at the very last line.

If you look in the logs of you esp32, you'll see it react when you press the `read` button.

### HTTP access

Now we're going to configure the wifi, it allows the device to re-set its internal clock on reboots, update its firmware automatically, and stream its datas to the cloud.

Another thing it allows is complete control of all the firmware's parameter, ble has limitations (no more than 64 `keys`, for ex.). Http does not, so it's the preferred method to interact with the firmware.

To configure the wifi get back to lightblue, and select the characteristic starting with `372f`, it's the `wifi_status` characteristic, click the `subscribe` button, so you'll have a notification when the value changes.

Now select the characteristic starting by `6ca3`, it's the `wifi_ssid` characteristic, press the `write` button in lightblue, and set your SSID, watch out for android users: the strings are in hex, so you can't type it directly, use a service like [this](https://sites.google.com/site/nathanlexwww/tools/utf8-convert) to do the transformation.

Do the same for the `wifi_password`, it starts with `f7e4`.

Now you should have notifications for the `wifi_status` characteristic changing value. You want it to be equal to `3`.

Once it's done, your firmware will be available as supergreendriver.local, for example the url [http://supergreendriver.local/s?k=DEVICE_NAME](http://supergreendriver.local/s?k=DEVICE_NAME). Try a few times if it complains about unknown host resolution, the firmware broadcast every 10 seconds.

The HTTP interface allows read and write on the firmware's keys that have a `write: true` attribute in `config.yml`, websocket change subscribing is underway.

The HTTP interface has 2 routes for now `/i` and `/s`, they correspond to the type of the value, `i` for `integer`, and `s` for `string`.

Query parameters are as follows:

- GET requests: `k` for the key's `name` to get.
- POST requests: `k` for the key's `name` to set, and `v` for the value to set.

So to set a new DEVICE_NAME:

```sh
curl -X POST http://supergreendriver.local/s?k=DEVICE_NAME&v=NewName
```

And to get the DEVICE_NAME back:

```sh
curl http://supergreendriver.local/s?k=DEV_NAME
NewName
```

All right, everything seems to be working, let's move on.

## Create Led module

We usually want to do something other than monitoring and alerts, in our case we have a temperature value, so we could control a motor based on that for example.

To illustrate that, we'll just blink a led, the hotter it gets the faster it blinks.

### Boilerplate

Just like we did with the i2c device, we'll use the `templates.sh` script to generate the base code for our module:

```sh

./templates.sh new_module led

```

(things should go roughly as with the i2c device)

Run a `make` to make sure it's ok.

### Generated code

Module files look like i2c devices' files, except that they run their own freeRTOS task.

Open the generated files in `main/led`:

led.h
```c

/*
 * [GPL HEADER]
 */

#ifndef LED_H_
#define LED_H_

void init_led();

#endif

```

led.c
```c

/*
 * [GPL HEADER]
 */

#include <stdlib.h>
#include "led.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

static void led_task(void *param);

void init_led() {
  ESP_LOGI(SGO_LOG_EVENT, "@LED Initializing led module\n");

  // TODO: write you setup code here

  xTaskCreate(led_task, "LED", 4096, NULL, 10, NULL);
}

static void led_task(void *param) {
  while (true) {

    // TODO: write your loop code here

    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}
```

We have two functions, `init_led` and `led_task`, `init_led` is called once on startup, and `led_task` is the code of your task.

In case you have never used freeRTOS before, you can see them as seperate threads.

If you have already used arduino, it's like a sketch that can run with other sketches at the same time on the same chip. Only difference with a sketch is that you never exit a task (hence the `while(true)`.

### Code the led blinking

## Cloud, Logs and MQTT

Now monitoring and alerts !

### How data is sent to MQTT

Now we have a way to know if it's too hot or too cold, but this would be even more useful if we could get that data when we're not here, or even better, if it could tell us when the temperature leaves a given range.

Actually we'd like to know EVERYTHING that is happening inside the chip, there are also stack RAM monitoring that could be useful, or even re-reading the logs to see what might a provoked a crash.

The boilerplate comes with an mqtt client, to make it simple, and be sure to sever nose anything, the firmware simply catches all logs from the code, and sends it directly to an mqtt server.

MQTT is a publish/subscribe protocol, if you haven't used that before, it's like a big hub, clients connect to it, and can publish (send), or subscribe to messages.

Which means that once the logs a gone in an mqtt server, it's really easy to plug other things to it, like a redis instance to keep the values of all key/value pairs of the system, or a prometheus server to produce nive graphs and alerts.

You can even connect a voice assistant like Alexa or others. But that's useless.

Checkout the repo [SuperGreenCloud](https://github.com/supergreenlab/SuperGreenCloud), it's a collection of softwares pre-configured, to let you deploy your own cloud in a matter of minutes.

### Setup MQTT configuration

There are 

## OTA

