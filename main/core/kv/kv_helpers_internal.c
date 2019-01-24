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
  set_wifi_ssid(value);

  value = on_set_wifi_ssid(value);

  set_wifi_ssid(value);

  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}
void internal_set_wifi_password(const char *value) {
  set_wifi_password(value);

  value = on_set_wifi_password(value);

  set_wifi_password(value);

}
void internal_set_time(int value) {
  set_time(value);

  value = on_set_time(value);

  set_time(value);

  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_n_restarts(int value) {
  set_n_restarts(value);



  // TODO: httpd notify
}
void internal_set_ota_timestamp(int value) {
  set_ota_timestamp(value);



  // TODO: httpd notify
}
void internal_set_ota_server_ip(const char *value) {
  set_ota_server_ip(value);


}
void internal_set_ota_server_hostname(const char *value) {
  set_ota_server_hostname(value);


}
void internal_set_ota_server_port(const char *value) {
  set_ota_server_port(value);


}
void internal_set_ota_version_filename(const char *value) {
  set_ota_version_filename(value);


}
void internal_set_ota_filename(const char *value) {
  set_ota_filename(value);


}
void internal_set_broker_url(const char *value) {
  set_broker_url(value);


}
void internal_set_i2c_0_sda(int value) {
  set_i2c_0_sda(value);



  // TODO: httpd notify
}
void internal_set_i2c_0_scl(int value) {
  set_i2c_0_scl(value);



  // TODO: httpd notify
}
void internal_set_i2c_0_enabled(int value) {
  set_i2c_0_enabled(value);



  // TODO: httpd notify
}
void internal_set_i2c_1_sda(int value) {
  set_i2c_1_sda(value);



  // TODO: httpd notify
}
void internal_set_i2c_1_scl(int value) {
  set_i2c_1_scl(value);



  // TODO: httpd notify
}
void internal_set_i2c_1_enabled(int value) {
  set_i2c_1_enabled(value);



  // TODO: httpd notify
}

/*
 * [/GENERATED]
 */
