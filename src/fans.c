#include <stdbool.h>

#include "fans.h"
#include "gpio.h"
#include "tim.h"
#include "stm32f0xx_hal_tim.h"

bool fan_on = false;

void fans_init() {
    MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
}

void turn_fan_on() {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000);
}

void turn_fan_off() {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0000);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_13 && fan_on == false) {
        turn_fan_on();
    }
    if (GPIO_Pin == GPIO_PIN_13 && fan_on == true) {
        turn_fan_off();
    }
    fan_on = !fan_on;
}
