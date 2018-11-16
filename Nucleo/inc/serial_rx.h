/**
 * @file serial_rx.h
 *
 * @brief Receiving serial data related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#ifndef __SERIAL_RX_H__
#define __SERIAL_RX__

#include <stdint.h>

/*****************************************
 * Public Variables
 *****************************************/

extern uint8_t turn_ON;

/*****************************************
 * Public Function Prototypes
 *****************************************/

void serial_init(void);

#endif  // __SERIAL_RX__
