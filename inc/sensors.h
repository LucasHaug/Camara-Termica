#ifndef __SENSORS_H__
#define __SENSORS_H__


// Number of ADC channels for the temperature sensors
#define T_ADC_CHANNELS 2
// Number of ADC channels for the humidity sensors
//@ Mudar para adicionar o senosr de umidade + setar pino PA4
#define H_ADC_CHANNELS 1
#define ADC_BUFFER_SIZE (128 * (T_ADC_CHANNELS + H_ADC_CHANNELS))

/**
 * Public Variables
 */
extern uint32_t temperature[T_ADC_CHANNELS];
//@ Mudar para adicionar o senosr de umidade + setar pino PA4
extern uint64_t humidity[H_ADC_CHANNELS];

void sensors_init(void);

void calibrate_sensors(float low_temp_ref, float high_temp_ref);

#endif  // __SENSORS_H__
