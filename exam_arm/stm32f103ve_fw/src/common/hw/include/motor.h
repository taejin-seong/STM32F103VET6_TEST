/*
 * motor.h
 *
 *  Created on: 2021. 2. 18.
 *      Author: sungt
 */

   /*
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                                             *
    *           L298N Driver GPIO Configuration      		*
    *                                              			*
    *               ENA   <------ TIMx_CHx                  *
    *               ENB   <------ TIMx_CHx                  *
    *               IN1   <------ GPIOx,GPIO_PIN_x          *
    *               IN2   <------ GPIOx,GPIO_PIN_x          *
    *               IN3   <------ GPIOx,GPIO_PIN_x          *
    *               IN4   <------ GPIOx,GPIO_PIN_x          *
    *                        		                        *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                 */


#ifndef SRC_COMMON_HW_INCLUDE_MOTOR_H_
#define SRC_COMMON_HW_INCLUDE_MOTOR_H_


#include "hw_def.h"


#ifdef _USE_HW_MOTOR



#define MOTOR_MAX_CH             HW_MOTOR_MAX_CH



/* Motor PWM Control TIMER Port
*/


/* #define MOTOR_TIM_PORT         htim1 */
/* #define MOTOR_TIM_PORT         htim2 */
#define MOTOR_TIM_PORT         htim3
/* #define MOTOR_TIM_PORT         htim4 */



/* Motor PWM Control TIMER Channel
*/


/* #define MOTOR_TIM1_CH         TIM_CHANNEL_1 */
/* #define MOTOR_TIM2_CH         TIM_CHANNEL_2 */
#define MOTOR_TIM3_CH         TIM_CHANNEL_3
#define MOTOR_TIM4_CH         TIM_CHANNEL_4
/* #define MOTOR_TIMALL_CH         TIM_CHANNEL_ALL */



/* L298N Motor Driver Direction Control Port
*/

#define MOTOR_CONTROL_A_PORT         GPIOA
#define MOTOR_CONTROL_B_PORT         GPIOB



/*L298N Motor Driver Direction Control Pin
 */

#define IN1_MOTORA      GPIO_PIN_12          // Modify if necessary.
#define IN2_MOTORA      GPIO_PIN_13
#define IN3_MOTORB      GPIO_PIN_14
#define IN4_MOTORB      GPIO_PIN_15




bool motorInit(uint8_t duty);
void Turn_Right(void);
void Turn_Left(void);
void Go_Straight(void);
void Back(void);
void Stop(void);






#endif /*_USE_HW_MOTOR */
#endif /* SRC_COMMON_HW_INCLUDE_MOTOR_H_ */
