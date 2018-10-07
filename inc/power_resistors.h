#ifndef __POWER_RESISTORS_H__
#define __POWER_RESISTORS_H__

typedef enum state {
    ON,
    OFF,
} state_t;

void resistors_state(state_t);

#endif // __POWER_RESISTORS_H__
