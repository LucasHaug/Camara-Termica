/**
 * @file power_resistors.h
 *
 * @brief Resistors state related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#ifndef __POWER_RESISTORS_H__
#define __POWER_RESISTORS_H__

/**
 * Public Enumerations
 */
typedef enum resist_state {
    ON,
    OFF,
} resist_state_t;

void resistors_state(resist_state_t);

#endif  // __POWER_RESISTORS_H__
