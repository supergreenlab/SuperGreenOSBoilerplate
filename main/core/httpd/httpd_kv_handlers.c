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

#include <stdlib.h>
#include <string.h>

#include "../kv/kv.h"
#include "../kv/kv_helpers_internal.h"
#include "httpd_kv_handlers.h"
#include "../include_modules.h"

const kvi_handler kvi_handlers[] = {
/*
* [GENERATED]
*/
  
  {
    .name = "WIFI_STATUS",
    .handler = NULL,
    .getter = get_wifi_status,
  },
  {
    .name = "TIME",
    .handler = internal_set_time,
    .getter = get_time,
  },
  {
    .name = "N_RESTARTS",
    .handler = NULL,
    .getter = get_n_restarts,
  },
  {
    .name = "OTA_TIMESTAMP",
    .handler = internal_set_ota_timestamp,
    .getter = get_ota_timestamp,
  },
  {
    .name = "I2C_0_SDA",
    .handler = internal_set_i2c_0_sda,
    .getter = get_i2c_0_sda,
  },
  {
    .name = "I2C_0_SCL",
    .handler = internal_set_i2c_0_scl,
    .getter = get_i2c_0_scl,
  },
  {
    .name = "I2C_0_ENABLED",
    .handler = internal_set_i2c_0_enabled,
    .getter = get_i2c_0_enabled,
  },
  {
    .name = "I2C_1_SDA",
    .handler = internal_set_i2c_1_sda,
    .getter = get_i2c_1_sda,
  },
  {
    .name = "I2C_1_SCL",
    .handler = internal_set_i2c_1_scl,
    .getter = get_i2c_1_scl,
  },
  {
    .name = "I2C_1_ENABLED",
    .handler = internal_set_i2c_1_enabled,
    .getter = get_i2c_1_enabled,
  },
  {
    .name = "REBOOT",
    .handler = internal_set_reboot,
    .getter = get_reboot,
  },

/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .handler = NULL,
  },
};

const kvi_handler *get_kvi_handler(const char *name) {
  for (int i = 0; kvi_handlers[i].name != NULL; ++i) {
    if (strcmp(kvi_handlers[i].name, name) == 0) {
      return &kvi_handlers[i];
    }
  }
  return NULL;
}

const kvs_handler kvs_handlers[] = {
/*
* [GENERATED]
*/

  {
    .name = "WIFI_SSID",
    .handler = internal_set_wifi_ssid,
    .getter = get_wifi_ssid,
  },
  {
    .name = "WIFI_PASSWORD",
    .handler = internal_set_wifi_password,
    .getter = get_wifi_password,
  },
  {
    .name = "WIFI_AP_SSID",
    .handler = internal_set_wifi_ap_ssid,
    .getter = get_wifi_ap_ssid,
  },
  {
    .name = "WIFI_AP_PASSWORD",
    .handler = internal_set_wifi_ap_password,
    .getter = get_wifi_ap_password,
  },
  {
    .name = "MDNS_DOMAIN",
    .handler = internal_set_mdns_domain,
    .getter = get_mdns_domain,
  },
  {
    .name = "WIFI_IP",
    .handler = NULL,
    .getter = get_wifi_ip,
  },
  {
    .name = "OTA_SERVER_IP",
    .handler = internal_set_ota_server_ip,
    .getter = get_ota_server_ip,
  },
  {
    .name = "OTA_SERVER_HOSTNAME",
    .handler = internal_set_ota_server_hostname,
    .getter = get_ota_server_hostname,
  },
  {
    .name = "OTA_SERVER_PORT",
    .handler = internal_set_ota_server_port,
    .getter = get_ota_server_port,
  },
  {
    .name = "OTA_BASEDIR",
    .handler = internal_set_ota_basedir,
    .getter = get_ota_basedir,
  },
  {
    .name = "BROKER_URL",
    .handler = internal_set_broker_url,
    .getter = get_broker_url,
  },
  {
    .name = "BROKER_CHANNEL",
    .handler = internal_set_broker_channel,
    .getter = get_broker_channel,
  },
  {
    .name = "BROKER_CLIENTID",
    .handler = internal_set_broker_clientid,
    .getter = get_broker_clientid,
  },

/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .handler = NULL,
  }
};

const kvs_handler *get_kvs_handler(const char *name) {
  for (int i = 0; kvs_handlers[i].name != NULL; ++i) {
    if (strcmp(kvs_handlers[i].name, name) == 0) {
      return &kvs_handlers[i];
    }
  }
  return NULL;
}
