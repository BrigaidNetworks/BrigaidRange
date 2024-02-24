#include "sound/beep.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "config.h"

// Musical Notes (array can potentially be moved to beep.c if not needed elsewhere)
uint16_t notes[]  ={
	0,31,33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,87,93,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,
	233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,
	1760,1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186,4435,4699,4978};

void play_beep(piano_note_t note, uint16_t duration_ms) {
    // LEDC Timer Configuration
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = notes[note],                    
        .speed_mode = LEDC_HIGH_SPEED_MODE, 
        .timer_num = LEDC_TIMER_0,           
        .clk_cfg = LEDC_AUTO_CLK,             
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // LEDC Channel Configuration
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = PIEZO_OUTPUT_IO,
        .speed_mode     = LEDC_HIGH_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 4096, // Approx. 50% duty cycle 
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    // Start beep
    ESP_ERROR_CHECK(ledc_fade_func_install(0));
    ESP_ERROR_CHECK(ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, ledc_channel.duty));
    ESP_ERROR_CHECK(ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel));

    vTaskDelay(pdMS_TO_TICKS(duration_ms)); 

    // Stop beep
    ESP_ERROR_CHECK(ledc_stop(ledc_channel.speed_mode, ledc_channel.channel, 0));
}
