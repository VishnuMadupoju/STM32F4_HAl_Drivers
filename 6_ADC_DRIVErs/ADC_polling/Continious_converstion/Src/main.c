
#include<stm32f4xx_hal.h>
#include<stdio.h>
#include<uart.h>
#include<adc.h>
#include<led.h>
uint32_t Sensorvalue=0;
uint32_t Sensorvalue1=0;

int main()
{

  HAL_Init();
  UART_conf();
  adc_start_init();
  LED_conf();

  while(1)
  {
	  Sensorvalue  =  PA0_adc_readValue();
	  Sensorvalue1=Sensorvalue*5/4096;
    if(Sensorvalue1>=3)
    {
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
    }
    else
    {
    	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
    }

	 // printf("Printf is being used !  \n\r");
	  //HAL_Delay(10);
  }
}



void  SysTick_Handler(void)
{
	HAL_IncTick();
}
