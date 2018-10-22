#include "leds.h"
#include "gpio.h"

//@ Mudar para psicar o led da placa e os leds da camara
void leds_state(leds_state_t state) {
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
