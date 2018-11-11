#include <stdint.h>

#include "stm32f0xx_hal.h"

#include "control.h"
#include "fans.h"
#include "power_resistors.h"
#include "sensors.h"

#define SETPOINT_TEMPERATURE 33
#define NMAX 10

static float action = 0;
static float last_action = 0;
static float error = 0;
static float last_error = 0;

static float current_time = 0;
static float last_time = 0;

// pi control constants
static float kp = 150;
static float ki = 9;

void pi_action(void) {
    for (;;) {
        float current_int_temperature = calibrated_reading(INT_SENSOR);
        // float current_ext_temperature = calibrated_reading(EXT_SENSOR);

        current_time = HAL_GetTick() / 1000;
        error = SETPOINT_TEMPERATURE - current_int_temperature;
        action = last_action + kp * (error - last_error) + ki * (current_time - last_time) * error;
        last_time = current_time;

        // limit action value
        if (action > 1000) {
            action = 1000;
        } else if (action < -1000) {
            action = -1000;
        }

        if (action < 0 /* && current_ext_temperature < current_int_temperature //@*/) {
            set_fan(TOP_FAN, action);
            set_fan(BOTTOM_FAN, 0);
            resistors_state(OFF);
        } else if (action > 0) {
            if (error > 5) {
                resistors_state(ON);
            }
            set_fan(TOP_FAN, 0);
            set_fan(BOTTOM_FAN, action*2/3);
        } else {
            set_fan(TOP_FAN, 0);
            set_fan(BOTTOM_FAN, 0);
            resistors_state(OFF);
        }

        last_error = error;
        last_action = action;
    }
}
