#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include "tim.h"


int main()
{

  HAL_Init();
  tim_timebase_init();
  uart_init();

  while(1)
  {

  }
}


void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef *htim)
{
	//Do somthing
	printf("A second just elapsed ! \n\r");

}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}




