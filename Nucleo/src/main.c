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
#include "dht11.h"
#include "leds.h"
#include "mcu.h"
#include "sensors.h"
#include "serial_rx.h"

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    mcu_sleep(1000);

    for (;;) {
        control_led_state(ON);

        lamps_state(OFF);
        while (turn_ON == 0)
            ;
        lamps_state(ON);
        pi_action();

        control_led_state(OFF);

        mcu_sleep(2000);
    }
}
