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

//@ Mudar para pqiscar o led da placa e os leds da camara
/**
 * @brief Changes LEDS state.
 */
void leds_state(leds_state_t state);

#endif  // __LEDS_H__
