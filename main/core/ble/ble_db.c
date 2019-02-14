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

#include "ble_db.h"

#include "string.h"

#include "../include_modules.h"
#include "../log/log.h"
#include "../ble/ble_utils.h"
#include "../kv/kv.h"
#include "../kv/kv_helpers_internal.h"


static const uint16_t GATTS_SERVICE_UUID      = 0x00FF;

const uint8_t WIFI_STATUS_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x5c};
const uint8_t WIFI_SSID_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x6c};
const uint8_t WIFI_PASSWORD_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x7c};
const uint8_t WIFI_IP_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x8c};
const uint8_t TIME_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};

const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] = {

  [IDX_SVC]    =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
    sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID), (uint8_t *)&GATTS_SERVICE_UUID}},

  /*
   * [GENERATED]
   */

    R_I_NOTIFIABLE_CHAR(WIFI_STATUS),
    RW_STR_CHAR(WIFI_SSID),
    RW_STR_NOTIFIABLE_CHAR(WIFI_PASSWORD),
    R_STR_NOTIFIABLE_CHAR(WIFI_IP),
    RW_I_NOTIFIABLE_CHAR(TIME),

  /*
   * [/GENERATED]
   */
};

void on_write(esp_ble_gatts_cb_param_t *param) {
  /*
   * [GENERATED]
   */
  
      if (param->write.handle == handle_table[IDX_VALUE(WIFI_SSID)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_wifi_ssid(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(WIFI_PASSWORD)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_wifi_password(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(TIME)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_time(value);
      }

  /*
   * [/GENERATED]
   */
}

void on_read(esp_ble_gatts_cb_param_t *param) {
}
