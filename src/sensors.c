#include <string.h>

#include "adc.h"
#include "dma.h"

#include "mcu.h"
#include "sensors.h"
#include "utils.h"

#define OLD_VALUE_WEIGHT 3
#define NEW_VALUE_WEIGHT 1

uint32_t temperature[T_ADC_CHANNELS] = {0};

uint32_t adc_buffer[ADC_BUFFER_SIZE] = {0};

void sensors_init(void) {
    MX_DMA_Init();
    MX_ADC_Init();

    HAL_ADC_Start_DMA(&hadc, adc_buffer, ADC_BUFFER_SIZE);
}

float calibrated_reading(sensors_order_t sensor) {
    float current_temperature;

    switch (sensor) {
        case INT_SENSOR:
            // current_temperature = map(temperature[INT_SENSOR] / 100.0, 0, 3.3, 0, 5.0) * 100;
            current_temperature = temperature[INT_SENSOR];
            break;
        case EXT_SENSOR:
            // current_temperature = map(temperature[EXT_SENSOR] / 100.0, 0, 3.3, 0, 5.0) * 100;
            current_temperature = temperature[EXT_SENSOR];
            current_temperature = current_temperature + 20;
            break;
    }

    return current_temperature / 10;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    uint32_t val[T_ADC_CHANNELS] = {0};

    for (int i = 0; i < ADC_BUFFER_SIZE / T_ADC_CHANNELS; i++) {
        for (int j = 0; j < T_ADC_CHANNELS; j++) {
            val[j] += adc_buffer[T_ADC_CHANNELS * i + j];
        }
    }

    for (int i = 0; i < T_ADC_CHANNELS; i++) {
        val[i] /= ADC_BUFFER_SIZE / T_ADC_CHANNELS;
    }

    for (int i = 0; i < T_ADC_CHANNELS; i++) {
        temperature[i] =
            (NEW_VALUE_WEIGHT * val[i] + OLD_VALUE_WEIGHT * temperature[i]) / (NEW_VALUE_WEIGHT + OLD_VALUE_WEIGHT);
    }
}
