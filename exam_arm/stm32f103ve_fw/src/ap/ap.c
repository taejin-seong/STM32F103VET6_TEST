/*
 * ap.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_AP_AP_C_
#define SRC_AP_AP_C_


#include "ap.h"



// TODO: 실전 함수



 void apInit(void)
{

}


void apMain(void)
{

	while(1)
	{
			LedOff(_DEF_LED1);
			LedOff(_DEF_LED2);
			delay(100);

			LedToggle(_DEF_LED2);
			LedToggle(_DEF_LED1);
			delay(100);



	}
}



#endif /* SRC_AP_AP_C_ */
