/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../log/log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "kv.h"
#include "kv_ble.h"
#include "../include_modules.h"

void init_helpers();
nvs_handle kv_handle;

void preinit_kv() {
  // Initialize NVS
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK( err );

  err = nvs_open("kv_store", NVS_READWRITE, &kv_handle);
  if (err != ESP_OK) {
    ESP_LOGI(SGO_LOG_EVENT, "@KV Error (%s) opening NVS handle!\n", esp_err_to_name(err));
  }

  /*
   * [GENERATED]
   */

  init_helpers();
  const char *default_wifi_ssid = "";
  defaultstr(WIFI_SSID, default_wifi_ssid);
  const char *default_wifi_password = "";
  defaultstr(WIFI_PASSWORD, default_wifi_password);
  int default_time = 0;
  defaulti(TIME, default_time);
  int default_n_restarts = 0;
  defaulti(N_RESTARTS, default_n_restarts);
  int default_ota_timestamp = OTA_BUILD_TIMESTAMP;
  defaulti(OTA_TIMESTAMP, default_ota_timestamp);
  const char *default_ota_server_ip = CONFIG_OTA_SERVER_IP;
  defaultstr(OTA_SERVER_IP, default_ota_server_ip);
  const char *default_ota_server_hostname = CONFIG_OTA_SERVER_HOSTNAME;
  defaultstr(OTA_SERVER_HOSTNAME, default_ota_server_hostname);
  const char *default_ota_server_port = CONFIG_OTA_SERVER_PORT;
  defaultstr(OTA_SERVER_PORT, default_ota_server_port);
  const char *default_ota_version_filename = CONFIG_OTA_VERSION_FILENAME;
  defaultstr(OTA_VERSION_FILENAME, default_ota_version_filename);
  const char *default_ota_filename = CONFIG_OTA_FILENAME;
  defaultstr(OTA_FILENAME, default_ota_filename);
  const char *default_broker_url = CONFIG_BROKER_URL;
  defaultstr(BROKER_URL, default_broker_url);
  int default_i2c_0_sda = DEFAULT_I2C_0_SDA;
  defaulti(I2C_0_SDA, default_i2c_0_sda);
  int default_i2c_0_scl = DEFAULT_I2C_0_SCL;
  defaulti(I2C_0_SCL, default_i2c_0_scl);
  int default_i2c_0_enabled = 1;
  defaulti(I2C_0_ENABLED, default_i2c_0_enabled);
  int default_i2c_1_sda = DEFAULT_I2C_1_SDA;
  defaulti(I2C_1_SDA, default_i2c_1_sda);
  int default_i2c_1_scl = DEFAULT_I2C_1_SCL;
  defaulti(I2C_1_SCL, default_i2c_1_scl);
  int default_i2c_1_enabled = 0;
  defaulti(I2C_1_ENABLED, default_i2c_1_enabled);

  /*
   * [/GENERATED]
   */
}

void postinit_kv() {
  /*
   * [GENERATED]
   */

  sync_ble_str(WIFI_SSID, IDX_VALUE(WIFI_SSID));
  sync_ble_i(TIME, IDX_VALUE(TIME));

  // Initialize non-nvs keys
  int default_wifi_status = DISCONNECTED;
  set_wifi_status(default_wifi_status);


  /*
   * [/GENERATED]
   */
}

bool hasi(const char * key) {
  int32_t value;
  esp_err_t err = nvs_get_i32(kv_handle, (const char *)key, &value);
  return err == ESP_OK;
}

int geti(const char * key) {
  int32_t value;
  esp_err_t err = nvs_get_i32(kv_handle, (const char *)key, &value);
  ESP_ERROR_CHECK(err);
  return (int)value;
}

void seti(const char * key, int value) {
  esp_err_t err = nvs_set_i32(kv_handle, (const char *)key, (int32_t)value);
  ESP_ERROR_CHECK(err);
  nvs_commit(kv_handle);
}

void defaulti(const char * key, int value) {
  if (!hasi(key)) {
    seti(key, value);
  }
}

bool hasstr(const char * key) {
  size_t length;
  esp_err_t err = nvs_get_str(kv_handle, (const char *)key, NULL, &length);
  return err == ESP_OK;
}

void getstr(const char * key, char *value, size_t length) {
  esp_err_t err = nvs_get_str(kv_handle, key, value, &length);
  ESP_ERROR_CHECK(err);
}

void setstr(const char * key, const char * value) {
  esp_err_t err = nvs_set_str(kv_handle, (const char *)key, value);
  ESP_ERROR_CHECK(err);
  nvs_commit(kv_handle);
}

void defaultstr(const char * key, const char * value) {
  if (!hasstr(key)) {
    setstr(key, value);
  }
}
