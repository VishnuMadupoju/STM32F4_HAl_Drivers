#include "stm32f4xx_hal.h"
#include <stdio.h>


#define RTC_ASYNCH_PREDIV  0x7F  // 127
#define RTC_SYNCH_PREDIV   0xF9  // 249

#define BK_FLAG		0x8888


UART_HandleTypeDef huart2;


void uart_init(void);


RTC_HandleTypeDef RtcHandle;

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,10);
	return ch;
}


uint8_t time[15] ={0};
uint8_t date[15] ={0};

void rtc_init(void);
void rtc_calendar_config(void);
void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate);


int main()
{

  HAL_Init();
  uart_init();

  __HAL_RTC_RESET_HANDLE_STATE(&RtcHandle);

  rtc_init();

  //Read backup register
  if(HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR0) != BK_FLAG)
  {
	  rtc_calendar_config();
  }



  while(1)
  {
	  rtc_calendar_show(time,date);

	 // HAL_Delay(10);
  }
}



 void rtc_init(void)
 {
	// Select RTC clock

	 RCC_OscInitTypeDef        RCC_OscInitStruct;
	 RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

	 //Turn of LSE and turn on LSI
	RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;

	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	//Set RTC clock src to LSI
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.RTCClockSelection =  RCC_RTCCLKSOURCE_LSI;

	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	//Enable RTC clock
	 __HAL_RCC_RTC_ENABLE();

    //configure calendar

	RtcHandle.Instance = RTC;
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
    RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
    RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
    RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;

    HAL_RTC_Init(&RtcHandle);




 }


 void rtc_calendar_config(void)
 {
	  RTC_DateTypeDef sdatestructure;
	  RTC_TimeTypeDef stimestructure;

	  //Set Date: Sunday JULY 14th 2019
	  sdatestructure.Year =0x19;
	  sdatestructure.Month = RTC_MONTH_JULY;
	  sdatestructure.Date =0x14;
	  sdatestructure.WeekDay = RTC_WEEKDAY_SUNDAY;

	  HAL_RTC_SetDate(&RtcHandle,&sdatestructure,RTC_FORMAT_BCD) ;

	  //Set Time: 03:00:00
	  stimestructure.Hours =  0x03;
	  stimestructure.Minutes = 0x00;
	  stimestructure.Seconds = 0x00;
	  stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
	  stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;
	  HAL_RTC_SetTime(&RtcHandle,&stimestructure,RTC_FORMAT_BCD);

	  //Wtite to Backup Register
	  HAL_RTCEx_BKUPWrite(&RtcHandle,RTC_BKP_DR0,BK_FLAG);


 }


 void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate)
 {

	 RTC_DateTypeDef sdatestructureget;
	 RTC_TimeTypeDef stimestructureget;

	  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);

	  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
	  /* Display time Format: hh:mm:ss */
	  sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

	  /* Display date Format: mm-dd-yy */
	  sprintf((char*)showdate,"%02d-%02d-%02d",sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);


	  printf(" Time : %02d:%02d:%02d\n\r",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
	  printf(" Date : %02d-%02d-%02d\n\r",sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);

 }

void  SysTick_Handler(void)
{
	HAL_IncTick();
}


void uart_init(void)
{

	 GPIO_InitTypeDef GPIO_InitStruct = {0};

    //Enable UART pins clock access
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
    __HAL_RCC_USART2_CLK_ENABLE();


	//Configure pins to act as alternate func pins(UART)

     GPIO_InitStruct.Pin  = GPIO_PIN_2|GPIO_PIN_3;
     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
     GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
     GPIO_InitStruct.Pull =  GPIO_NOPULL;
     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

     HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);

     //Configure UART module
     huart2.Instance = USART2;
     huart2.Init.BaudRate = 115200;
     huart2.Init.WordLength = UART_WORDLENGTH_8B;
     huart2.Init.StopBits = UART_STOPBITS_1;
     huart2.Init.Parity = UART_PARITY_NONE;
     huart2.Init.Mode = UART_MODE_TX;
     huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
     huart2.Init.OverSampling = UART_OVERSAMPLING_16;

     HAL_UART_Init(&huart2);


}
