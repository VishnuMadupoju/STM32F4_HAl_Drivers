
#include<stm32f4xx_hal.h>
#include<stdio.h>
#include<uart.h>
#include<adc.h>
#include<led.h>
uint32_t Sensorvalue=0;

ADC_HandleTypeDef hadc1;
int main()
{

  HAL_Init();
//  UART_conf();
  HAL_ADC_Start_IT(&hadc1);
  adc_start_init();
  UART_conf();

  while(1)
  {



	 // printf("Printf is being used !  \n\r");
	  //HAL_Delay(10);
  }
}



void  SysTick_Handler(void)
{
	HAL_IncTick();
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//do something

	Sensorvalue =   PA0_adc_readValue();
	printf("Analog Sensor Value is %d",(int)Sensorvalue);


}
