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


static SemaphoreHandle_t _mutex_wifi_status; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_status_changed = true;

void reset_wifi_status_changed() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  _wifi_status_changed = false;
  xSemaphoreGive(_mutex_wifi_status);
}

bool is_wifi_status_changed() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  bool v = _wifi_status_changed;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}


static int _wifi_status = 0;

int get_wifi_status() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  int v = _wifi_status;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}

void set_wifi_status(int value) {
  xSemaphoreTake(_mutex_wifi_status, 0);
  if (_wifi_status == value) return;
  _wifi_status = value;
  _wifi_status_changed = true;
  xSemaphoreGive(_mutex_wifi_status);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_wifi_ssid; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_ssid_changed = true;

void reset_wifi_ssid_changed() {
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  _wifi_ssid_changed = false;
  xSemaphoreGive(_mutex_wifi_ssid);
}

bool is_wifi_ssid_changed() {
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  bool v = _wifi_ssid_changed;
  xSemaphoreGive(_mutex_wifi_ssid);
  return v;
}




void get_wifi_ssid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_SSID, dest, len);
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  _wifi_ssid_changed = true;
  xSemaphoreGive(_mutex_wifi_ssid);
}

void set_wifi_ssid(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_SSID, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_SSID, value);
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  _wifi_ssid_changed = true;
  xSemaphoreGive(_mutex_wifi_ssid);
  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}

static SemaphoreHandle_t _mutex_wifi_password; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_password_changed = true;

void reset_wifi_password_changed() {
  xSemaphoreTake(_mutex_wifi_password, 0);
  _wifi_password_changed = false;
  xSemaphoreGive(_mutex_wifi_password);
}

bool is_wifi_password_changed() {
  xSemaphoreTake(_mutex_wifi_password, 0);
  bool v = _wifi_password_changed;
  xSemaphoreGive(_mutex_wifi_password);
  return v;
}




void get_wifi_password(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_PASSWORD, dest, len);
  xSemaphoreTake(_mutex_wifi_password, 0);
  _wifi_password_changed = true;
  xSemaphoreGive(_mutex_wifi_password);
}

void set_wifi_password(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_PASSWORD, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_PASSWORD, value);
  xSemaphoreTake(_mutex_wifi_password, 0);
  _wifi_password_changed = true;
  xSemaphoreGive(_mutex_wifi_password);
}

static SemaphoreHandle_t _mutex_time; // TODO check RAM weight of creating so many semaphores :/
static bool _time_changed = true;

void reset_time_changed() {
  xSemaphoreTake(_mutex_time, 0);
  _time_changed = false;
  xSemaphoreGive(_mutex_time);
}

bool is_time_changed() {
  xSemaphoreTake(_mutex_time, 0);
  bool v = _time_changed;
  xSemaphoreGive(_mutex_time);
  return v;
}



int get_time() {
  return geti(TIME);
}

void set_time(int value) {
  if (geti(TIME) == value) return;
  seti(TIME, value);
  xSemaphoreTake(_mutex_time, 0);
  _time_changed = true;
  xSemaphoreGive(_mutex_time);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_n_restarts; // TODO check RAM weight of creating so many semaphores :/
static bool _n_restarts_changed = true;

void reset_n_restarts_changed() {
  xSemaphoreTake(_mutex_n_restarts, 0);
  _n_restarts_changed = false;
  xSemaphoreGive(_mutex_n_restarts);
}

bool is_n_restarts_changed() {
  xSemaphoreTake(_mutex_n_restarts, 0);
  bool v = _n_restarts_changed;
  xSemaphoreGive(_mutex_n_restarts);
  return v;
}



int get_n_restarts() {
  return geti(N_RESTARTS);
}

void set_n_restarts(int value) {
  if (geti(N_RESTARTS) == value) return;
  seti(N_RESTARTS, value);
  xSemaphoreTake(_mutex_n_restarts, 0);
  _n_restarts_changed = true;
  xSemaphoreGive(_mutex_n_restarts);
}


static SemaphoreHandle_t _mutex_ota_timestamp; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_timestamp_changed = true;

void reset_ota_timestamp_changed() {
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  _ota_timestamp_changed = false;
  xSemaphoreGive(_mutex_ota_timestamp);
}

bool is_ota_timestamp_changed() {
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  bool v = _ota_timestamp_changed;
  xSemaphoreGive(_mutex_ota_timestamp);
  return v;
}



int get_ota_timestamp() {
  return geti(OTA_TIMESTAMP);
}

void set_ota_timestamp(int value) {
  if (geti(OTA_TIMESTAMP) == value) return;
  seti(OTA_TIMESTAMP, value);
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  _ota_timestamp_changed = true;
  xSemaphoreGive(_mutex_ota_timestamp);
}


static SemaphoreHandle_t _mutex_ota_server_ip; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_ip_changed = true;

void reset_ota_server_ip_changed() {
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  _ota_server_ip_changed = false;
  xSemaphoreGive(_mutex_ota_server_ip);
}

bool is_ota_server_ip_changed() {
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  bool v = _ota_server_ip_changed;
  xSemaphoreGive(_mutex_ota_server_ip);
  return v;
}




void get_ota_server_ip(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_IP, dest, len);
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  _ota_server_ip_changed = true;
  xSemaphoreGive(_mutex_ota_server_ip);
}

void set_ota_server_ip(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_SERVER_IP, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_SERVER_IP, value);
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  _ota_server_ip_changed = true;
  xSemaphoreGive(_mutex_ota_server_ip);
}

static SemaphoreHandle_t _mutex_ota_server_hostname; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_hostname_changed = true;

void reset_ota_server_hostname_changed() {
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  _ota_server_hostname_changed = false;
  xSemaphoreGive(_mutex_ota_server_hostname);
}

bool is_ota_server_hostname_changed() {
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  bool v = _ota_server_hostname_changed;
  xSemaphoreGive(_mutex_ota_server_hostname);
  return v;
}




void get_ota_server_hostname(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_HOSTNAME, dest, len);
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  _ota_server_hostname_changed = true;
  xSemaphoreGive(_mutex_ota_server_hostname);
}

void set_ota_server_hostname(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_SERVER_HOSTNAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_SERVER_HOSTNAME, value);
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  _ota_server_hostname_changed = true;
  xSemaphoreGive(_mutex_ota_server_hostname);
}

static SemaphoreHandle_t _mutex_ota_server_port; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_port_changed = true;

void reset_ota_server_port_changed() {
  xSemaphoreTake(_mutex_ota_server_port, 0);
  _ota_server_port_changed = false;
  xSemaphoreGive(_mutex_ota_server_port);
}

bool is_ota_server_port_changed() {
  xSemaphoreTake(_mutex_ota_server_port, 0);
  bool v = _ota_server_port_changed;
  xSemaphoreGive(_mutex_ota_server_port);
  return v;
}




void get_ota_server_port(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_PORT, dest, len);
  xSemaphoreTake(_mutex_ota_server_port, 0);
  _ota_server_port_changed = true;
  xSemaphoreGive(_mutex_ota_server_port);
}

void set_ota_server_port(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_SERVER_PORT, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_SERVER_PORT, value);
  xSemaphoreTake(_mutex_ota_server_port, 0);
  _ota_server_port_changed = true;
  xSemaphoreGive(_mutex_ota_server_port);
}

static SemaphoreHandle_t _mutex_ota_version_filename; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_version_filename_changed = true;

void reset_ota_version_filename_changed() {
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  _ota_version_filename_changed = false;
  xSemaphoreGive(_mutex_ota_version_filename);
}

bool is_ota_version_filename_changed() {
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  bool v = _ota_version_filename_changed;
  xSemaphoreGive(_mutex_ota_version_filename);
  return v;
}




void get_ota_version_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_VERSION_FILENAME, dest, len);
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  _ota_version_filename_changed = true;
  xSemaphoreGive(_mutex_ota_version_filename);
}

void set_ota_version_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_VERSION_FILENAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_VERSION_FILENAME, value);
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  _ota_version_filename_changed = true;
  xSemaphoreGive(_mutex_ota_version_filename);
}

static SemaphoreHandle_t _mutex_ota_filename; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_filename_changed = true;

void reset_ota_filename_changed() {
  xSemaphoreTake(_mutex_ota_filename, 0);
  _ota_filename_changed = false;
  xSemaphoreGive(_mutex_ota_filename);
}

bool is_ota_filename_changed() {
  xSemaphoreTake(_mutex_ota_filename, 0);
  bool v = _ota_filename_changed;
  xSemaphoreGive(_mutex_ota_filename);
  return v;
}




void get_ota_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_FILENAME, dest, len);
  xSemaphoreTake(_mutex_ota_filename, 0);
  _ota_filename_changed = true;
  xSemaphoreGive(_mutex_ota_filename);
}

void set_ota_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_FILENAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_FILENAME, value);
  xSemaphoreTake(_mutex_ota_filename, 0);
  _ota_filename_changed = true;
  xSemaphoreGive(_mutex_ota_filename);
}

static SemaphoreHandle_t _mutex_broker_url; // TODO check RAM weight of creating so many semaphores :/
static bool _broker_url_changed = true;

void reset_broker_url_changed() {
  xSemaphoreTake(_mutex_broker_url, 0);
  _broker_url_changed = false;
  xSemaphoreGive(_mutex_broker_url);
}

bool is_broker_url_changed() {
  xSemaphoreTake(_mutex_broker_url, 0);
  bool v = _broker_url_changed;
  xSemaphoreGive(_mutex_broker_url);
  return v;
}




void get_broker_url(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_URL, dest, len);
  xSemaphoreTake(_mutex_broker_url, 0);
  _broker_url_changed = true;
  xSemaphoreGive(_mutex_broker_url);
}

void set_broker_url(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(BROKER_URL, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(BROKER_URL, value);
  xSemaphoreTake(_mutex_broker_url, 0);
  _broker_url_changed = true;
  xSemaphoreGive(_mutex_broker_url);
}

static SemaphoreHandle_t _mutex_i2c_0_sda; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_sda_changed = true;

void reset_i2c_0_sda_changed() {
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  _i2c_0_sda_changed = false;
  xSemaphoreGive(_mutex_i2c_0_sda);
}

bool is_i2c_0_sda_changed() {
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  bool v = _i2c_0_sda_changed;
  xSemaphoreGive(_mutex_i2c_0_sda);
  return v;
}



int get_i2c_0_sda() {
  return geti(I2C_0_SDA);
}

void set_i2c_0_sda(int value) {
  if (geti(I2C_0_SDA) == value) return;
  seti(I2C_0_SDA, value);
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  _i2c_0_sda_changed = true;
  xSemaphoreGive(_mutex_i2c_0_sda);
}


static SemaphoreHandle_t _mutex_i2c_0_scl; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_scl_changed = true;

void reset_i2c_0_scl_changed() {
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  _i2c_0_scl_changed = false;
  xSemaphoreGive(_mutex_i2c_0_scl);
}

bool is_i2c_0_scl_changed() {
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  bool v = _i2c_0_scl_changed;
  xSemaphoreGive(_mutex_i2c_0_scl);
  return v;
}



int get_i2c_0_scl() {
  return geti(I2C_0_SCL);
}

void set_i2c_0_scl(int value) {
  if (geti(I2C_0_SCL) == value) return;
  seti(I2C_0_SCL, value);
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  _i2c_0_scl_changed = true;
  xSemaphoreGive(_mutex_i2c_0_scl);
}


static SemaphoreHandle_t _mutex_i2c_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_enabled_changed = true;

void reset_i2c_0_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  _i2c_0_enabled_changed = false;
  xSemaphoreGive(_mutex_i2c_0_enabled);
}

bool is_i2c_0_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  bool v = _i2c_0_enabled_changed;
  xSemaphoreGive(_mutex_i2c_0_enabled);
  return v;
}



int get_i2c_0_enabled() {
  return geti(I2C_0_ENABLED);
}

void set_i2c_0_enabled(int value) {
  if (geti(I2C_0_ENABLED) == value) return;
  seti(I2C_0_ENABLED, value);
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  _i2c_0_enabled_changed = true;
  xSemaphoreGive(_mutex_i2c_0_enabled);
}


static SemaphoreHandle_t _mutex_i2c_1_sda; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_sda_changed = true;

void reset_i2c_1_sda_changed() {
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  _i2c_1_sda_changed = false;
  xSemaphoreGive(_mutex_i2c_1_sda);
}

bool is_i2c_1_sda_changed() {
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  bool v = _i2c_1_sda_changed;
  xSemaphoreGive(_mutex_i2c_1_sda);
  return v;
}



int get_i2c_1_sda() {
  return geti(I2C_1_SDA);
}

void set_i2c_1_sda(int value) {
  if (geti(I2C_1_SDA) == value) return;
  seti(I2C_1_SDA, value);
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  _i2c_1_sda_changed = true;
  xSemaphoreGive(_mutex_i2c_1_sda);
}


static SemaphoreHandle_t _mutex_i2c_1_scl; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_scl_changed = true;

void reset_i2c_1_scl_changed() {
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  _i2c_1_scl_changed = false;
  xSemaphoreGive(_mutex_i2c_1_scl);
}

bool is_i2c_1_scl_changed() {
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  bool v = _i2c_1_scl_changed;
  xSemaphoreGive(_mutex_i2c_1_scl);
  return v;
}



int get_i2c_1_scl() {
  return geti(I2C_1_SCL);
}

void set_i2c_1_scl(int value) {
  if (geti(I2C_1_SCL) == value) return;
  seti(I2C_1_SCL, value);
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  _i2c_1_scl_changed = true;
  xSemaphoreGive(_mutex_i2c_1_scl);
}


static SemaphoreHandle_t _mutex_i2c_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_enabled_changed = true;

void reset_i2c_1_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  _i2c_1_enabled_changed = false;
  xSemaphoreGive(_mutex_i2c_1_enabled);
}

bool is_i2c_1_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  bool v = _i2c_1_enabled_changed;
  xSemaphoreGive(_mutex_i2c_1_enabled);
  return v;
}



int get_i2c_1_enabled() {
  return geti(I2C_1_ENABLED);
}

void set_i2c_1_enabled(int value) {
  if (geti(I2C_1_ENABLED) == value) return;
  seti(I2C_1_ENABLED, value);
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  _i2c_1_enabled_changed = true;
  xSemaphoreGive(_mutex_i2c_1_enabled);
}


void init_helpers() {
  _mutex_wifi_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_ssid = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_password = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_time = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_n_restarts = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_timestamp = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_ip = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_hostname = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_port = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_version_filename = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_filename = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_broker_url = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_sda = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_scl = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_sda = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_scl = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
}

/*
 * [/GENERATED]
 */
