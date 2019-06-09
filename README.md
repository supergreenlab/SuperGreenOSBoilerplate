![SuperGreenLab](assets/sgl.png?raw=true "SuperGreenLab")

[![SuperGreenLab](assets/reddit-button.png?raw=true "SuperGreenLab")](https://www.reddit.com/r/SuperGreenLab)

Table of Contents
=================

   * [SuperGreenOSBoilerplate](#supergreenosboilerplate)
      * [Features](#features)
      * [TODO](#todo)
      * [Philosophy](#philosophy)
   * [How to use](#how-to-use)
      * [Hardware](#hardware)
      * [Workstation setup](#workstation-setup)
   * [Quickstart](#quickstart)
      * [Creating modules and devices](#creating-modules-and-devices)
      * [Create sht1x i2c device](#create-sht1x-i2c-device)
         * [I2C device boilerplate](#i2c-device-boilerplate)
         * [Generated code](#generated-code)
         * [Driver code](#driver-code)
      * [Create sht1x_temp key in config.yml](#create-sht1x_temp-key-in-configyml)
      * [First run](#first-run)
         * [Tool setup](#tool-setup)
         * [WIFI AP](#wifi-ap)
         * [BLE](#ble)
      * [Create Led module](#create-led-module)
         * [Boilerplate](#boilerplate)
         * [Generated code](#generated-code-1)
         * [Code the led blinking](#code-the-led-blinking)
      * [WIFI Configuration](#wifi-configuration)
         * [Through WIFI AP](#through-wifi-ap)
         * [Through BLE](#through-ble)
      * [HTTP API](#http-api)
      * [Cloud, Logs and MQTT](#cloud-logs-and-mqtt)
         * [How data is sent to MQTT](#how-data-is-sent-to-mqtt)
         * [Setup MQTT configuration](#setup-mqtt-configuration)
         * [Monitoring](#monitoring)
         * [Alert](#alert)
      * [Over-The-Air (OTA) updates](#over-the-air-ota-updates)
   * [Troubleshoot](#troubleshoot)
   * [Contribute](#contribute)

# SuperGreenOSBoilerplate

tl;dr configuring http/ws/ble/whatnot is a pain in the ass, this boilerplate generates C code from yml through mustache templates to remove the pain and focus on the fun.

SuperGreenOSBoilerplate proposes a way to ease and accelerate esp32 firmware development. By making most widely used features free.
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
- Tiny local file system and http file serving
- All logs redirected to MQTT
- Comes with a [cloud backend](http://github.com/supergreenlab/SuperGreenCloud/)

## TODO

- Websocket
- Mesh network (TODO)
- Bluetooth (non BLE)

## Philosophy

The whole point is to end up with a code that is as static as possible, so we can totally eliminate any kind of memory leaks coming from our code itself.

This is meant to be running 24/24 7/7 for months straight, so better have something as predictable as possible. Full static code makes that more reachable.

But we don't want to lose the advantages of dynamic code, neither do we want to have to repeat things N times all over the code base. So the proposed solution is to produce static code before compilation.

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

For windows users struggling to install `ruby`, just type `pacman -Ss ruby`.
Then when the warning ` You don't have [path to bin dir] in your PATH, gem executables will not run.` just type `PATH="$PATH:[path to bin dir]"`.

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

If it's the first time you launch this command, this is going to ask you a bunch of questions, just press enter to enter the default.

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
- `module_name` is the name of the module of i2c_device we're creating.

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

- [sht1x.c](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/sht1x/sht1x.c)
- [sht1x.h](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/sht1x/sht1x.h)
- [sht1x_driver.c](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/sht1x/sht1x_driver.c)
- [sht1x_driver.h](https://raw.githubusercontent.com/supergreenlab/SuperGreenOS/master/main/sht1x/sht1x_driver.h)

Connect the sht1x sensor as follows:

```

- PWR: 3.3v
- GND: GND
- SDA: 26
- SCL: 27
cf. main/core/i2c/i2c.h (these values can be changed through http)

```

## Create sht1x_temp key in config.yml

Open `config.yml` and go all the way down the file.
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

Now there are two options to do the initial setup, by connecting either to its wifi or ble inteface.

### WIFI AP

In your wifi list, you'll see that the firmware has started its own wifi AP, it's called `🤖🍁`, and the default password is `multipass`.

Once connected to it, the firmware is accessible as `supergreendriver.local`.

The HTTP API is further explained [here](https://github.com/supergreenlab/SuperGreenOSBoilerplate#http-api)

### BLE

Download `LightBlue` on the ios and google stores, and start it.

You should see a device named `🤖🍁`, select it. Now you're connected.

In the characteristics list you should see a bunch of characteristics, those are the default ones, and at the very last, there's our temperature characteristic, it's name starts with `b2e0`, select it.

Now you can press the `read` button, and it should display, `0`, which is the default value we provided in the config.yml file, under the `default` key, at the very last line.

If you look in the logs of you esp32, you'll see it react when you press the `read` button.

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

You know what ? I'm too lazy to do this part.

Thus, this part shall be left as an exercise for the reader.

Hint: [Espressif has done a great job with their examples](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/gpio)

## WIFI Configuration

Now we're going to configure the wifi, it allows the device to reset its internal clock on reboots, update its firmware automatically, and stream its datas to the cloud.

Another thing it allows is complete control of all the firmware's parameter, ble has limitations (no more than 64 `keys`, for ex.). Http does not, so it's the preferred method to interact with the firmware.

### Through WIFI AP

When no wifi station is configured or if connection repeatedly fails, the firmware will start its own wifi AP, it's called `🤖🍁`, and the default password is `multipass`.

Once connected you can set the wifi credentials with the following commands:

(Try a few times if it complains about unknown host resolution, the firmware broadcast every 10 seconds.)
```sh

curl -X POST http://supergreendriver.local/s?k=WIFI_SSID&v=[ Insert SSID here ]
curl -X POST http://supergreendriver.local/s?k=WIFI_PASSWORD&v=[ Insert Wifi WPA password here ]

```

Only `wpa` is supported for now.

You can check the wifi connection status in the log or by repeatedly calling this command, until it says `3`, which means `CONNECTED`

```sh

curl http://supergreendriver.local/i?k=WIFI_STATUS

```

### Through BLE

To configure the wifi with BLE get back to lightblue, and select the characteristic starting with `372f`, it's the `wifi_status` characteristic, click the `subscribe` button, so you'll have a notification when the value changes.

Now select the characteristic starting by `6ca3`, it's the `wifi_ssid` characteristic, press the `write` button in lightblue, and set your SSID, watch out for android users: the strings are in hex, so you can't type it directly, use a service like [this](https://sites.google.com/site/nathanlexwww/tools/utf8-convert) to do the transformation.

Do the same for the `wifi_password`, it starts with `f7e4`.

Now you should have notifications for the `wifi_status` characteristic changing value. You want it to be equal to `3`.

Once it's done, your firmware will be available as supergreendriver.local, for example the url [http://supergreendriver.local/s?k=DEVICE_NAME](http://supergreendriver.local/s?k=DEVICE_NAME) will print it's name.
Try a few times if it complains about unknown host resolution, the firmware broadcast every 10 seconds.

## HTTP API

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

## Cloud, Logs and MQTT

Now monitoring and alerts !

### How data is sent to MQTT

Now we have a way to know if it's too hot or too cold, but this would be even more useful if we could get that data when we're not here, or even better, if it could tell us when the temperature leaves a given range.

Actually we'd like to know EVERYTHING that is happening inside the chip, there are also stack RAM monitoring that could be useful, or even re-reading the logs to see what might have lead to a crash.

The boilerplate comes with an mqtt client, to make it simple, and be sure to never lose anything, the firmware simply catches all logs from the code, and sends it directly to an mqtt server.

MQTT is a publish/subscribe protocol, if you haven't used that before, it's like a big hub, clients connect to it, and can publish (send), or subscribe to messages.

Which means that once the logs are gone in an mqtt server, it's really easy to plug other things to it, like a redis instance to keep the values of all key/value pairs of the system, or a prometheus server to produce nive graphs and alerts.

You can even connect a voice assistant like Alexa or others. But that's useless.

Checkout the repo [SuperGreenCloud](https://github.com/supergreenlab/SuperGreenCloud), it's a collection of softwares pre-configured, to let you deploy your own cloud in a matter of minutes.

### Setup MQTT configuration

There is a key pre-configured to set the mqtt broker url: `BROKER_URL`, it's only accessible through wifi.
To change it's value:

```sh

curl -X POST http://supergreendriver.local/s?k=BROKER_URL&v=[ Enter your URL here ]

```

Restarting is required for changes to take effect (removing this is on the TODO)

Now you should start seeing logs arriving in prometheus and grafana.

### Monitoring

Please follow the [SuperGreenCloud Quickstart guide](https://github.com/supergreenlab/SuperGreenCloud#quickstart).

Which will lead you to something like this:

![Graphs 1](assets/sht1x-graphs.png?raw=true "Graphs 1")
![Graphs 2](assets/sht1x-graphs2.png?raw=true "Grahs 2")

Let me know if you need a complete guide, because that's much more work than just typing text:P

### Alert

TODO

## Over-The-Air (OTA) updates

Now that we have our device setup and installed, we don't really want to have to bet back to it with a usb cord and a laptop.

That's where OTA updates get handy, we only have to place two files on a server online, tell the firmware how to find them, and it'll check periodically if it needs to update itself.

Again there are a few keys that you can configure to set this up, and they're only accessible through wifi:

- OTA_SERVER_IP: IP address of the server.
- OTA_SERVER_HOSTNAME: Hostname to set in the `Host: ` http header.
- OTA_SERVER_PORT: Server port.
- OTA_VERSION_FILENAME: The path of the file containing the version information, right now it contains a timestamp, that is compared to the timestamp of the build (set at compile time).
- OTA_FILENAME: The actual firmware file path.

# Keys definition

The whole OS revolves around the key/value database embedded (KV) in the firmware.
KV is the center of trust, it sits in the middle. All modules can add more keys to work with.
All keys are defined in the file [config.yml](https://github.com/supergreenlab/SuperGreenOS/blob/master/config.yml).

Each keys have a set of avaiable configs:

- *name*: lowercase name, ex: wifi_ssid
- *caps_name*: uppcase name, ex: WIFI_SSID
- *string* or *integer*: should have the value true, determines the datatype used for the value (string is a char[512] and integer is int)
- *nvs*: if absent the key is not persistent between reboots (ie. not stored in flash)
  - *key*: name of the key in the flash, limited to 15 characters, ex: WSSID
- *ble*: if absent, the key will not be available over ble, watchout ble only supports a limited number of available keys.
  - *first*: needs to be set to true if it's the first on the list, that's a mustache template limitation:( 
  - *uuid*: BLE UUID, in the form: "{0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x6c}" see [here](http://yupana-engineering.com/online-uuid-to-c-array-converter)
  - *write*: Set this to true if the key is writable
  - *notify*: Set this to true to tell the generated to produce a ble notification on value internally changed.
- *http*: if absent, the key is not be available over http
  - *write*: Set this to true if the key is writable
  - *noop*: Set this to true, just to avoid have an empty 'http' configuration (when `write` is absent)
- *write_cb*: This determines if you want a callback to be called when the key is changed, either set it to `true` and it'll call a function called `on_set_[name]`, or directly enter the name of a function you have. prototype of the function is as: `const char *on_set_name(const char *ssid)` for a string or `int on_set_name(int boxId, int value)` for integer values.
- *default*: This is the default value for the key, if the value is in a variable or macro in you code, skip this and use `default_var` instead.
- *default_var*: allows to use a variable or macro name for the default value.

# Troubleshoot

Right now SuperGreenLab does not have an official support hotline.
But here's a bunch of places where we'll respond:

- [towelie@supergreenlab.com](mailto:towelie@supergreenlab.com)
- [r/supergreenlab](https://www.reddit.com/r/supergreenlab), maybe the chat is the right place for quick questions
- [Github issues](https://github.com/supergreenlab/SuperGreenOSBoilerplate/issues)

# Contribute

Actually that's the whole purpose of this repository, so what you'll learn on SuperGreenOS can actually be used for other stuffs:)
