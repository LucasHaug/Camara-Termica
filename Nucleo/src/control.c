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

#include "gpio.h"
#include "mcu.h"
#include "usart.h"

#ifdef F0_SERIE
#include "stm32f0xx_hal.h"
#else
#include "stm32f3xx_hal.h"
#endif

#include "control.h"
#include "dht11.h"
#include "fans.h"
#include "power_resistors.h"
#include "sensors.h"
#include "serial_rx.h"

/**
 * @brief Set point temperature in degrees Celsius.
 */
#define SETPOINT_TEMPERATURE_C 33

/**
 * @brief Serial comunication sending period in miliseconds.
 */
#define SENDING_PERIOD_MS 1000

/**
 * @brief Maximum temperature to consider a cold day in degrees Celsius.
 */
#define COLD_DAY_TEMPERATURE_C 25

/**
 * @brief Minimum temperature to consider a hot day in degrees Celsius.
 */
#define HOT_DAY_TEMPERATURE_C 29

/**
 * @bief Minumum error value for the power resisitors to turn on.
 */
static float resist_ON_min_error = 0.5;

static float action = 0;
static float last_action = 0;
static float error = 0;
static float last_error = 0;

static float current_time = 0;
static float last_time = 0;

/**
 * @brief pi control constants
 */
static float kp = 120;
static float ki = 9;

char send_data[256];
uint8_t temp;
int8_t humidity;
uint32_t time_aux = 0;

void pi_action(void) {
    for (;;) {
        float current_int_temperature = calibrated_reading(INT_SENSOR);
        float current_ext_temperature = calibrated_reading(EXT_SENSOR);

#ifdef F3_SERIE
        humidity = dht11_get_humidity();
#else
        /**
         * Atributes any invalid value;
         */
        humidity = -42;
#endif  // F3_SERIE

        current_time = HAL_GetTick() / 1000;
        error = SETPOINT_TEMPERATURE_C - current_int_temperature;
        action = last_action + kp * (error - last_error) + ki * (current_time - last_time) * error;
        last_time = current_time;

        /** Limit action value */
        if (action > 1000) {
            action = 1000;
        } else if (action < -1000) {
            action = -1000;
        }

        if (current_ext_temperature < COLD_DAY_TEMPERATURE_C) {
            resist_ON_min_error = 0;
        } else if (current_ext_temperature > HOT_DAY_TEMPERATURE_C) {
            resist_ON_min_error = 1;
        } else {
            resist_ON_min_error = 0.5;
        }

        if (action < 0 && current_ext_temperature < current_int_temperature) {
            set_fan(TOP_FAN, -action);
            set_fan(BOTTOM_FAN, 0);
            resistors_state(OFF);
        } else if (action > 0 && error > resist_ON_min_error) {
            resistors_state(ON);
            set_fan(TOP_FAN, 0);
            // set_fan(BOTTOM_FAN, action * 2 / 3);
        } else {
            set_fan(TOP_FAN, 0);
            set_fan(BOTTOM_FAN, 0);
            resistors_state(OFF);
        }

        last_error = error;
        last_action = action;

        /**
         * To see the serial data in the terminal, run
         * `sudo screen /dev/ttyACM0 115200`
         */
        if (HAL_GetTick() - time_aux > SENDING_PERIOD_MS) {
            uint8_t fan_on = action < 0;
            uint8_t heat_on = action > 0 && error > resist_ON_min_error;

            time_aux = HAL_GetTick();
            sprintf(send_data, "s,%.2f,%.2f,%d,%u,%u,e\r\n", current_int_temperature, current_ext_temperature, humidity,
                    fan_on, heat_on);
            mcu_printf(send_data);
        }

        if (turn_ON == 0) {
            sprintf(send_data, "stop,stop,stop,stop,stop,stop,stop\r\n");
            mcu_printf(send_data);
            break;
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_13) {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
            ;
        turn_ON = !turn_ON;
    }
}
