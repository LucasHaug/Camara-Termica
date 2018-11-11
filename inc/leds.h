/**
 * @file leds.h
 *
 * @brief Functions to change the state of the control
 *        led of the board and of the lamps of leds.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#ifndef __LEDS_H__
#define __LEDS_H__

/**
 * Public Enumerations
 */
typedef enum leds_state {
    ON,
    OFF,
    TOGGLE,
} leds_state_t;

/**
 * @brief Changes LEDS state.
 */
void lamps_state(leds_state_t state);

void control_led_state(leds_state_t state);

#endif  // __LEDS_H__
