/**
  ******************************************************************************
  * @file    motor.c
  * @author  Edit by Sung Tae-jin
  * @version V1.0
  * @date    19-February-2021
  * @brief   Using STM32F103C8T6 & L298N MOTOR Driver module

  ******************************************************************************
  * @attention
  *
  *IN1~IN4 Port 변경 시  Motor_Table에  순서대로 작성
  *IN1~IN4 Pin  변경 시  motor.h  에서 수정
  *Timer Port,Ch 변경 시 motor.h 에서 수정
  ******************************************************************************
**/


//#include "bsp.h"

#include "motor.h"
#include "tim.h"




typedef struct
{
	GPIO_TypeDef *Port;
	uint16_t	  Pin;
	GPIO_PinState PinState_ON;
	GPIO_PinState PinState_OFF;

}Motor_Table_uct;



Motor_Table_uct Motor_Table[MOTOR_MAX_CH] =
		{
		 /*
		  * 여기에 MOTOR를 제어할  Port를  차례대로(IN1~IN4 내림차순으로) 작성하세요.
		  *
		       Port 	   		 Pin	             Pin_State      		*/
		 {MOTOR_CONTROL_B_PORT,  IN1_MOTORA,	   GPIO_PIN_RESET, GPIO_PIN_SET},
		 {MOTOR_CONTROL_B_PORT,  IN2_MOTORA, 	   GPIO_PIN_RESET, GPIO_PIN_SET},


		 {MOTOR_CONTROL_B_PORT,  IN3_MOTORB,     GPIO_PIN_RESET, GPIO_PIN_SET},
		 {MOTOR_CONTROL_B_PORT,  IN4_MOTORB,     GPIO_PIN_RESET, GPIO_PIN_SET},

		};



bool motorInit(uint8_t duty)
{

	  bool ret = true;

	  GPIO_InitTypeDef GPIO_InitStruct = {0};


	  /*Configure GPIO pin */
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	  /* InitStruct	pin, gpio  */
	  for (int i=0; i<MOTOR_MAX_CH; i++) // 입력된  MOTOR 채널 수 만큼 구성된 Pin,Port를 설정합니다.
	  {
		  // GPIO_PIN_XX 값을 MOTOR 테이블에 받아옵니다.
		  GPIO_InitStruct.Pin = Motor_Table[i].Pin;

		  // GPIOX 값을 MOTOR 테이블에 받아옵니다.
		  HAL_GPIO_Init(Motor_Table[i].Port, &GPIO_InitStruct);

		  // 초기설정으로 일단 MOTOR를 정지시킵니다.
		  Stop();
	  }

#ifdef MOTOR_TIM1_CH
	  HAL_TIM_PWM_Start(&MOTOR_TIM_PORT, MOTOR_TIM1_CH);
	  __HAL_TIM_SetCompare(&MOTOR_TIM_PORT, MOTOR_TIM2_CH, duty);
#endif

#ifdef MOTOR_TIM2_CH
	  HAL_TIM_PWM_Start(&MOTOR_TIM_PORT, MOTOR_TIM2_CH);
	  __HAL_TIM_SetCompare(&MOTOR_TIM_PORT, MOTOR_TIM2_CH, duty);
#endif

#ifdef MOTOR_TIM3_CH
	  HAL_TIM_PWM_Start(&MOTOR_TIM_PORT, MOTOR_TIM3_CH);
	  __HAL_TIM_SetCompare(&MOTOR_TIM_PORT, MOTOR_TIM3_CH, duty);
#endif

#ifdef MOTOR_TIM4_CH
	  HAL_TIM_PWM_Start(&MOTOR_TIM_PORT, MOTOR_TIM4_CH);
	  __HAL_TIM_SetCompare(&MOTOR_TIM_PORT, MOTOR_TIM4_CH, duty);
#endif

#ifdef MOTOR_TIMALL_CH
	  HAL_TIM_PWM_Start(&MOTOR_TIM_PORT, MOTOR_TIMALL_CH);
	  __HAL_TIM_SetCompare(&MOTOR_TIM_PORT, MOTOR_TIMALL_CH, duty);
#endif


	  return ret;
}



void Turn_Right(void)
{


	HAL_GPIO_WritePin(Motor_Table[0].Port, Motor_Table[0].Pin, Motor_Table[0].PinState_OFF);
	HAL_GPIO_WritePin(Motor_Table[1].Port, Motor_Table[1].Pin, Motor_Table[1].PinState_OFF);


	HAL_GPIO_WritePin(Motor_Table[2].Port, Motor_Table[2].Pin, Motor_Table[2].PinState_ON );
	HAL_GPIO_WritePin(Motor_Table[3].Port, Motor_Table[3].Pin, Motor_Table[3].PinState_OFF);


}



void Turn_Left(void)
{

	HAL_GPIO_WritePin(Motor_Table[0].Port, Motor_Table[0].Pin, Motor_Table[0].PinState_ON);
	HAL_GPIO_WritePin(Motor_Table[1].Port, Motor_Table[1].Pin, Motor_Table[1].PinState_OFF );

	HAL_GPIO_WritePin(Motor_Table[2].Port, Motor_Table[2].Pin, Motor_Table[2].PinState_OFF);
	HAL_GPIO_WritePin(Motor_Table[3].Port, Motor_Table[3].Pin, Motor_Table[3].PinState_OFF);

}



void Go_Straight(void)
{

	HAL_GPIO_WritePin(Motor_Table[0].Port, Motor_Table[0].Pin, Motor_Table[0].PinState_ON);
	HAL_GPIO_WritePin(Motor_Table[1].Port, Motor_Table[1].Pin, Motor_Table[1].PinState_OFF);


	HAL_GPIO_WritePin(Motor_Table[2].Port, Motor_Table[2].Pin, Motor_Table[2].PinState_ON);
	HAL_GPIO_WritePin(Motor_Table[3].Port, Motor_Table[3].Pin, Motor_Table[3].PinState_OFF);

}


void Back(void)
{

	HAL_GPIO_WritePin(Motor_Table[0].Port, Motor_Table[0].Pin, Motor_Table[0].PinState_OFF);
	HAL_GPIO_WritePin(Motor_Table[1].Port, Motor_Table[1].Pin, Motor_Table[1].PinState_ON);


	HAL_GPIO_WritePin(Motor_Table[2].Port, Motor_Table[2].Pin, Motor_Table[2].PinState_OFF);
	HAL_GPIO_WritePin(Motor_Table[3].Port, Motor_Table[3].Pin, Motor_Table[3].PinState_ON);



}


void Stop(void)
{

	HAL_GPIO_WritePin(Motor_Table[0].Port, Motor_Table[0].Pin, Motor_Table[0].PinState_OFF);
	HAL_GPIO_WritePin(Motor_Table[1].Port, Motor_Table[1].Pin, Motor_Table[1].PinState_OFF);


	HAL_GPIO_WritePin(Motor_Table[2].Port, Motor_Table[2].Pin, Motor_Table[2].PinState_OFF);
	HAL_GPIO_WritePin(Motor_Table[3].Port, Motor_Table[3].Pin, Motor_Table[3].PinState_OFF);

}
