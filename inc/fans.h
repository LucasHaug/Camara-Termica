#ifndef __FANS_H__
#define __FANS_H__

#include <stdint.h>

typedef enum fan {
    TOP_FAN,
    BOTTOM_FAN,
} fan_t;

void fans_init();

void set_fan(fan_t fan, uint16_t speed);

#endif  // __FANS_H__
