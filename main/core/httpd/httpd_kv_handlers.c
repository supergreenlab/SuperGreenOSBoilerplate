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
    .name = "I2C_SDA",
    .handler = internal_set_i2c_sda,
    .getter = get_i2c_sda,
  },
  {
    .name = "I2C_SCL",
    .handler = internal_set_i2c_scl,
    .getter = get_i2c_scl,
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
    .name = "OTA_VERSION_FILENAME",
    .handler = internal_set_ota_version_filename,
    .getter = get_ota_version_filename,
  },
  {
    .name = "OTA_FILENAME",
    .handler = internal_set_ota_filename,
    .getter = get_ota_filename,
  },
  {
    .name = "BROKER_URL",
    .handler = internal_set_broker_url,
    .getter = get_broker_url,
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
