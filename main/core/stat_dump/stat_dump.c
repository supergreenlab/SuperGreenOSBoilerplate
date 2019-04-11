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

#include "stat_dump.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../log/log.h"
#include "../kv/kv.h"

#include "../include_modules.h"

#define MAX_KEY_SIZE 21

static void dump_heap_infos(const char *name, uint32_t cap) {
  multi_heap_info_t heap_infos;
  heap_caps_get_info(&heap_infos, cap);
  ESP_LOGI(SGO_LOG_METRIC, "@MALLOC_CAP_%s total_free_bytes=%d, total_allocated_bytes=%d", name, heap_infos.total_free_bytes, heap_infos.total_allocated_bytes);
  ESP_LOGI(SGO_LOG_METRIC, "@MALLOC_CAP_%s largest_free_block=%d, minimum_free_bytes=%d", name, heap_infos.largest_free_block, heap_infos.minimum_free_bytes);
  ESP_LOGI(SGO_LOG_METRIC, "@MALLOC_CAP_%s allocated_blocks=%d, free_blocks=%d, total_blocks=%d", name, heap_infos.allocated_blocks, heap_infos.free_blocks, heap_infos.total_blocks);
}

static void stat_dump_task(void *param) {
  int counter = 0;
  //wait_connected();
  vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
  //uint32_t ulTotalRunTime, ulStatsAsPercentage;
  while(1) {
    dump_heap_infos("32BIT", MALLOC_CAP_32BIT);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("8BIT", MALLOC_CAP_8BIT);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("DMA", MALLOC_CAP_DMA);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("PID2", MALLOC_CAP_PID2);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("PID3", MALLOC_CAP_PID3);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("PID4", MALLOC_CAP_PID4);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("PID5", MALLOC_CAP_PID5);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("PID6", MALLOC_CAP_PID6);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("PID7", MALLOC_CAP_PID7);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("SPIRAM", MALLOC_CAP_SPIRAM);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("INTERNAL", MALLOC_CAP_INTERNAL);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("DEFAULT", MALLOC_CAP_DEFAULT);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    dump_heap_infos("INVALID", MALLOC_CAP_INVALID);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    ESP_LOGI(SGO_LOG_METRIC, "@HEAP free=%d, min=%d", esp_get_free_heap_size(), esp_get_minimum_free_heap_size());

    ESP_LOGI(SGO_LOG_METRIC, "@SYS n_tasks=%d", uxTaskGetNumberOfTasks());
    /* int n_tasks = uxTaskGetNumberOfTasks();
    TaskStatus_t *statuses = malloc(n_tasks * sizeof(TaskStatus_t));
    if (statuses) {
      uxTaskGetSystemState(statuses, n_tasks, &ulTotalRunTime);
      ulTotalRunTime /= 100UL;
      for (int i = 0; i < n_tasks; ++i) {
        ESP_LOGI(SGO_LOG_METRIC, "@%s stack_left=%d", statuses[i].pcTaskName, statuses[i].usStackHighWaterMark);
        if (ulTotalRunTime != 0) {
          ulStatsAsPercentage = statuses[i].ulRunTimeCounter / ulTotalRunTime;
          ESP_LOGI(SGO_LOG_METRIC, "@%s task_counter=%d, task_percent=%d", statuses[i].pcTaskName, statuses[i].ulRunTimeCounter, ulStatsAsPercentage);
        }
      }
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      free(statuses);
    }*/

    /*
     * [GENERATED]
     */

    int value;
    char str[MAX_KVALUE_SIZE] = {0};
    if ((counter % 20) == 0 || is_wifi_status_changed()) {
      reset_wifi_status_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ssid_changed()) {
      get_wifi_ssid(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_SSID", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_wifi_ssid_changed();
    }
    if ((counter % 20) == 0 || is_wifi_password_changed()) {
      get_wifi_password(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_PASSWORD", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_wifi_password_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ap_ssid_changed()) {
      get_wifi_ap_ssid(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_AP_SSID", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_wifi_ap_ssid_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ap_password_changed()) {
      get_wifi_ap_password(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_AP_PASSWORD", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_wifi_ap_password_changed();
    }
    if ((counter % 20) == 0 || is_mdns_domain_changed()) {
      get_mdns_domain(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "MDNS_DOMAIN", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_mdns_domain_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ip_changed()) {
      get_wifi_ip(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_IP", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_wifi_ip_changed();
    }
    if ((counter % 20) == 0 || is_time_changed()) {
      value = get_time();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIME", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_time_changed();
    }
    if ((counter % 20) == 0 || is_n_restarts_changed()) {
      value = get_n_restarts();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "N_RESTARTS", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_n_restarts_changed();
    }
    if ((counter % 20) == 0 || is_ota_timestamp_changed()) {
      value = get_ota_timestamp();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OTA_TIMESTAMP", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_ota_timestamp_changed();
    }
    if ((counter % 20) == 0 || is_ota_server_ip_changed()) {
      get_ota_server_ip(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_IP", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_ota_server_ip_changed();
    }
    if ((counter % 20) == 0 || is_ota_server_hostname_changed()) {
      get_ota_server_hostname(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_HOSTNAME", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_ota_server_hostname_changed();
    }
    if ((counter % 20) == 0 || is_ota_server_port_changed()) {
      get_ota_server_port(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_PORT", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_ota_server_port_changed();
    }
    if ((counter % 20) == 0 || is_ota_basedir_changed()) {
      get_ota_basedir(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_BASEDIR", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_ota_basedir_changed();
    }
    if ((counter % 20) == 0 || is_ota_status_changed()) {
      reset_ota_status_changed();
    }
    if ((counter % 20) == 0 || is_broker_url_changed()) {
      get_broker_url(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_URL", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_broker_url_changed();
    }
    if ((counter % 20) == 0 || is_broker_channel_changed()) {
      get_broker_channel(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_CHANNEL", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_broker_channel_changed();
    }
    if ((counter % 20) == 0 || is_broker_clientid_changed()) {
      get_broker_clientid(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_CLIENTID", str);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_broker_clientid_changed();
    }
    if ((counter % 20) == 0 || is_i2c_0_sda_changed()) {
      value = get_i2c_0_sda();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_0_SDA", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_i2c_0_sda_changed();
    }
    if ((counter % 20) == 0 || is_i2c_0_scl_changed()) {
      value = get_i2c_0_scl();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_0_SCL", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_i2c_0_scl_changed();
    }
    if ((counter % 20) == 0 || is_i2c_0_enabled_changed()) {
      value = get_i2c_0_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_0_ENABLED", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_i2c_0_enabled_changed();
    }
    if ((counter % 20) == 0 || is_i2c_1_sda_changed()) {
      value = get_i2c_1_sda();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_1_SDA", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_i2c_1_sda_changed();
    }
    if ((counter % 20) == 0 || is_i2c_1_scl_changed()) {
      value = get_i2c_1_scl();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_1_SCL", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_i2c_1_scl_changed();
    }
    if ((counter % 20) == 0 || is_i2c_1_enabled_changed()) {
      value = get_i2c_1_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_1_ENABLED", value);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      reset_i2c_1_enabled_changed();
    }
    if ((counter % 20) == 0 || is_reboot_changed()) {
      reset_reboot_changed();
    }

    vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
    ++counter;

    /*
     * [/GENERATED]
     */
  }
}

void init_stat_dump_queues() {
}

void init_stat_dump() {
  ESP_LOGI(SGO_LOG_EVENT, "@SYS reset_reason=%d", esp_reset_reason());
  xTaskCreate(stat_dump_task, "STAT_DUMP", 4096, NULL, 10, NULL);
}
