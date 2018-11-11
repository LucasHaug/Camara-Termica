#ifndef __SENSORS_H__
#define __SENSORS_H__

// Number of ADC channels for the temperature sensors
#define T_ADC_CHANNELS 2

#define ADC_BUFFER_SIZE (128 * T_ADC_CHANNELS)

/**
 * Public Types
 */

/**
 * @brief Sensors order
 */

typedef enum sensors_order {
    INT_SENSOR,
    EXT_SENSOR,
} sensors_order_t;

/**
 * Public Variables
 */
extern uint32_t temperature[T_ADC_CHANNELS];

void sensors_init(void);

float calibrated_reading(sensors_order_t sensor);

#endif  // __SENSORS_H__
