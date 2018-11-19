/**
 * @file dht11.h
 *
 * @brief Functions to read the DHT11 sensor.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 11/2018
 */

#ifndef __DHT11_H__
#define __DHT11_H__

#include <stdint.h>

uint8_t dht11_get_temperature(void);
uint8_t dht11_get_humidity(void);

#endif  // __DHT11_H__
