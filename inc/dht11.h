#ifndef __DHT11_H__
#define __DH11T_H__

#include <stdint.h>

uint8_t dht11_get_temperature(void);
uint8_t dht11_get_humidity(void);

#endif  // __DHT11_H__
