/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
 * Author: Constantin Clauzel <constantin.clauzel@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "kv.h"
#include "kv_ble.h"
#include "../ble/ble.h"

/*
 * [GENERATED]
 */

StaticSemaphore_t mutex_buffer;


static SemaphoreHandle_t _mutex_wifi_status;
static int _wifi_status = 0;

int get_wifi_status() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  int v = _wifi_status;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}

void set_wifi_status(int value) {
  xSemaphoreTake(_mutex_wifi_status, 0);
  _wifi_status = value;
  xSemaphoreGive(_mutex_wifi_status);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));
}




void get_wifi_ssid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_SSID, dest, len);
}

void set_wifi_ssid(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(WIFI_SSID, value);
  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}



void get_wifi_password(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_PASSWORD, dest, len);
}

void set_wifi_password(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(WIFI_PASSWORD, value);
}


int get_time() {
  return geti(TIME);
}

void set_time(int value) {
  seti(TIME, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}



int get_n_restarts() {
  return geti(N_RESTARTS);
}

void set_n_restarts(int value) {
  seti(N_RESTARTS, value);
}



int get_ota_timestamp() {
  return geti(OTA_TIMESTAMP);
}

void set_ota_timestamp(int value) {
  seti(OTA_TIMESTAMP, value);
}




void get_ota_server_ip(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_IP, dest, len);
}

void set_ota_server_ip(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_SERVER_IP, value);
}



void get_ota_server_hostname(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_HOSTNAME, dest, len);
}

void set_ota_server_hostname(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_SERVER_HOSTNAME, value);
}



void get_ota_server_port(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_PORT, dest, len);
}

void set_ota_server_port(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_SERVER_PORT, value);
}



void get_ota_version_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_VERSION_FILENAME, dest, len);
}

void set_ota_version_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_VERSION_FILENAME, value);
}



void get_ota_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_FILENAME, dest, len);
}

void set_ota_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_FILENAME, value);
}



void get_broker_url(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_URL, dest, len);
}

void set_broker_url(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(BROKER_URL, value);
}


int get_i2c_0_sda() {
  return geti(I2C_0_SDA);
}

void set_i2c_0_sda(int value) {
  seti(I2C_0_SDA, value);
}



int get_i2c_0_scl() {
  return geti(I2C_0_SCL);
}

void set_i2c_0_scl(int value) {
  seti(I2C_0_SCL, value);
}



int get_i2c_0_enabled() {
  return geti(I2C_0_ENABLED);
}

void set_i2c_0_enabled(int value) {
  seti(I2C_0_ENABLED, value);
}



int get_i2c_1_sda() {
  return geti(I2C_1_SDA);
}

void set_i2c_1_sda(int value) {
  seti(I2C_1_SDA, value);
}



int get_i2c_1_scl() {
  return geti(I2C_1_SCL);
}

void set_i2c_1_scl(int value) {
  seti(I2C_1_SCL, value);
}



int get_i2c_1_enabled() {
  return geti(I2C_1_ENABLED);
}

void set_i2c_1_enabled(int value) {
  seti(I2C_1_ENABLED, value);
}


void init_helpers() {
  _mutex_wifi_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
}

/*
 * [/GENERATED]
 */
