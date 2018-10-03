/**
 * @file main.c
 *
 * @brief Main function
 */

#include "mcu.h"
#include "temp_sensors.h"
#include "adc.h"
#include "dma.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/
#define LED_TOGGLE_DELAY_MS 1500

/*****************************************
 * Main Function
 *****************************************/
int main(void) {
    mcu_init();

    for (;;) {
        led_toggle();
        mcu_sleep(LED_TOGGLE_DELAY_MS);
    }
}
