#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <driver/gpio.h>
#include "config.h"

// Function to initialize the LED
void led_init(gpio_num_t pin);

// Turn on the LED
void led_on(gpio_num_t pin);

// Turn off the LED
void led_off(gpio_num_t pin);

#endif //LED_H