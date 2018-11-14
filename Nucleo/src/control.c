/**
 * @file control.c
 *
 * @brief PI algorithm.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#include <stdint.h>

#include "mcu.h"
#include "usart.h"

#ifdef F0_SERIE
#include "stm32f0xx_hal.h"
#else
#include "stm32f3xx_hal.h"
#endif

#include "control.h"
// #include "dht11.h"  //@
#include "fans.h"
#include "power_resistors.h"
#include "sensors.h"

#define SETPOINT_TEMPERATURE 33
#define NMAX 10

static float action = 0;
static float last_action = 0;
static float error = 0;
static float last_error = 0;

static float current_time = 0;
static float last_time = 0;

// pi control constants
static float kp = 120;
static float ki = 9;

// char send_data[256]; //@
// uint8_t temp; //@
// uint8_t hum; //@

void pi_action(void) {
    for (;;) {
        float current_int_temperature = calibrated_reading(INT_SENSOR);
        float current_ext_temperature = calibrated_reading(EXT_SENSOR);

        // temp = dht11_get_temperature();
        // hum = dht11_get_humidity();

        current_time = HAL_GetTick() / 1000;
        error = SETPOINT_TEMPERATURE - current_int_temperature;
        action = last_action + kp * (error - last_error) + ki * (current_time - last_time) * error;
        last_time = current_time;

        /** Limit action value */
        if (action > 1000) {
            action = 1000;
        } else if (action < -1000) {
            action = -1000;
        }

        if (action < 0 /* && current_ext_temperature < current_int_temperature //@ */) {
            set_fan(TOP_FAN, action);
            set_fan(BOTTOM_FAN, 0);
            resistors_state(OFF);
        } else if (action > 0) {
            if (error > 1) {
                resistors_state(ON);
            }
            set_fan(TOP_FAN, 0);
            // set_fan(BOTTOM_FAN, action * 2 / 3);
        } else {
            set_fan(TOP_FAN, 0);
            set_fan(BOTTOM_FAN, 0);
            resistors_state(OFF);
        }

        last_error = error;
        last_action = action;

        // snprintf(send_data, sizeof(send_data), "T1: %ldoC\r\nT2: %ldoC\r\n\r\n", temperature[EXT_SENSOR],
        // temperature[INT_SENSOR]); HAL_UART_Transmit(&huart2, (uint8_t*) send_data, strlen(send_data), 100);

        // sudo screen /dev/ttyACM0 115200
    }
}
