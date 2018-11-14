/**
 * @file dht11.c
 *
 * @brief Functions to read the DHT11 sensor.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 11/2018
 */

#ifdef F3_SERIE

#include <string.h>

#include "dht11.h"
#include "mcu.h"

#ifdef F0_SERIE
#include "stm32f0xx_hal.h"
#else
#include "stm32f3xx_hal.h"
#endif

#define MIN_READ_TIME 2000

static GPIO_InitTypeDef GPIO_InitStruct;
static uint32_t last_read_time = -MIN_READ_TIME;
static uint8_t last_data[5] = {0};

static void set_gpio_output(void);
static void set_gpio_input(void);
static void dht11_read(void);
static uint32_t get_pulse(uint8_t val);

uint8_t dht11_get_temperature(void) {
    dht11_read();
    return last_data[2];
}

uint8_t dht11_get_humidity(void) {
    dht11_read();
    return last_data[0];
}

void set_gpio_output(void) {
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void set_gpio_input(void) {
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint32_t get_pulse(uint8_t val) {
    uint32_t cycles = 0;

    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == val) {
        cycles++;

        if (HAL_GetTick() - last_read_time >= 1000) {
            return 0;
        }
    }

    return cycles;
}

void dht11_read(void) {
    if (HAL_GetTick() - last_read_time < MIN_READ_TIME) {
        return;
    }

    last_read_time = HAL_GetTick();

    uint8_t read_data[5] = {0};

    set_gpio_input();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
    mcu_sleep(250);

    set_gpio_output();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
    mcu_sleep(20);

    HAL_NVIC_DisableIRQ(ADC1_2_IRQn);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
    mcu_sleep_us(40);

    set_gpio_input();
    mcu_sleep_us(10);

    get_pulse(0);
    get_pulse(1);

    uint32_t cycles[80];
    for (int i = 0; i < 80; i += 2) {
        cycles[i] = get_pulse(0);

        if (HAL_GetTick() - last_read_time >= 1000) {
            HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
            return;
        }

        cycles[i + 1] = get_pulse(1);

        if (HAL_GetTick() - last_read_time >= 1000) {
            HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
            return;
        }
    }

    for (int i = 0; i < 40; i++) {
        uint32_t lowCycles = cycles[2 * i];
        uint32_t highCycles = cycles[2 * i + 1];
        read_data[i / 8] <<= 1;
        if (highCycles > lowCycles) {
            read_data[i / 8] |= 1;
        }
    }

    if (read_data[4] != (read_data[0] + read_data[1] + read_data[2] + read_data[3])) {
        HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
        return;
    }

    memcpy(last_data, read_data, sizeof(last_data));
    HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
}

#endif // F3_SERIE
