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

void open_kv() {
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
}

void preinit_kv() {
  /*
   * [GENERATED]
   */

  init_helpers();
  const char *default_wifi_ssid = "";
  defaultstr(WIFI_SSID, default_wifi_ssid);
  const char *default_wifi_password = "";
  defaultstr(WIFI_PASSWORD, default_wifi_password);
  const char *default_wifi_ap_ssid = DEFAULT_AP_SSID;
  defaultstr(WIFI_AP_SSID, default_wifi_ap_ssid);
  const char *default_wifi_ap_password = DEFAULT_AP_PASSWORD;
  defaultstr(WIFI_AP_PASSWORD, default_wifi_ap_password);
  const char *default_mdns_domain = DEFAULT_MDNS_DOMAIN;
  defaultstr(MDNS_DOMAIN, default_mdns_domain);
  const char *default_wifi_ip = "0.0.0.0";
  defaultstr(WIFI_IP, default_wifi_ip);
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
  const char *default_ota_basedir = CONFIG_OTA_BASEDIR;
  defaultstr(OTA_BASEDIR, default_ota_basedir);
  const char *default_broker_url = CONFIG_BROKER_URL;
  defaultstr(BROKER_URL, default_broker_url);
  const char *default_broker_channel = "";
  defaultstr(BROKER_CHANNEL, default_broker_channel);
  const char *default_broker_clientid = "";
  defaultstr(BROKER_CLIENTID, default_broker_clientid);
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
  sync_ble_str(WIFI_IP, IDX_VALUE(WIFI_IP));
  sync_ble_i(TIME, IDX_VALUE(TIME));

  // Initialize non-nvs keys
  if (is_wifi_status_undefined()) {
    int default_wifi_status = DISCONNECTED;
    set_wifi_status(default_wifi_status);
  }
  if (is_ota_status_undefined()) {
    int default_ota_status = OTA_STATUS_IDLE;
    set_ota_status(default_ota_status);
  }
  if (is_reboot_undefined()) {
    int default_reboot = 0;
    set_reboot(default_reboot);
  }


  /*
   * [/GENERATED]
   */
}

void reset_defaults() {
  const char *default_wifi_ssid = "";
  setstr(WIFI_SSID, default_wifi_ssid);
  const char *default_wifi_password = "";
  setstr(WIFI_PASSWORD, default_wifi_password);
  const char *default_wifi_ap_ssid = DEFAULT_AP_SSID;
  setstr(WIFI_AP_SSID, default_wifi_ap_ssid);
  const char *default_wifi_ap_password = DEFAULT_AP_PASSWORD;
  setstr(WIFI_AP_PASSWORD, default_wifi_ap_password);
  const char *default_mdns_domain = DEFAULT_MDNS_DOMAIN;
  setstr(MDNS_DOMAIN, default_mdns_domain);
  const char *default_wifi_ip = "0.0.0.0";
  setstr(WIFI_IP, default_wifi_ip);
  int default_time = 0;
  seti(TIME, default_time);
  int default_n_restarts = 0;
  seti(N_RESTARTS, default_n_restarts);
  int default_ota_timestamp = OTA_BUILD_TIMESTAMP;
  seti(OTA_TIMESTAMP, default_ota_timestamp);
  const char *default_ota_server_ip = CONFIG_OTA_SERVER_IP;
  setstr(OTA_SERVER_IP, default_ota_server_ip);
  const char *default_ota_server_hostname = CONFIG_OTA_SERVER_HOSTNAME;
  setstr(OTA_SERVER_HOSTNAME, default_ota_server_hostname);
  const char *default_ota_server_port = CONFIG_OTA_SERVER_PORT;
  setstr(OTA_SERVER_PORT, default_ota_server_port);
  const char *default_ota_basedir = CONFIG_OTA_BASEDIR;
  setstr(OTA_BASEDIR, default_ota_basedir);
  const char *default_broker_url = CONFIG_BROKER_URL;
  setstr(BROKER_URL, default_broker_url);
  const char *default_broker_channel = "";
  setstr(BROKER_CHANNEL, default_broker_channel);
  const char *default_broker_clientid = "";
  setstr(BROKER_CLIENTID, default_broker_clientid);
  int default_i2c_0_sda = DEFAULT_I2C_0_SDA;
  seti(I2C_0_SDA, default_i2c_0_sda);
  int default_i2c_0_scl = DEFAULT_I2C_0_SCL;
  seti(I2C_0_SCL, default_i2c_0_scl);
  int default_i2c_0_enabled = 1;
  seti(I2C_0_ENABLED, default_i2c_0_enabled);
  int default_i2c_1_sda = DEFAULT_I2C_1_SDA;
  seti(I2C_1_SDA, default_i2c_1_sda);
  int default_i2c_1_scl = DEFAULT_I2C_1_SCL;
  seti(I2C_1_SCL, default_i2c_1_scl);
  int default_i2c_1_enabled = 0;
  seti(I2C_1_ENABLED, default_i2c_1_enabled);
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
