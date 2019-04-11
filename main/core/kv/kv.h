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

#ifndef KV_H_
#define KV_H_

#include <stdlib.h>
#include <stdbool.h>
#include "keys.h"

#define MAX_KVALUE_SIZE 517

void open_kv();
void preinit_kv();
void postinit_kv();
void reset_defaults();

int geti(const char * key);
void seti(const char * key, int value);
bool hasi(const char * key);
void defaulti(const char * key, int value);

void getstr(const char * key, char *value, const size_t length);
void setstr(const char * key, const char * value);
bool hasstr(const char * key);
void defaultstr(const char * key, const char * value);

/*
 * [GENERATED]
 */

void reset_wifi_status_changed();
bool is_wifi_status_changed();
int get_wifi_status();
void set_wifi_status(int value);
void reset_wifi_ssid_changed();
bool is_wifi_ssid_changed();
void get_wifi_ssid(char *dest, size_t len);
void set_wifi_ssid(const char *value);
void reset_wifi_password_changed();
bool is_wifi_password_changed();
void get_wifi_password(char *dest, size_t len);
void set_wifi_password(const char *value);
void reset_wifi_ap_ssid_changed();
bool is_wifi_ap_ssid_changed();
void get_wifi_ap_ssid(char *dest, size_t len);
void set_wifi_ap_ssid(const char *value);
void reset_wifi_ap_password_changed();
bool is_wifi_ap_password_changed();
void get_wifi_ap_password(char *dest, size_t len);
void set_wifi_ap_password(const char *value);
void reset_mdns_domain_changed();
bool is_mdns_domain_changed();
void get_mdns_domain(char *dest, size_t len);
void set_mdns_domain(const char *value);
void reset_wifi_ip_changed();
bool is_wifi_ip_changed();
void get_wifi_ip(char *dest, size_t len);
void set_wifi_ip(const char *value);
void reset_time_changed();
bool is_time_changed();
int get_time();
void set_time(int value);
void reset_n_restarts_changed();
bool is_n_restarts_changed();
int get_n_restarts();
void set_n_restarts(int value);
void reset_ota_timestamp_changed();
bool is_ota_timestamp_changed();
int get_ota_timestamp();
void set_ota_timestamp(int value);
void reset_ota_server_ip_changed();
bool is_ota_server_ip_changed();
void get_ota_server_ip(char *dest, size_t len);
void set_ota_server_ip(const char *value);
void reset_ota_server_hostname_changed();
bool is_ota_server_hostname_changed();
void get_ota_server_hostname(char *dest, size_t len);
void set_ota_server_hostname(const char *value);
void reset_ota_server_port_changed();
bool is_ota_server_port_changed();
void get_ota_server_port(char *dest, size_t len);
void set_ota_server_port(const char *value);
void reset_ota_basedir_changed();
bool is_ota_basedir_changed();
void get_ota_basedir(char *dest, size_t len);
void set_ota_basedir(const char *value);
void reset_ota_status_changed();
bool is_ota_status_changed();
int get_ota_status();
void set_ota_status(int value);
void reset_broker_url_changed();
bool is_broker_url_changed();
void get_broker_url(char *dest, size_t len);
void set_broker_url(const char *value);
void reset_broker_channel_changed();
bool is_broker_channel_changed();
void get_broker_channel(char *dest, size_t len);
void set_broker_channel(const char *value);
void reset_broker_clientid_changed();
bool is_broker_clientid_changed();
void get_broker_clientid(char *dest, size_t len);
void set_broker_clientid(const char *value);
void reset_i2c_0_sda_changed();
bool is_i2c_0_sda_changed();
int get_i2c_0_sda();
void set_i2c_0_sda(int value);
void reset_i2c_0_scl_changed();
bool is_i2c_0_scl_changed();
int get_i2c_0_scl();
void set_i2c_0_scl(int value);
void reset_i2c_0_enabled_changed();
bool is_i2c_0_enabled_changed();
int get_i2c_0_enabled();
void set_i2c_0_enabled(int value);
void reset_i2c_1_sda_changed();
bool is_i2c_1_sda_changed();
int get_i2c_1_sda();
void set_i2c_1_sda(int value);
void reset_i2c_1_scl_changed();
bool is_i2c_1_scl_changed();
int get_i2c_1_scl();
void set_i2c_1_scl(int value);
void reset_i2c_1_enabled_changed();
bool is_i2c_1_enabled_changed();
int get_i2c_1_enabled();
void set_i2c_1_enabled(int value);
void reset_reboot_changed();
bool is_reboot_changed();
int get_reboot();
void set_reboot(int value);

/*
 * [/GENERATED]
 */

#endif
