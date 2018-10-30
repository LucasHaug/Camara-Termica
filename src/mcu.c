/**
 * @file mcu.c
 *
 * @brief MCU related
 */

#include <stdint.h>
#include <string.h>

#include "mcu.h"

#include "gpio.h"
#include "main.h"
#include "stm32f0xx_hal.h"
#include "usart.h"

#include "fans.h"
#include "sensors.h"

/*****************************************
 * Private Function Prototypes
 *****************************************/

/**
 * @brief Initializes System Clock.
 */
static void SystemClock_Config(void);

/*****************************************
 * Public Function Body Definitions
 *****************************************/
void mcu_init(void) {
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    sensors_init();
    fans_init();

    MX_USART2_UART_Init();
}

void mcu_sleep(uint32_t ms) {
    HAL_Delay(ms);
}

void mcu_printf(char* data) {
    HAL_UART_Transmit(&huart2, (uint8_t*) data, strlen(data), 100);
}

void mcu_sleep_us(uint32_t us) {
    us *= (SystemCoreClock / 1000000) / 5;
    while (us--)
        ;
}

/*****************************************
 * Private Function Body Definitions
 *****************************************/

// Clock config should be copied from Cube generated
// main.c before "make prepare" is called
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        _Error_Handler(__FILE__, __LINE__);
    }

    /**Initializes the CPU, AHB and APB busses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        _Error_Handler(__FILE__, __LINE__);
    }

    /**Configure the Systick interrupt time
     */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /**Configure the Systick
     */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void _Error_Handler(char* file, int line) {
    (void) file;
    (void) line;

    for (;;) {
    }
}

// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//     if (GPIO_Pin == GPIO_PIN_13 && fan_on == false) {
//         set_fan(TOP_FAN, 1000);
//         set_fan(BOTTOM_FAN, 0);
//     } else if (GPIO_Pin == GPIO_PIN_13 && fan_on == true) {
//         set_fan(TOP_FAN, 0);
//         set_fan(BOTTOM_FAN, 1000);
//     }

//     fan_on = !fan_on;
// }
