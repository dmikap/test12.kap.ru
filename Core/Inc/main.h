/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define ADC_DATA_LENGTH                                        10
#define SIZE_OF_CMD                                             4
#define UART_RX_DATA_LENGTH                                    10
#define SYMB_QUANT                                              9
#define KU_BAT1                                               419 //с учетом делителя Ku*100*3.3
#define KU_BAT2                                               844
#define KU_BAT3                                              1263
#define KU_BAT4                                              1706
#define KI_DIS                                               3300
#define U_BAT_MIN                                            360 // 3.6V
#define I_DIS_MAX                                            1000// 10A

#define SWITCH_RESET                     GPIOA, GPIO_PIN_5, RESET
#define SWITCH_SET                       GPIOA, GPIO_PIN_5, SET

#define TEST_RESET                         GPIOC, GPIO_PIN_13, RESET
#define TEST_SET                           GPIOC, GPIO_PIN_13, SET

#define SWITCH_STATE                       GPIOA, GPIO_PIN_6

#define SC                                                    1 // короткое замыкане
#define OK                                                    0



/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef struct
{
	uint16_t adcData[ADC_DATA_LENGTH];

    uint16_t U_bat1;
    uint16_t U_bat2;
    uint16_t U_bat3;
    uint16_t U_bat4;
    uint16_t I_disch;
    uint8_t SW_state;

} ADC_inputsTypeDef;

typedef struct
{
    char U_bat_1[SYMB_QUANT];
    char U_bat_2[SYMB_QUANT];
    char U_bat_3[SYMB_QUANT];
    char U_bat_4[SYMB_QUANT];
    char I_disch_[SYMB_QUANT+1];
    char SW_state_[8];
} USART_TXTypeDef;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */
void Error_Handler(void);
uint16_t avg (uint16_t* data);
void ADC_Struct_update (ADC_HandleTypeDef *hadcx, ADC_ChannelConfTypeDef *sConfig, ADC_inputsTypeDef *adc_struct);
void Usart_Tx_data (UART_HandleTypeDef* huartx, ADC_inputsTypeDef* adc_struct, USART_TXTypeDef* usart_struct);
int Usart_Rx_cmd_data (uint8_t uartRXData[UART_RX_DATA_LENGTH], uint8_t *pData);
uint16_t median (uint16_t* data);
short comp(const void *, const void *);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
