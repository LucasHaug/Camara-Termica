#include "power_resistors.h"

#include "gpio.h"

void resistors_state(state_t state) {
    switch (state) {
        case ON:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
            break;
        case OFF:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
            break;
    }
}
