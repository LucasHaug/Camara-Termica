#include <stdint.h>

#include "control.h"
#include "fans.h"
#include "power_resistors.h"
#include "sensors.h"
#include "tim.h"

#define SETPOINT_TEMPERATURE 33
#define NMAX 10

//@ Causar erro minimo proposital

static float action = 0;
static float last_action = 0;
static float error = 0;
static float last_error = 0;

static float current_time = 0;
static float last_time = 0;

static uint8_t temperature_trend[NMAX] = {0};
// global temperature_trend[] index
static uint8_t n = 0;

// pi control constants
static float kp = 0.2;
static float ki = 0.009;

void pi_action(void) {
    int8_t current_trend = 0;
    float current_temperature = (float) temperature[2] / 10;

    current_time = HAL_GetTick() / 1000;
    error = SETPOINT_TEMPERATURE - current_temperature;
    action = last_action + kp * (error - last_error) + ki * (current_time - last_time) * error;
    last_time = current_time;

    // limit action value
    action *= 1000;
    if (action > 1000) {
        action = 1000;
    } else if (action < -1000) {
        action = -1000;
    }

    // calculate current temperature trend
    if (last_error - error > 0) {
        temperature_trend[n] = 1;
    } else if (last_error - error < 0) {
        temperature_trend[n] = -1;
    } else {
        temperature_trend[n] = 0;
    }
    n = (n + 1) % NMAX;
    for (int i = 0; i < NMAX; i++) {
        current_trend += temperature_trend[i];
    }

    if (current_trend > 0) {
        resistors_state(ON);
    } else if (current_trend < 0) {
        resistors_state(OFF);
    } else {
        resistors_state(OFF);
    }

    if (action < 0 && temperature[1] < temperature[2]) {
        set_fan(TOP_FAN, action);
        set_fan(BOTTOM_FAN, 0);
    } else if (action > 0) {
        set_fan(TOP_FAN, 0);
        set_fan(BOTTOM_FAN, action);
    } else {
        set_fan(TOP_FAN, 0);
        set_fan(BOTTOM_FAN, 0);
    }

    last_error = error;
    last_action = action;
}
