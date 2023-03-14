/*
 * adc.c
 *
 *  Created on: 4 мар. 2023 г.
 *      Author: ƒмитрий
 */
#include "main.h"



extern uint8_t status;
extern uint16_t SW_cnt;
extern uint8_t data_ready;


void ADC_Struct_update (ADC_HandleTypeDef *hadcx, ADC_ChannelConfTypeDef *sConfig, ADC_inputsTypeDef *adc_struct)
{

 switch(sConfig->Channel)
 {

	  case 0:
		      adc_struct->U_bat1 = (uint32_t)median(adc_struct->adcData) * KU_BAT1 / 4095;
		      if(adc_struct->U_bat1 < U_BAT_MIN)
		    	  HAL_GPIO_WritePin(SWITCH_RESET);
		      sConfig->Channel = 1;
		      HAL_ADC_ConfigChannel(hadcx, sConfig);
		      HAL_ADC_Start_DMA(hadcx, (uint32_t*)adc_struct->adcData, ADC_DATA_LENGTH);
		      break;

	  case 1:
	  		  adc_struct->U_bat2 = (uint32_t)median(adc_struct->adcData) * KU_BAT2 / 4095 - adc_struct->U_bat1;
	  		  if(adc_struct->U_bat2 < U_BAT_MIN)
	  			  HAL_GPIO_WritePin(SWITCH_RESET);
	  		  sConfig->Channel = 2;
	  		  HAL_ADC_ConfigChannel(hadcx, sConfig);
	  		  HAL_ADC_Start_DMA(hadcx, (uint32_t*)adc_struct->adcData, ADC_DATA_LENGTH);
	  		  break;

	  case 2:
	  	  	  adc_struct->U_bat3 = (uint32_t)median(adc_struct->adcData) * KU_BAT3 / 4095 - adc_struct->U_bat2
			  - adc_struct->U_bat1;
	  	  	  if(adc_struct->U_bat3 < U_BAT_MIN)
	  	  	  HAL_GPIO_WritePin(SWITCH_RESET);
	  	  	  sConfig->Channel = 3;
              HAL_ADC_ConfigChannel(hadcx, sConfig);
	  	      HAL_ADC_Start_DMA(hadcx, (uint32_t*)adc_struct->adcData, ADC_DATA_LENGTH);
	  	      break;

	  case 3:
	 	  	  adc_struct->U_bat4 = (uint32_t)median(adc_struct->adcData) * KU_BAT4 / 4095 - adc_struct->U_bat3
			  - adc_struct->U_bat2 - adc_struct->U_bat1;
	 	  	  if(adc_struct->U_bat4 < U_BAT_MIN)
	 	  		  HAL_GPIO_WritePin(SWITCH_RESET);
	 	  	  sConfig->Channel = 4;
              HAL_ADC_ConfigChannel(hadcx, sConfig);
	 	  	  HAL_ADC_Start_DMA(hadcx, (uint32_t*)adc_struct->adcData, ADC_DATA_LENGTH);
	 	  	  break;

	  case 4:
	  	 	  adc_struct->I_disch = (uint32_t)median(adc_struct->adcData) * KI_DIS / 4095; // 3.3*10*100
	  	 	  if (adc_struct->I_disch > I_DIS_MAX)
	  	 	  {
	  	 		  HAL_GPIO_WritePin(SWITCH_SET);
//	  	 		  HAL_GPIO_WritePin(TEST_SET);
	  	 		  status = SC;
	  	 		  SW_cnt = 1000;//10 sec to systick
	  	 	  }
	  	 	  sConfig->Channel = 0;
              HAL_ADC_ConfigChannel(hadcx, sConfig);
	  	 	  HAL_ADC_Start_DMA(hadcx, (uint32_t*)adc_struct->adcData, ADC_DATA_LENGTH);
	  	 	  data_ready = 1;
	  	 	  break;
 }

}

uint16_t avg (uint16_t* data)
{
	int i;
	uint32_t summ = 0;
	for( i = 0; i < ADC_DATA_LENGTH; i++ )
	{
		summ = summ + data[i];
	}
	return summ/ADC_DATA_LENGTH;
}

short comp(const void *i, const void *j)
{
  return *(short *)i - *(short *)j;
}

uint16_t median (uint16_t* data)
{
	uint16_t med;
	qsort(data, ADC_DATA_LENGTH, sizeof(short), comp);
	if (ADC_DATA_LENGTH % 2)
	{
		med = data[ADC_DATA_LENGTH/2];
	}
	else
	{
		med = (data[ADC_DATA_LENGTH/2-1] +  data[ADC_DATA_LENGTH/2])/2;
	}
	return med;
}

