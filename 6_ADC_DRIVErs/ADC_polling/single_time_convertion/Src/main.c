
#include<stm32f4xx_hal.h>
#include<stdio.h>
#include<uart.h>
#include<adc.h>

ADC_HandleTypeDef hadc1;

uint32_t Sensorvalue=0;


int main()
{

  HAL_Init();
  UART_conf();
  //adc_start_init();


  while(1)
  {
	  // Every time You need to do this
	  // 1.Start of ADC
     HAL_ADC_Start(&hadc1);
	  // 2,poll for convertion
	  HAL_ADC_PollForConversion(&hadc1,1);
	  // reading the sensor Vlue
	  Sensorvalue  =  PA0_adc_readValue();
	 printf("Value of the Sensor = %d  \n\r",(int)Sensorvalue);

	  HAL_Delay(100);
  }
}



void  SysTick_Handler(void)
{
	HAL_IncTick();
}
