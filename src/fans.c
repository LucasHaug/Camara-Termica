#include <stdbool.h>
#include <stdint.h>

#include "fans.h"
#include "gpio.h"
#include "tim.h"
#include "stm32f0xx_hal_tim.h"

bool fan_on = false;

void fans_init() {
    MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

    // primeira ponte H
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

    // segunda ponte H - ver se é necessário, se pode usar o mesmo sinal do uC da primeira ponte
    // HAL_GPIO_WritePin(GPIOX, GPIO_PIN_X, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOX, GPIO_PIN_X, GPIO_PIN_RESET);
}

void fan_speed(fan_t fan, uint16_t speed) {
    switch (fan) {
        case TOP_FAN:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
            break;
        case BOTTOM_FAN:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
            break;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_13 && fan_on == false) {
        fan_speed(TOP_FAN, 1000);
        fan_speed(BOTTOM_FAN, 0);
    }
    if (GPIO_Pin == GPIO_PIN_13 && fan_on == true) {
        fan_speed(TOP_FAN, 0);
        fan_speed(BOTTOM_FAN, 1000);
    }
    fan_on = !fan_on;
}
