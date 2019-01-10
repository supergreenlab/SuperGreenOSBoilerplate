/*
 * =====================================================================================
 *
 *       Filename:  httpd_kv_handlers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/14/2018 11:24:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "../kv/kv_helpers_internal.h"
#include "httpd_kv_handlers.h"
#include "../include_modules.h"

const kvi_handler kvi_handlers[] = {
/*
* [GENERATED]
*/
  
  {
    .name = "TIME",
    .nvs_key = NULL,
    .nvs_key = "TIME",
    .handler = internal_set_time,
  },
  {
    .name = "OTA_TIMESTAMP",
    .nvs_key = NULL,
    .nvs_key = "OTA_TMSTP",
    .handler = internal_set_ota_timestamp,
  },
  {
    .name = "I2C_SDA",
    .nvs_key = NULL,
    .nvs_key = "I2C_SDA",
    .handler = internal_set_i2c_sda,
  },
  {
    .name = "I2C_SCL",
    .nvs_key = NULL,
    .nvs_key = "I2C_SCL",
    .handler = internal_set_i2c_scl,
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
    .nvs_key = NULL,
    .nvs_key = "WSSID",
    .handler = internal_set_wifi_ssid,
  },
  {
    .name = "WIFI_PASS",
    .nvs_key = NULL,
    .nvs_key = "WPASS",
    .handler = internal_set_wifi_password,
  },
  {
    .name = "OTA_SERVER_IP",
    .nvs_key = NULL,
    .nvs_key = "OTA_SRV_IP",
    .handler = internal_set_ota_server_ip,
  },
  {
    .name = "OTA_SERVER_HOSTNAME",
    .nvs_key = NULL,
    .nvs_key = "OTA_SRV_HN",
    .handler = internal_set_ota_server_hostname,
  },
  {
    .name = "OTA_SERVER_PORT",
    .nvs_key = NULL,
    .nvs_key = "OTA_SRV_PRT",
    .handler = internal_set_ota_server_port,
  },
  {
    .name = "OTA_VERSION_FILENAME",
    .nvs_key = NULL,
    .nvs_key = "OTA_VR_FILE",
    .handler = internal_set_ota_version_filename,
  },
  {
    .name = "OTA_FILENAME",
    .nvs_key = NULL,
    .nvs_key = "OTA_FILE",
    .handler = internal_set_ota_filename,
  },
  {
    .name = "OTA",
    .nvs_key = NULL,
    .nvs_key = "OTA_SRV_IP",
    .handler = internal_set_mqtt_broker_url,
  },
  {
    .name = "BROKER_URL",
    .nvs_key = NULL,
    .nvs_key = "BRKR_URL",
    .handler = internal_set_broker_url,
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
