/**
 * @file fans.h
 *
 * @brief Functions for initializing and setting fan's speed.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#ifndef __FANS_H__
#define __FANS_H__

#include <stdint.h>

typedef enum fan {
    TOP_FAN,
    BOTTOM_FAN,
} fan_t;

void fans_init(void);

void set_fan(fan_t fan, uint16_t speed);

#endif  // __FANS_H__
