/**
 * @file main.c
 *
 * @brief Main function.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#include "gpio.h"

#include "control.h"
#include "leds.h"
#include "mcu.h"


/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    mcu_sleep(1000);

    for (;;) {
        lamps_state(OFF);
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
            ;
        lamps_state(ON);
        pi_action();

        mcu_sleep(3000);
    }
}
