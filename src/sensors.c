#include "adc.h"
#include "dma.h"

#include "sensors.h"

#define OLD_VALUE_WEIGHT 3
#define NEW_VALUE_WEIGHT 1

//@ calibration indexs
static float a = 0;
static float b = 0;

uint32_t temperature[T_ADC_CHANNELS] = {0};
//@ Mudar para adicionar o senosr de umidade + setar pino PA4
// uint32_t uint32_t humidity[H_ADC_CHANNELS] = {0};

uint32_t adc_buffer[ADC_BUFFER_SIZE] = {0};

void sensors_init(void) {
    MX_DMA_Init();
    MX_ADC_Init();

    HAL_ADC_Start_DMA(&hadc, adc_buffer, ADC_BUFFER_SIZE);
}

void calibrate_sensors(float low_temp_ref, float high_temp_ref) {
    float low_reading;
    float high_reading;
    float low_diff;
    float high_diff;
    return;

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    uint32_t val[T_ADC_CHANNELS + H_ADC_CHANNELS] = {0};

    for (int i = 0; i < ADC_BUFFER_SIZE / (T_ADC_CHANNELS + H_ADC_CHANNELS); i++) {
        for (int j = 0; j < (T_ADC_CHANNELS + H_ADC_CHANNELS); j++) {
            val[j] += adc_buffer[(T_ADC_CHANNELS + H_ADC_CHANNELS) * i + j];
        }
    }

    for (int i = 0; i < (T_ADC_CHANNELS + H_ADC_CHANNELS); i++) {
        val[i] /= ADC_BUFFER_SIZE / (T_ADC_CHANNELS + H_ADC_CHANNELS);
    }

    for (int i = 0; i < T_ADC_CHANNELS; i++) {
        temperature[i] = (NEW_VALUE_WEIGHT * val[i] + OLD_VALUE_WEIGHT * temperature[i]) /
                         (NEW_VALUE_WEIGHT + OLD_VALUE_WEIGHT);
    }
    //@ Mudar para adicionar o senosr de umidade + setar pino PA4
    // humidity = val[T_ADC_CHANNELS - 1];
}
