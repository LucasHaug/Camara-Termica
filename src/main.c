#include "fans.h"
#include "leds.h"
#include "mcu.h"

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
        leds_state(TOGGLE);
        mcu_sleep(LED_TOGGLE_DELAY_MS);
    }
}
