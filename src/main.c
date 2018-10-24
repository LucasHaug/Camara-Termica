#include "gpio.h"

#include "fans.h"
#include "leds.h"
#include "mcu.h"
#include "control.h"

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
        control_led_state(OFF);
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
            ;
        control_led_state(ON);
        pi_action();
    }
}
