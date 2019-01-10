/*
 * =====================================================================================
 *
 *       Filename:  stat_dump.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/2018 11:27:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
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

static void stat_dump_task(void *param) {
  wait_connected();
  vTaskDelay(60000 / portTICK_PERIOD_MS);
  int n_tasks = uxTaskGetNumberOfTasks();
  uint32_t ulTotalRunTime, ulStatsAsPercentage;
  TaskStatus_t *statuses = malloc(n_tasks * sizeof(TaskStatus_t));
  while(1) {
    int nn_tasks = uxTaskGetNumberOfTasks();
    if (n_tasks != nn_tasks) {
      free(statuses);
      n_tasks = nn_tasks;
      statuses = malloc(n_tasks * sizeof(TaskStatus_t));
    }
    uxTaskGetSystemState(statuses, n_tasks, &ulTotalRunTime);
    ulTotalRunTime /= 100UL;
    if (ulTotalRunTime == 0) continue;

    for (int i = 0; i < n_tasks; ++i) {
      ulStatsAsPercentage = statuses[i].ulRunTimeCounter / ulTotalRunTime;
      ESP_LOGI(SGO_LOG_METRIC, "@%s stack_left=%d, task_counter=%d, task_percent=%d", statuses[i].pcTaskName, statuses[i].usStackHighWaterMark, statuses[i].ulRunTimeCounter, ulStatsAsPercentage);
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    /*
     * [GENERATED]
     */

    int value;
    char str[MAX_KVALUE_SIZE] = {0};
    getstr(WIFI_SSID, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_SSID", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(WIFI_PASSWORD, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_PASSWORD", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(TIME);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIME", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(OTA_TIMESTAMP);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OTA_TIMESTAMP", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_SERVER_IP, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_IP", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_SERVER_HOSTNAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_HOSTNAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_SERVER_PORT, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_PORT", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_VERSION_FILENAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_VERSION_FILENAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_FILENAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_FILENAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(BROKER_URL, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_URL", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(I2C_SDA);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_SDA", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(I2C_SCL);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_SCL", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);

    vTaskDelay(60000 / portTICK_PERIOD_MS);

    /*
     * [/GENERATED]
     */
  }
}

void init_stat_dump_queues() {
}

void init_stat_dump() {
  xTaskCreate(stat_dump_task, "STAT_DUMP", 3072, NULL, 10, NULL);
}
