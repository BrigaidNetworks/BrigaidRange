#include "fieldtest/manager.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "wifi/softap.h"
#include "wifi/sta.h"
#include "misc/led.h"

const char *TAG = "FIELDTEST";

void blink(int time) {
	int count = time / 200;
	for (int i = 0; i < count; i++) {
		led_on(ONBOARD_LED_IO);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		led_off(ONBOARD_LED_IO);
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

void wifi_sta_fieldtest() {
    wifi_init_sta();
	start_wifi_scan(); 

	while (true) {
        EventBits_t bits = xEventGroupWaitBits(get_scan_event_group(), 
                                               WIFI_SCANNING_BIT | WIFI_FOUND_BIT | WIFI_NOT_FOUND_BIT,
                                               pdFALSE,  // Clear bits on exit
                                               pdFALSE,   // Wait for any of the bits
                                               portMAX_DELAY);

		// print bits (long unsigned int)
		ESP_LOGI(TAG, "bits: %lu", bits);

        if (bits & WIFI_SCANNING_BIT) {
            // WiFi scan in progress...
            // You could have an indicator LED or a status message here
			ESP_LOGI(TAG, "scanning...");
            blink(1000);
        } else if (bits & WIFI_FOUND_BIT) {
            // WiFi Network Found
            led_on(ONBOARD_LED_IO);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
        } else if (bits & WIFI_NOT_FOUND_BIT) {
            // WiFi Network Not Found
            led_off(ONBOARD_LED_IO);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void wifi_softap_fieldtest() {
    wifi_init_softap();
    while (true) {
        // Blink the onboard LED
        blink(1000);
    }
}

void manager_select(int mode) {
    switch (mode) {
        case 0:
            wifi_softap_fieldtest();
            break;
        case 1:
            wifi_sta_fieldtest();
            break;
        default:
            ESP_LOGE(TAG, "Invalid mode: %d", mode);
            break;
    }
}