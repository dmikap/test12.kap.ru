/*
 * usart.c
 *
 *  Created on: 6 мар. 2023 г.
 *      Author: ƒмитрий
 */
#include "main.h"



void Usart_Tx_data (UART_HandleTypeDef* huartx, ADC_inputsTypeDef* adc_struct, USART_TXTypeDef* usart_struct)
{
	uint16_t tempint;
	uint16_t i;
	tempint = adc_struct->U_bat1;

	for(i=SYMB_QUANT-2;i>3;i--)
	{
		if(i!=5)
		{
	       usart_struct->U_bat_1[i] = (tempint % 10) + 48;
	       tempint/=10;
		}
	    else usart_struct->U_bat_1[i] = '.';

	}

	while (HAL_UART_Transmit_DMA(huartx,(uint8_t*) &usart_struct->U_bat_1, sizeof(usart_struct->U_bat_1)) != HAL_OK);

	tempint = adc_struct->U_bat2;

	for(i=SYMB_QUANT-2;i>3;i--)
	{
		 if(i!=5)
		 {
		    usart_struct->U_bat_2[i] = (tempint % 10) + 48;
		    tempint/=10;
		 }
		 else usart_struct->U_bat_2[i] = '.';

	}

	while (HAL_UART_Transmit_DMA(huartx,(uint8_t*) &usart_struct->U_bat_2, sizeof(usart_struct->U_bat_2)) != HAL_OK);

	tempint = adc_struct->U_bat3;

	for(i=SYMB_QUANT-2;i>3;i--)
	{
		if(i!=5)
		{
			 usart_struct->U_bat_3[i] = (tempint % 10) + 48;
			 tempint/=10;
		}
		else usart_struct->U_bat_3[i] = '.';
	}

	while (HAL_UART_Transmit_DMA(huartx,(uint8_t*) &usart_struct->U_bat_3, sizeof(usart_struct->U_bat_3)) != HAL_OK);

	tempint = adc_struct->U_bat4;

	for(i=SYMB_QUANT-2;i>3;i--)
	{
		if(i!=5)
		{
			usart_struct->U_bat_4[i] = (tempint % 10) + 48;
			tempint/=10;
		}
		else usart_struct->U_bat_4[i] = '.';
	}

	while (HAL_UART_Transmit_DMA(huartx,(uint8_t*) &usart_struct->U_bat_4, sizeof(usart_struct->U_bat_4)) != HAL_OK);

	tempint = adc_struct->I_disch;

	for(i=SYMB_QUANT-1;i>3;i--)
	{
		if(i!=6)
		{
			usart_struct->I_disch_[i] = (tempint % 10) + 48;
			tempint/=10;
		}
		else usart_struct->I_disch_[i] = '.';
	}

	while (HAL_UART_Transmit_DMA(huartx,(uint8_t*) &usart_struct->I_disch_, sizeof(usart_struct->I_disch_)) != HAL_OK);

	if(HAL_GPIO_ReadPin(SWITCH_STATE))
	{
		usart_struct->SW_state_[4] = 'S';
	    usart_struct->SW_state_[6] = 'T';
	}
	else
	{
		usart_struct->SW_state_[4] = 'R';
		usart_struct->SW_state_[6] = 'S';
	}

	while (HAL_UART_Transmit_DMA(huartx,(uint8_t*) &usart_struct->SW_state_, sizeof(usart_struct->SW_state_)) != HAL_OK);

}

int Usart_Rx_cmd_data (uint8_t uartRXData[UART_RX_DATA_LENGTH], uint8_t* pData)
{
	 uint8_t i;
	 uint8_t buff[UART_RX_DATA_LENGTH+SIZE_OF_CMD];
	 memset(buff,0,UART_RX_DATA_LENGTH+SIZE_OF_CMD);
	 memcpy(buff,uartRXData,UART_RX_DATA_LENGTH);
	 for(i=0;i<SIZE_OF_CMD;i++)
	 {
	 buff[UART_RX_DATA_LENGTH+i] = uartRXData[i];
	 }

	 for(i=0; i<UART_RX_DATA_LENGTH; i++)
     {
         if(buff[i] == pData[0] && buff[i+1] == pData[1] && buff[i+2] == pData[2] && buff[i+3] == pData[3])
         {
        	memset(uartRXData,0,UART_RX_DATA_LENGTH);
        	return SET;
         }
	 }
	 return RESET;
}

