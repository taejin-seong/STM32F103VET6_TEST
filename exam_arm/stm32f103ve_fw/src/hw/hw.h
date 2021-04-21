/*
 * hw.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_




#include "hw_def.h"


//TODO: HW 설정 (1)
#include "uart.h"
#include "tim.h"
#include "i2c.h"
#include "spi.h"
#include "motor.h"
#include "mpu9250.h"
#include "nrf24l01.h"
#include "led.h"


void hwInit(void);






#endif /* SRC_HW_HW_H_ */
