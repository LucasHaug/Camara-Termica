/**
 * @file leds.c
 *
 * @brief Functions to change the state of the control
 *        led of the board and of the lamps of leds.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#include "leds.h"
#include "gpio.h"

void lamps_state(leds_state_t state) {
    switch (state) {
        case ON:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, SET);
            break;
        case OFF:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
            break;
        case TOGGLE:
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
            break;
    }
}

void control_led_state(leds_state_t state) {
    switch (state) {
        case ON:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
            break;
        case OFF:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
            break;
        case TOGGLE:
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            break;
    }
}

// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//     if (GPIO_Pin == GPIO_PIN_13) {
//         lamps_state(ON);
//     }
// }
