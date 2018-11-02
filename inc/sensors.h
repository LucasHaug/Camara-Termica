#ifndef __SENSORS_H__
#define __SENSORS_H__


// Number of ADC channels for the temperature sensors
#define T_ADC_CHANNELS 2

#define ADC_BUFFER_SIZE (128 * T_ADC_CHANNELS )

/**
 * Public Variables
 */
extern uint32_t temperature[T_ADC_CHANNELS];

void sensors_init(void);

void calibrate_sensors(float low_temp_ref, float high_temp_ref);

#endif  // __SENSORS_H__
