/*
 * hw.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


#include "hw.h"


void hwInit(void)
{
	bspInit();

	//TODO: HW 설정 (3)
	uartInit();

	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_I2C2_Init();
	MX_SPI1_Init();
	motorInit(100); //duty ratio 0~100
	MPU9250_Init();
	NRF24L01_Init();
	LedInit();

}
