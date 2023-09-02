
#include<stm32f4xx_hal.h>
#include<stdio.h>
#include<uart.h>
#include<adc.h>
#include<led.h>
uint32_t sensorvalue[2];

ADC_HandleTypeDef hadc1;
int main()
{

  HAL_Init();
//  UART_conf();
 // HAL_ADC_Start_IT(&hadc1);
  ADC_conf_mutiple();
  UART_conf();
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)sensorvalue,2);
  while(1)
  {


	printf("Sensor 1 data :  %d \n\r",(int)sensorvalue[0]);
	printf("Sensor 2 data :  %d \n\r",(int)sensorvalue[1]);
	HAL_Delay(1000);

}

}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}



