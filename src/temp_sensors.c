#include "adc.h"
#include "dma.h"

#include "temp_sensors.h"

u_int32_t temperature[ADC_CHANNELS] = { 0 };

u_int32_t adc_buffer[ADC_BUFFER_SIZE] = { 0 };

void temp_sensors_init() {
    MX_DMA_Init();
    MX_ADC_Init();

    HAL_ADC_Start_DMA(&hadc, adc_buffer, ADC_BUFFER_SIZE);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    u_int32_t val[ADC_CHANNELS] = { 0 };

    for (int i = 0; i < ADC_BUFFER_SIZE / ADC_CHANNELS; i++) {
        for (int j = 0; j < ADC_CHANNELS; j++) {
            val[j] += adc_buffer[ADC_CHANNELS * i + j];
        }
    }

    for (int i = 0; i < ADC_CHANNELS; i++) {
        val[i] /= ADC_BUFFER_SIZE / ADC_CHANNELS;
    }

    for (int i = 0; i < ADC_CHANNELS; i++) {
        temperature[i] = val[i];
    }
}