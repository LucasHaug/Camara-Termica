/**
 * @file mcu.h
 *
 * @brief MCU related
 */

#ifndef __MCU_H__
#define __MCU_H__

#include <stdint.h>

/** Changes are needed also in the Makefile */
#define SERIE 3

#if SERIE == 0
#define F0_SERIE
#else
#define F3_SERIE
#endif

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initializes MCU and some peripherals.
 */
void mcu_init(void);

/**
 * @brief Put the MCU to sleep.
 *
 * @param ms  Sleep time in milliseconds
 */
void mcu_sleep(uint32_t ms);

void mcu_printf(char* data);

void mcu_sleep_us(uint32_t us);

#endif  // __MCU_H__
