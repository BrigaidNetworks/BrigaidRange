#ifndef FIELDTEST_MANAGER_H
#define FIELDTEST_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @brief Initialize the Wi-Fi station mode for field testing.
 */
void wifi_sta_fieldtest();

/**
 * @brief Initialize the Wi-Fi softAP mode for field testing.
 */
void wifi_softap_fieldtest();

/**
 * @brief Select and start the appropriate field test mode.
 * 
 * @param mode The mode to select (0 for softAP, 1 for station).
 */
void manager_select(int mode);

#endif /* FIELDTEST_MANAGER_H */
