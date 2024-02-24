#include "wifi/sta.h"
#include "misc/led.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

static const char *TAG = "WIFI_STA";
static const int SCAN_INTERVAL_MS = 10000;  

static bool scan_running = false; 
static EventGroupHandle_t wifi_scan_event_group;

static void wifi_scan_callback(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_SCAN_DONE) {
        // clear all bits
        xEventGroupClearBits(wifi_scan_event_group, WIFI_SCANNING_BIT | WIFI_FOUND_BIT | WIFI_NOT_FOUND_BIT);

        uint16_t ap_count = 0;
        esp_wifi_scan_get_ap_num(&ap_count);
        if (ap_count == 0) {
            xEventGroupSetBits(wifi_scan_event_group, WIFI_NOT_FOUND_BIT);
            return;
        }

        wifi_ap_record_t *ap_info = (wifi_ap_record_t*)malloc(sizeof(wifi_ap_record_t) * ap_count);
        bool found = false;
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_info));

        for (int i = 0; i < ap_count; i++) {
            if (strcmp((char*)ap_info[i].ssid, EXAMPLE_ESP_WIFI_SSID) == 0) {
                found = true;
                break; // No need to continue searching
            }
        }

        free(ap_info);

        //set not found bit
        if (found) {
            xEventGroupSetBits(wifi_scan_event_group, WIFI_FOUND_BIT);
        } else {
            xEventGroupSetBits(wifi_scan_event_group, WIFI_NOT_FOUND_BIT);
        }

    }
}

esp_err_t wifi_init_sta() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_scan_callback,
                                                        NULL,
                                                        NULL));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    return ESP_OK;
}

void start_wifi_scan() {
    if (scan_running) return; 

    wifi_scan_event_group = xEventGroupCreate();

    ESP_LOGI(TAG, "Starting WiFi task");

    xTaskCreate(&wifi_scan_task, "wifi_scan_task", 2048, NULL, 5, NULL);
    scan_running = true;
}

void wifi_scan_task(void* pvParameters) { 
    ESP_LOGI(TAG, "WiFi scan task started");
    while (scan_running) {
        xEventGroupSetBits(wifi_scan_event_group, WIFI_SCANNING_BIT); 

        wifi_scan_config_t scan_config = {
            .show_hidden = true
        };
        ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

        vTaskDelay(pdMS_TO_TICKS(SCAN_INTERVAL_MS));
    }

    vTaskDelete(NULL); 
}

void stop_wifi_scan() {
    scan_running = false;
}

EventGroupHandle_t get_scan_event_group() {
    return wifi_scan_event_group;
}


