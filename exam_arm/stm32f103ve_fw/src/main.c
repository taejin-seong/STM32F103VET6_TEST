/*
 * main.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


#include "main.h"



int main(void)
{
	hwInit();
	apInit();

	apMain();

	return 0;
}
