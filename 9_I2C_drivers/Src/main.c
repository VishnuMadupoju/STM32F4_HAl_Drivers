#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"


#define   DEVICE_ADDR     0x53<<1


#define   DEVID_R					0x00
#define   POWER_CTL_R 		        0x2D
#define   DATA_FORMAT_R             0x31

#define		FOUR_G					0x01
#define		RESET					0x00
#define   SET_MEASURE_B		        0x08

#define  DATA_START_ADDR			0x32

#define  FOUR_G_SCALE_FACT  		 0.0078;


I2C_HandleTypeDef hi2c1;
void i2c1_init(void);


void adxl_write (uint8_t reg, uint8_t value);
void adxl_read_values (uint8_t reg);
void adxl_init(void);

uint8_t data_rec[6];
uint8_t device_id;

int16_t x,y,z;
float xg,yg,zg;


int main()
{

  HAL_Init();
  i2c1_init();
  adxl_init();



  while(1)
  {

	adxl_read_values (DATA_START_ADDR);

	  x = ((data_rec[1]<<8)|data_rec[0]);
	  y = ((data_rec[3]<<8)|data_rec[2]);
	  z = ((data_rec[5]<<8)|data_rec[4]);

	  xg = x * FOUR_G_SCALE_FACT;
	  yg = y * FOUR_G_SCALE_FACT;
	  zg = z * FOUR_G_SCALE_FACT;

	  HAL_Delay(10);



  }
}

void adxl_write (uint8_t reg, uint8_t value)
{
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;

	HAL_I2C_Master_Transmit (&hi2c1, DEVICE_ADDR, data, 2, 100);

}

void adxl_read_values (uint8_t reg)
{
	HAL_I2C_Mem_Read (&hi2c1, DEVICE_ADDR, reg, 1, (uint8_t *)data_rec, 6, 100);

}

void adxl_read_address (uint8_t reg)
{
	HAL_I2C_Mem_Read (&hi2c1, DEVICE_ADDR, reg, 1, &device_id, 1, 100);

}

void adxl_init(void)
{
	//1. Read device ID
	 adxl_read_address(DEVID_R);

	//2. Set data format to +/- 4g
	 adxl_write (DATA_FORMAT_R, FOUR_G);

	//3.Reset all bits
	 adxl_write (POWER_CTL_R, RESET);

	//4.Config PWR control
	adxl_write (POWER_CTL_R, SET_MEASURE_B);

}


void i2c1_init(void)
{
   /* PB8     ------> I2C1_SCL
      PB9      ------> I2C1_SDA */

	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    //Configure I2C

    __HAL_RCC_I2C1_CLK_ENABLE();

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c1);

}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}



