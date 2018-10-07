#ifndef __FANS_H__
#define __FANS_H__

typedef enum fan {
    TOP_FAN,
    BOTTOM_FAN,
} fan_t;

void fans_init();

void fan_speed(fan_t fan, uint16_t speed);

#endif // __FANS_H__
