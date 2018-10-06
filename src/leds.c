#include "leds.h"

void led_toggle(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
