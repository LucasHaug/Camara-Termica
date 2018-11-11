#include <string.h>

#include "gpio.h"
#include "usart.h"

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

    char send_data[256];

    // uint8_t temp;
    // uint8_t hum;

    for (;;) {
        // temp = dht11_get_temperature();
        // hum = dht11_get_humidity();

        control_led_state(OFF);
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
            ;
        control_led_state(ON);
        pi_action();



        // snprintf(send_data, sizeof(send_data), "T1: %ldoC\r\nT2: %ldoC\r\n\r\n", temperature[EXT_SENSOR], temperature[INT_SENSOR]);
        // HAL_UART_Transmit(&huart2, (uint8_t*) send_data, strlen(send_data), 100);

        mcu_sleep(3000);
    }
}
// sudo screen /dev/ttyACM0 115200
