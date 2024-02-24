#ifndef WIFI_STA_H
#define WIFI_STA_H

#include <esp_err.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

// Event Bits
#define WIFI_SCANNING_BIT       BIT0
#define WIFI_FOUND_BIT          BIT1
#define WIFI_NOT_FOUND_BIT      BIT2

// Function prototypes
esp_err_t wifi_init_sta();
void wifi_scan_task(void* pvParameters); 
void start_wifi_scan();
void stop_wifi_scan();
EventGroupHandle_t get_scan_event_group();

#endif
