
#include<stm32f4xx_hal.h>
#include<stdio.h>
UART_HandleTypeDef huart2;

char message[50]="WELCOME TO UART1 \n";
void  GPIO_conf(void);
//int_io_putchar(int ch)
//{
//	 HAL_UART_Transmit(&huart2,(uint8_t *)ch,20,10);// 20 is word length and 10 is time out 10m
//	 return ch;
//}
int main()
{

	 // initilzes the HAL API
      HAL_Init();
     // initilzes the UART Initillization
      GPIO_conf();

	while(1)
	{
     //printf("Hello Chary Garu\r\n");
    HAL_UART_Transmit(&huart2,(uint16_t *)message,30,10);// 50 is word length and 70 is time out 10m

    }
}




 void GPIO_conf(void)
{

	 // Initilizaton the GPIOPORTS
	 GPIO_InitTypeDef GPIO_Conf={0};// conifigurations are of the user varable
	// ENABLING THE CLOCK FOR THE CLOCK FOR THE PORT A Connetec to poert uart2
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// ENABLING THE CLOCK FOR THE CLOCK FOR THE uart2
	__HAL_RCC_USART2_CLK_ENABLE();
	//Configurations of GPIO a as output
	GPIO_Conf.Pin=GPIO_PIN_2|GPIO_PIN_3;
	GPIO_Conf.Mode=GPIO_MODE_AF_PP;
	GPIO_Conf.Pull=GPIO_NOPULL;
	GPIO_Conf.Alternate=GPIO_AF7_USART2;
	GPIO_Conf.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA,&GPIO_Conf);
	// Configuration of UART2 as it connected to the inbuild usb pin
	huart2.Instance=USART2;
	huart2.Init.BaudRate=115200;
	huart2.Init.WordLength=UART_WORDLENGTH_8B;
	huart2.Init.StopBits=UART_STOPBITS_1;
	huart2.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	huart2.Init.Mode=UART_MODE_TX;
	huart2.Init.OverSampling=UART_OVERSAMPLING_16;
	huart2.Init.Parity=UART_PARITY_NONE ;
	HAL_UART_Init(&huart2);



}
 void SystTick_Handler(void)
 {
	 HAL_IncTick();
 }
