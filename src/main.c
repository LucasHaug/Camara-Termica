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

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    mcu_sleep(1000);

    char data[128];

    for (;;) {
        control_led_state(TOGGLE);
        // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
        // mcu_sleep_us(50);

        uint8_t temp = dht11_get_temperature();
        uint8_t humi = dht11_get_humidity();

        // lamps_state(OFF);
        // while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
        //     ;
        // lamps_state(ON);
        // pi_action();

        sprintf(data, "d,%.2f,%.2f,%u,%u,f\r\n", calibrated_reading(EXT_SENSOR), calibrated_reading(INT_SENSOR), temp,
                humi);
        mcu_printf(data);

        mcu_sleep(2000);
    }
}
