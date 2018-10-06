#include "mcu.h"
#include "fans.h"
#include "leds.h"

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
