#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "config.h"

#include "fieldtest/manager.h"
#include "sound/beep.h"
#include "misc/led.h"

static const char *TAG = "MAIN";

void app_main(void) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
	
	led_init(ONBOARD_LED_IO);

    // Play startup beep
    play_beep(NOTE_C4, BEEP_DURATION_MS);
    ESP_LOGI(TAG, "Startup beep played"); 

    manager_select(FIELDTEST_TYPE);
}
