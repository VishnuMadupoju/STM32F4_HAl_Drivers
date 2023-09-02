#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"



#define BTN_PORT	GPIOC
#define BTN_PIN		GPIO_PIN_13
#define LED_PORT	GPIOA
#define LED_PIN		GPIO_PIN_5


void gpio_pc13_interrupt_init(void);

int main()
{

 HAL_Init();

gpio_pc13_interrupt_init();
UART_conf();

  while(1)
  {

  }

}



void  SysTick_Handler(void)
{
	HAL_IncTick();
}


void gpio_pc13_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_Conf = {0};


	//Enabling the Clocks
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();


	//Configure PC13

	GPIO_Conf.Pin=BTN_PIN;
	GPIO_Conf.Mode=GPIO_MODE_IT_RISING;
	GPIO_Conf.Pull=GPIO_NOPULL;
	GPIO_Conf.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BTN_PORT,&GPIO_Conf);

	//Configure PA5

    GPIO_Conf.Pin = LED_PIN;
    GPIO_Conf.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Conf.Pull = GPIO_NOPULL;
    GPIO_Conf.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT,&GPIO_Conf);

    //Configure EXTI
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, -1, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


}

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin)
{


	//Do something..



	printf("Interrupt ids used ! \n\r");





}


void EXTI15_10_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);

}



