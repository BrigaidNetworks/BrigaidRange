#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_WIFI_CHANNEL   CONFIG_ESP_WIFI_CHANNEL
#define EXAMPLE_MAX_STA_CONN       CONFIG_ESP_MAX_STA_CONN
#define TRANSMIT_POWER_20_DBM      80

// LED and Beep Configuration
#define BEEP_DURATION_MS        100 // Duration of the startup beep in milliseconds
#define PIEZO_OUTPUT_IO         GPIO_NUM_32 
#define ONBOARD_LED_IO          GPIO_NUM_2

// Demo Configuration
// Demo Type: 0 = WiFi SoftAP, 1 = WiFi Station, 2 = BLE Beacon, 3 = BLE Scanner
#define FIELDTEST_TYPE          CONFIG_FIELDTEST_TYPE


#endif // CONFIG_H