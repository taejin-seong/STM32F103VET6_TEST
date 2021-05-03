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
	   uartOpen(_DEF_UART1, 115200); //UART 개통

	   /* TODO 4. nRF24L01 송신  초기화 셋팅  */

	   while(NRF24L01_Check())
	   {
	  	  uartPrintf(_DEF_UART1,"NRF24L01 wireless module cannot be found by hardware\n" );
	      HAL_Delay(100);
	   }

	   uartPrintf(_DEF_UART1, "NRF24L01 wireless module hardware connection is normal\n");

	   NRF24L01_TX_Mode();
	   uartPrintf(_DEF_UART1, "Enter data sending mode, send data every 1s\n");



	   /* TODO 4. nRF24L01 수신 초기화 셋팅  */
/*
	   while(NRF24L01_Check())
	   {
	      uartPrintf(_DEF_UART1,"NRF24L01 wireless module cannot be found by hardware\n");
	      HAL_Delay(100);
	   }

	   uartPrintf(_DEF_UART1,"NRF24L01 wireless module hardware connection is normal\n");

	   NRF24L01_RX_Mode();
	   uartPrintf(_DEF_UART1, "Enter data receiving mode\n");
*/

}


void apMain(void)
{
		/*  TODO 4. nRF24L01 송신 코드 (보낼 데이터) */
	uint8_t tmp_buf[]="Hey, data is received!";

		/* TODO 4. nRF24L01 수신 코드 (받을 데이터 버퍼) */
	//uint8_t tmp_buf[256]; // 임시로 지정


		/* TODO 5. MPU9250  각도 값 테스트 변수  */
	//int16_t AccData, MagData, GyroData ;

	 /* TODO 5. MPU9250 축 테스트 변수  */
	//int16_t Ac_X, Ac_Y, Ac_Z, Gy_X, Gy_Y, Gy_Z, Ma_X, Ma_Y, Ma_Z;

	  /* TODO 5. 상보 필터 테스트 변수  */
  //int16_t Reward_Mx, Reward_My; // 변환행렬 지자계 각도 보정 변수 *
/*
	  int16_t Base_Ax, Base_Ay,Base_Az, Base_Gx, Base_Gy, Base_Gz;
	  int16_t Las_Angle_Gx , Las_Angle_Gy, Las_Angle_Gz;
	  int16_t Angle_Ax, Angle_Ay, Angle_Gx, Angle_Gy, Angle_Gz; //Angle_Az,
	  int16_t Roll, Pitch, Yaw, Yaw_G, Yaw_M;

	  int32_t dt,pre_msec;

	 calibrate(&Base_Ax, &Base_Ay, &Base_Az, &Base_Gx, &Base_Gy, &Base_Gz);
*/


		/* TODO 6. Encoder Motor 테스트 변수 */

/*
		HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
		HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

		uint32_t  TIM4_CNT, TIM2_CNT;
	  uint8_t Pos_L, Pos_R = 0;
		const float One_Thick_Distance = (float)( CIRCUMFERENCE / (GEAR_RATIO * ENCODER_PULSES ) );
		float Thick_Left = 0.0;
		float Thick_Right = 0.0;
		float  Thick_Center = 0.0;
	  float Distance, Past_Distance = 0.0;

*/

	while(1)
	{
			/* TODO: 1. LED TEST */
/*
			LedOff(_DEF_LED1);
			LedOff(_DEF_LED2);
			delay(100);

			LedToggle(_DEF_LED2);
			LedToggle(_DEF_LED1);
			delay(100);
*/

			/* TODO: 2. 모터 제어 테스트  */

/*
			Go_Straight();
			delay(1000);
			Stop();

			Back();
			delay(1000);
		  Stop();

		  Turn_Left();
		  delay(1000);
		  Stop();

		  Turn_Right();
		  delay(1000);
		  Stop();

*/


			/* TODO: 3. 라즈베리파이 초음파 장애물 감지시 UART로 수신 받아 모터 정지  또는 회전 테스트 */
/*
			uint8_t rx_data = uartRead(_DEF_UART1);

			switch (rx_data)
			{
				case 'f':
					Go_Straight();
					break;

				case 's':
					Stop();

				default:
					break;
				}
*/


			/* TODO 4.nRF24L01 송신 코드  */

			if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
			{
				uartPrintf(_DEF_UART1,"NRF24L01 wireless module data sent successfully: %s\n",tmp_buf);
			}
			else
			{
				uartPrintf(_DEF_UART1, "NRF24L01 wireless module data transmission failed\n");
			}


			/* TODO 4.nRF24L01 수신 코드 */
/*
			if(NRF24L01_RxPacket(tmp_buf)==0)
			{
				// tmp_buf[32]=0;//Add string terminator
		    uartPrintf(_DEF_UART1,"NRF24L01 wireless module data received successfully: %s\n",tmp_buf);
			}
			else
			{
				uartPrintf(_DEF_UART1,"NRF24L01 wireless module data reception failed \n");
				HAL_Delay(100);
			}

			HAL_Delay(10);
*/


			/* TODO 5. MPU9250: 변환행렬로 지자계 각도 보정 할 시  */
/*
			dt = (millis()-pre_msec)/1000.0; ////단위시간 변화량
			pre_msec = millis();

			MPU6050_GetData_Axis(&Ac_X, &Ac_Y, &Ac_Z, &Gy_X, &Gy_Y, &Gy_Z, &Ma_X, &Ma_Y, &Ma_Z);

			Las_Angle_Gx = Roll;	//최근값 누적
			Las_Angle_Gy = Pitch;
			Las_Angle_Gz = Yaw;


			Gy_X = (Gy_X - Base_Gx)/ 131;
			Gy_Y = (Gy_Y - Base_Gy)/ 131;
			Gy_Z = (Gy_Z - Base_Gz)/ 131;


			Angle_Ax = atan(-1.000 * Ac_Y / sqrt( pow(Ac_X,2) + pow(Ac_Z,2) ) ) * RAD2DEG;
			Angle_Ay = atan(Ac_X / sqrt( pow(Ac_Y,2) + pow(Ac_Z,2) ) ) * RAD2DEG;

			Angle_Gx = Gy_X * dt + Las_Angle_Gx;
			Angle_Gy = Gy_Y * dt + Las_Angle_Gy;
			Angle_Gz = Gy_Z * dt + Las_Angle_Gz;

			dt = 0.000;

			Roll  = Alpha * Angle_Gx + (1.000 - Alpha) * Angle_Ax;
			Pitch = Alpha * Angle_Gy + (1.000 - Alpha) * Angle_Ay;


			Ma_X  =  (Ma_X - 15) * 0.9;
			Ma_Y  =  Ma_Y + 65;
			Ma_Z  =  (Ma_Z + 125) * 0.53;

			Reward_Mx =  (cos(70.000*DEG2RAD)*Ma_X + sin(70.000*DEG2RAD)*Ma_Z) - 141;
			Reward_My =  (cos(-70.000*DEG2RAD)*Ma_Y - sin(-70.000*DEG2RAD)*Ma_Z)- 143;

			Yaw_G =  Angle_Gz;
			Yaw_M =  -atan2(Reward_Mx, Reward_My) * RAD2DEG;


			if( (Roll<10) && (Roll>-10) && (Pitch<10) && (Pitch>-10) )
		  {
				 Yaw = Beta * Yaw_G + (1.000 - Beta) * Yaw_M;
			}
			else
			{
				Yaw = Yaw_G;
			}

			uartPrintf(_DEF_UART1, "Roll:%d, Pitch %d, Yaw:%d , Yaw_G:%d, Yaw_M:%d \r\n", Roll, Pitch, Yaw, Yaw_G, Yaw_M);
			delay(10);
*/





			/* TODO: MPU9250: 변환행렬로 지자계 각도 비보정  */

/*
			dt = (millis()-pre_msec)/1000.0; //단위시간 변화량
		  pre_msec = millis();


			MPU6050_GetData_Axis(&Ac_X, &Ac_Y, &Ac_Z, &Gy_X, &Gy_Y, &Gy_Z, &Ma_X, &Ma_Y, &Ma_Z);

			Las_Angle_Gx = Roll;	//최근값 누적
			Las_Angle_Gy = Pitch;
			Las_Angle_Gz = Yaw;

			Gy_X = (Gy_X - Base_Gx)/ 131;
			Gy_Y = (Gy_Y - Base_Gy)/ 131;
			Gy_Z = (Gy_Z - Base_Gz)/ 131;


			Angle_Ax = atan(-1.000 * Ac_Y / sqrt( pow(Ac_X,2) + pow(Ac_Z,2) ) ) * RAD2DEG;
			Angle_Ay = atan(Ac_X / sqrt( pow(Ac_Y,2) + pow(Ac_Z,2) ) ) * RAD2DEG;

			Angle_Gx = Gy_X * dt + Las_Angle_Gx;
			Angle_Gy = Gy_Y * dt + Las_Angle_Gy;
			Angle_Gz = Gy_Z * dt + Las_Angle_Gz;

		 dt = 0.000;

		 Roll  = Alpha * Angle_Gx + (1.000 - Alpha) * Angle_Ax;
		 Pitch = Alpha * Angle_Gy + (1.000 - Alpha) * Angle_Ay;

	   Yaw_G =  Angle_Gz;
	   Yaw_M =  -atan2(Ma_X, Ma_Y) * RAD2DEG;

		 Yaw = Beta * Yaw_G + (1.000 - Beta) * Yaw_M;

		 uartPrintf(_DEF_UART1, "Roll:%d, Pitch %d, Yaw:%d , Yaw_G:%d, Yaw_M:%d \r\n", Roll, Pitch, Yaw, Yaw_G, Yaw_M);
		 delay(5);

*/

			/* TODO 5. MPU9250 Yaw 제어 테스트 , GO기준값 잡고 그거 중심으로 R,L 범위 잡기, 실제 차량에서는 기준점을 잡는 것이 중요 */
/*
		    if( (Yaw > -14) && (0 > Yaw))//G: 기준 값 -14보다 크고 0보다 작을 경우
		    {
		    	 uartPrintf(_DEF_UART1, "G. %d\n\r", Yaw);
		    }
		    else if (-14 < Yaw) //R: 기준 값 -14보다 작을 경우
		    {
		    	 uartPrintf(_DEF_UART1, "R. %d\n\r", Yaw);
		    }
		    else if (0 > Yaw) //L: 기준 값 0보다 클 경우
		    {
		       uartPrintf(_DEF_UART1, "L.%d\n\r", Yaw);
		    }
*/


		/* TODO 5. MPU-9250 각도 값 테스트 */
/*
		MPU9250_GetData(&AccData, &MagData, &GyroData);
		uartPrintf(_DEF_UART1, "MPU9250: ACC:%d , Mag:%d , Gyro:%d \r\n", AccData,  MagData,  GyroData);
		HAL_Delay(10);
*/




		/* TODO 5. MPU-9250  센서 축 테스트 */
/*
		MPU6050_GetData_Axis(&Ac_X, &Ac_Y, &Ac_Z, &Gy_X, &Gy_Y, &Gy_Z, &Ma_X, &Ma_Y, &Ma_Z);
		uartPrintf(_DEF_UART1, "MPU9250: Ac_X: %d, Ac_Y: %d, Ac_Z: %d, Gy_X: %d, Gy_Y: %d, Gy_Z: %d, Ma_X: %d, &Ma_Y: %d, Ma_Z: %d \r\n",
				   	   	   	   	   	   	  Ac_X, Ac_Y, Ac_Z, Gy_X, Gy_Y, Gy_Z, Ma_X, Ma_Y, Ma_Z);

	  uartPrintf(_DEF_UART1, "Ma_X: %d, Ma_Y: %d, Ma_Z: %d \r\n", Ma_X, Ma_Y, Ma_Z);
	  HAL_Delay(10);
*/



			/* TODO 6. Encoder 이동거리 테스트  */

		//	Go_Straight();
		//Back();
/*			TIM2_CNT = TIM2 -> CNT;
			TIM4_CNT = TIM4 -> CNT;

			if (TIM2_CNT < 1320) // ppr * step * gear (11  * 4체배 * 30 )
			{
				Pos_L ++;
				if (Pos_L == 330) // 샤프트 축 한바퀴 회전 시 총 출력되는 엔코더 펄스 수
				{
					Thick_Left  =   One_Thick_Distance;
					Pos_L = 0;
				}
			}

			if (TIM4_CNT < 1320)
			{
				Pos_R ++;
				if (Pos_R == 330)
				{
					Thick_Right =   One_Thick_Distance;
					Pos_R = 0;
				}
			}

			else
			{
				Pos_L = 0; Pos_R = 0;
			}

			Thick_Center = (Thick_Right + Thick_Left) / 2;  // 현재 이동 거리
			Past_Distance += Thick_Center ; // 과거 누적 이동거리

			Distance =  ( (Past_Distance - 1) + Thick_Center) / 1000.0f ;  // 현재 누적 이동거리

			uartPrintf(_DEF_UART1, " Thick_Center: %.3f  Past_Distance: %.3f \r\n", Thick_Center,Past_Distance);
			uartPrintf(_DEF_UART1, "cnt:%d,%d distance: %.3fM  pos:%d, %d\r\n", TIM2_CNT,TIM4_CNT,Distance,Pos_L, Pos_R);
*/

/*
			if  ( TIM2_CNT < 560 ) {
			if  ( TIM4_CNT < 560 ) {

				Pos ++;

				if (Pos == 140)
				{
					Pos = 0;
					Thick_Left  = Pos  *  One_Thick_Distance; //Pulse가 한주기에 카운터가 4만큼 증가(X4체배)
					Thick_Right = Pos  *  One_Thick_Distance; //카운터 4개 셋트가 140번나와야지 한바퀴 돈 것
															  //이거 가지고 카운터 140번 나오는 카운트 수 세야함 todo

					Thick_Center = (Thick_Right + Thick_Left) / 2;  // 현재 이동 거리
					Past_Distance += Thick_Center ; // 과거 누적 이동거리

				    Distance =  ( (Past_Distance - 1) + Thick_Center) / 1000.0f ;  // 현재 누적 이동거리
				    uartPrintf(_DEF_UART1, "distance: %.3f  pos:%d\r\n", Distance,Pos);
				}

			}
		}


		   // uartPrintf(_DEF_UART1, "l:%.3f, r:%.3f\n\r",Thick_Left, Thick_Right);
		  // uartPrintf(_DEF_UART1, "distance: %.3f  pos:%d\r\n", Distance,Pos);
*/





	}
}



#endif /* SRC_AP_AP_C_ */
