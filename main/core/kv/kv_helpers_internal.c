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

#include "kv.h"
#include "keys.h"
#include "kv_ble.h"
#include "../ble/ble.h"

#include "../include_modules.h"

/*
 * [GENERATED]
 */

void internal_set_wifi_status(int value) {


  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_wifi_ssid(const char *value) {
  setstr(WIFI_SSID, value);

  value = on_set_wifi_ssid(value);

  setstr(WIFI_SSID, value);

  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}
void internal_set_wifi_password(const char *value) {
  setstr(WIFI_PASSWORD, value);

  value = on_set_wifi_password(value);

  setstr(WIFI_PASSWORD, value);

}
void internal_set_time(int value) {
  seti(TIME, value);

  value = on_set_time(value);

  seti(TIME, value);

  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_n_restarts(int value) {
  seti(N_RESTARTS, value);



  // TODO: httpd notify
}
void internal_set_ota_timestamp(int value) {
  seti(OTA_TIMESTAMP, value);



  // TODO: httpd notify
}
void internal_set_ota_server_ip(const char *value) {
  setstr(OTA_SERVER_IP, value);


}
void internal_set_ota_server_hostname(const char *value) {
  setstr(OTA_SERVER_HOSTNAME, value);


}
void internal_set_ota_server_port(const char *value) {
  setstr(OTA_SERVER_PORT, value);


}
void internal_set_ota_version_filename(const char *value) {
  setstr(OTA_VERSION_FILENAME, value);


}
void internal_set_ota_filename(const char *value) {
  setstr(OTA_FILENAME, value);


}
void internal_set_mqtt_broker_url(const char *value) {
  setstr(OTA, value);


}
void internal_set_broker_url(const char *value) {
  setstr(BROKER_URL, value);


}
void internal_set_i2c_sda(int value) {
  seti(I2C_SDA, value);



  // TODO: httpd notify
}
void internal_set_i2c_scl(int value) {
  seti(I2C_SCL, value);



  // TODO: httpd notify
}

/*
 * [/GENERATED]
 */
