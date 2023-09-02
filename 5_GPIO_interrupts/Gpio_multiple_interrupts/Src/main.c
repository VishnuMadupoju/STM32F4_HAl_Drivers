#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"


#define INT_PORT    GPIOA
#define INT_PIN    GPIO_PIN_0
#define BTN_PORT	GPIOC
#define BTN_PIN		GPIO_PIN_13
#define LED_PORT	GPIOA
#define LED_PIN		GPIO_PIN_5


void gpio_pc13_interrupt_init(void);

int main()
{

  HAL_Init();

gpio_pc13_interrupt_init();
uart_init();

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
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();


	//Configure PC13

	GPIO_InitStruct.Pin  = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BTN_PORT,&GPIO_InitStruct);


    // configure the pa0 pin as interrupts
    GPIO_InitStruct.Pin=INT_PIN;
    GPIO_InitStruct.Mode=GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull=GPIO_NOPULL;
    GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(INT_PORT,& GPIO_InitStruct);

	//Configure PA5

    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT,&GPIO_InitStruct);

    //Configure EXTI for the push button
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    // configure the multiple interrupts as pa0 as interrupts
    HAL_NVIC_SetPriority(EXTI0_IRQn,0,0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);


}

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin)
{
	//Do something..
	if(GPIO_Pin == GPIO_PIN_13){

	HAL_GPIO_WritePin(LED_PORT,LED_PIN,1);
	printf("Button 13 pressed ! \n\r");
	HAL_Delay(100);
	HAL_GPIO_WritePin(LED_PORT,LED_PIN,0);
	HAL_Delay(100);
	}

	if(GPIO_Pin == GPIO_PIN_0){

	printf("Button 0 pressed ! \n\r");


	}
}


void EXTI15_10_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);

}
void EXTI0_IRQHandler (void)
{

HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);

}



