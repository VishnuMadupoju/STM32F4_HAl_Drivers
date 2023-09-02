#include "stm32f4xx_hal.h"
 static void ADC_conf(void);
 extern ADC_HandleTypeDef hadc1;
// function To read The value
uint32_t PA0_adc_readValue( void)
{
  return HAL_ADC_GetValue(&hadc1);
}
 void adc_start_init(void)
 {
	 ADC_conf();
	 HAL_ADC_Start(&hadc1);

 }


void ADC_conf(void)
{
	//Configure pa0 as analog pin
    // Enabling the clock to GPIO
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_conf={0};
	GPIO_conf.Pin=GPIO_PIN_0;
	GPIO_conf.Mode= GPIO_MODE_ANALOG ;
	GPIO_conf.Pull= GPIO_NOPULL ;

	HAL_GPIO_Init(GPIOA,&GPIO_conf);

	// Configure the ADC module
	// Enabling the Clock to the ADC module
	__HAL_RCC_ADC1_CLK_ENABLE();

	hadc1.Instance=ADC1;
	hadc1.Init.ClockPrescaler= ADC_CLOCK_SYNC_PCLK_DIV8 ;
	hadc1.Init.ContinuousConvMode=DISABLE;
	hadc1.Init.Resolution=ADC_RESOLUTION_12B ;
	hadc1.Init.DMAContinuousRequests=DISABLE;
	hadc1.Init.DataAlign=ADC_DATAALIGN_RIGHT ;
	hadc1.Init.DiscontinuousConvMode=DISABLE;
	hadc1.Init.NbrOfDiscConversion=1;
	hadc1.Init.ExternalTrigConv= ADC_SOFTWARE_START ;
	hadc1.Init.ExternalTrigConvEdge= ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    HAL_ADC_Init(&hadc1);
    // Configure the Channel
    ADC_ChannelConfTypeDef Sconf={0};
    Sconf.Channel=ADC_CHANNEL_0 ;
    Sconf.Rank = 1;
    Sconf.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &Sconf);
}
