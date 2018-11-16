/**
 * @file serial_rx.c
 *
 * @brief Receiving serial data related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 11/2018
 */

#include "serial_rx.h"

#include "dma.h"
#include "usart.h"

uint8_t turn_ON = 0;

void serial_init(void) {
    MX_DMA_Init();
    MX_USART2_UART_Init();
    HAL_UART_Receive_DMA(&huart2, &turn_ON, 1);
}
