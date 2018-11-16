/**
 * @file fans.c
 *
 * @brief Functions for initializing and setting fan's speeds.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#include <stdbool.h>
#include <stdint.h>

#include "fans.h"
#include "mcu.h"
#include "tim.h"

#ifdef F0_SERIE
#include "stm32f0xx_hal_tim.h"
#else
#include "stm32f3xx_hal_tim.h"
#endif

void fans_init(void) {
    MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
}

void set_fan(fan_t fan, uint16_t speed) {
    switch (fan) {
        case TOP_FAN:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
            break;
        case BOTTOM_FAN:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
            break;
    }
}
