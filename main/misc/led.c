#include "misc/led.h"
#include <string.h>
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "rom/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "config.h"

void led_init(gpio_num_t pin) {
    //set direction, mode, etc.
    gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, 0);
}

void led_on(gpio_num_t pin) {
    gpio_set_level(pin, 1);
}
    
void led_off(gpio_num_t pin) {
    gpio_set_level(pin, 0);
}