#include <string.h>

#include "gpio.h"

#include "control.h"
#include "dht11.h"
#include "leds.h"
#include "mcu.h"
#include "sensors.h"

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

