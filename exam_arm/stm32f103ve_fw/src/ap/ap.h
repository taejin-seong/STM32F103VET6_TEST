/*
 * ap.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */
/* 실질적으로  Main 함수를 담당하는 부분입니다.*/

#ifndef SRC_AP_AP_H_
#define SRC_AP_AP_H_


#include "hw.h"



void apInit(void);
void apMain(void);



/*  MPU9250 상보필터 매크로 */
#define Alpha  				0.96f
#define Beta   				0.92f
#define DEG2RAD   			0.01745f  	// pi/180
#define RAD2DEG   			57.29578f 	// 180/pi


/* 엔코더 모터 RPM, 이동거리  매크로 */
//#define USING_MACRO
#ifdef  USING_MACRO

#define PI			  		 3.14f
#define DIAMETER 	 	     65.0f 							   // 바퀴 지름  (mm 단위)
#define SHAFT_PPR			 GEAR_RATIO * ONE_ROTATION_PULSES  // 샤프트축  PPR
#define ONE_THICK_DISTANCE   CIRCUMFERENCE / SHAFT_PPR		   // 1 thick당 이동한 거리 (mm 단위)

#endif /* USING_MACRO */

//#define RPM_TEST
#ifdef  RPM_TEST
#define ONE_ROTATION_PULSES  7			// 엔코더 축 PPR

#else
#define ENCODER_PULSES  	 7			// 엔코더 축 PPR

#endif /* RPM_TEST */

#define CIRCUMFERENCE 		 204.1f 	// 바퀴 원주(둘레) = 바퀴지름 * pi (mm 단위)
#define GEAR_RATIO    		 20			// 기어비








#endif /* SRC_AP_AP_H_ */
