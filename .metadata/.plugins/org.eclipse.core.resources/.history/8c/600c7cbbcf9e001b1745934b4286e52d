/*
 * ap.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_AP_AP_C_
#define SRC_AP_AP_C_


#include "ap.h"




// TEST용 함수
void apInit(void)
{
   uartOpen(_DEF_UART1, 115200); //UART 개통


   // nRF24L01 송신 코드
   /*
   while(NRF24L01_Check())
   	{
	    uartPrintf(_DEF_UART1,"NRF24L01 wireless module cannot be found by hardware\n" );
   		HAL_Delay(100);
   	}
   	 uartPrintf(_DEF_UART1, "NRF24L01 wireless module hardware connection is normal\n");

   	 NRF24L01_TX_Mode();
   	 uartPrintf(_DEF_UART1, "Enter data sending mode, send data every 1s\n");
	*/


   // nRF24L01 수신 코드
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



// TEST용 함수
void apMain(void)
{

	// nRF24L01 송신 코드 (보낼 데이터)
//	uint8_t tmp_buf[]="Hey, data is received!";

	// nRF24L01 수신 코드 (받을 데이터 버퍼)
//	uint8_t tmp_buf[256]; // 임시로 지정


	// MPU9250  각도 값 테스트 변수
	//int16_t AccData, MagData, GyroData ;

    // MPU9250 축 테스트 변수
   //int16_t Ac_X, Ac_Y, Ac_Z, Gy_X, Gy_Y, Gy_Z, Ma_X, Ma_Y, Ma_Z;

   //상보 필터 테스트 변수

 //  int16_t Reward_Mx, Reward_My; // 변환행렬 지자계 각도 보정 변수 *
/*
   int16_t Base_Ax, Base_Ay,Base_Az, Base_Gx, Base_Gy, Base_Gz;
   int16_t Las_Angle_Gx , Las_Angle_Gy, Las_Angle_Gz;
   int16_t Angle_Ax, Angle_Ay, Angle_Gx, Angle_Gy, Angle_Gz; //Angle_Az,
   int16_t Roll, Pitch, Yaw, Yaw_G, Yaw_M;

   int32_t dt,pre_msec;

   calibrate(&Base_Ax, &Base_Ay, &Base_Az, &Base_Gx, &Base_Gy, &Base_Gz);
*/


	//엔코더 모터 테스트 변수

//	uint8_t rx_data;
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);


/*
  	uint16_t TIM2_CNT1, TIM2_CNT2, TIM2_DIFF, TIM2_DIR,
	         TIM4_CNT1, TIM4_CNT2, TIM4_DIFF, TIM4_DIR,
			 TIM2_RPM_HALL = 0, TIM2_RPM_SHAFT = 0,
			 TIM4_RPM_HALL = 0, TIM4_RPM_SHAFT = 0 ;

 	uint32_t tick;

 	// 현재 카운터와 tick 값
	TIM2_CNT1 = TIM2 -> CNT;
	TIM4_CNT1 = TIM4 -> CNT;

	tick = millis();
*/

	//TODO:엔코더 이동거리 테스트 변수
	uint32_t  TIM4_CNT, TIM2_CNT;
    uint8_t Pos_L, Pos_R = 0;
	const float One_Thick_Distance = (float)( CIRCUMFERENCE / (GEAR_RATIO * ENCODER_PULSES ) );
	float Thick_Left, Thick_Right, Thick_Center;
    float Distance, Past_Distance = 0.0;




	while(1)
	{

		//TODO: MPU9250: 변환행렬로 지자계 각도 보정 할 시...

		  //단위시간 변화량

		/*
		  dt = (millis()-pre_msec)/1000.0;
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


		//TODO: MPU9250: 변환행렬로 지자계 각도 비보정

		  //단위시간 변화량
/*
		  dt = (millis()-pre_msec)/1000.0;
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
*/
	      //TODO MPU9250 Yaw 제어 테스트 , GO기준값 잡고 그거 중심으로 R,L 범위 잡기, 실제 차량에서는 기준점을 잡는 것이 중요
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

	      /*
		  uartPrintf(_DEF_UART1, "Roll:%d, Pitch %d, Yaw:%d , Yaw_G:%d, Yaw_M:%d \r\n", Roll, Pitch, Yaw, Yaw_G, Yaw_M);
		  delay(5);
		  */




		//MPU-9250 각도 값 테스트
		/*
		MPU9250_GetData(&AccData, &MagData, &GyroData);
		//															  가속도계센서 각도      지자기센서 각도  자이로센서 각도
		uartPrintf(_DEF_UART1, "MPU9250: ACC:%d , Mag:%d , Gyro:%d \r\n", AccData,  MagData,  GyroData);
		HAL_Delay(10);
		*/




		//MPU-9250  센서 축 테스트

	//	MPU6050_GetData_Axis(&Ac_X, &Ac_Y, &Ac_Z, &Gy_X, &Gy_Y, &Gy_Z, &Ma_X, &Ma_Y, &Ma_Z);
	//	uartPrintf(_DEF_UART1, "MPU9250: Ac_X: %d, Ac_Y: %d, Ac_Z: %d, Gy_X: %d, Gy_Y: %d, Gy_Z: %d, Ma_X: %d, &Ma_Y: %d, Ma_Z: %d \r\n",
	//			   	   	   	   	   	   	  Ac_X, Ac_Y, Ac_Z, Gy_X, Gy_Y, Gy_Z, Ma_X, Ma_Y, Ma_Z);

	//	uartPrintf(_DEF_UART1, "Ma_X: %d, Ma_Y: %d, Ma_Z: %d \r\n", Ma_X, Ma_Y, Ma_Z);
	//    HAL_Delay(10);




		//nRF24L01 송신 코드
		/*
		if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
		{
			uartPrintf(_DEF_UART1,"NRF24L01 wireless module data sent successfully: %s\n",tmp_buf);
		}
		else
		{
			uartPrintf(_DEF_UART1, "NRF24L01 wireless module data transmission failed\n");
		}
		*/

		//nRF24L01 수신 코드
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




		//TODO: 모터 제어 테스트

/*		Go_Straight();
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



	    // 유아트 수신 테스트..
	    /*
	    uartPrintf(_DEF_UART1, "a");

		if (uartAvailable(_DEF_UART1) == 0)
		{
			uint8_t rx_data = uartRead(_DEF_UART1);
			uartPrintf(_DEF_UART1, "rx_data : %c\n\r", rx_data);

		}
		*/



		//TODO: 라즈베리파이 초음파 장애물 감지시 모터 정지  또는 회전 테스트
		/*
		 * 1). 라즈베리파이 초음파 장애물 감지에 따라  모터 정지, 직진은 하나 라즈베리파이 서보모터는 정지하지 않음
		 *     생각해서 코딩 다시 짜야댐
		 *
		 * 2). 라즈베리파이 쪽에서 전압 딸림
		 *
		 * 3). 실제로 사용할려면 while문에 스위치문 쓰기에는 무리가 있음 구조체나 다른 방안 검토
		 */
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





		//TODO: 엔코더 모터 count 테스트
/*
		  rx_data = uartRead(_DEF_UART1);
  	      switch (rx_data)
		  {
			 case 'a':
				 Go_Straight();
			//	 uartPrintf(_DEF_UART1, "UART1: %c, COUNT:%d\n\r", rx_data, htim2.Instance->CNT);
				 break;

			 case 's':
				 Back();
			//	 uartPrintf(_DEF_UART1, "UART1: %c, COUNT:%d\n\r", rx_data, htim2.Instance->CNT);
				 break;

			 case 'd':
				 Stop();
			//	 uartPrintf(_DEF_UART1, "UART1: %c\n\r,", rx_data);
				 break;

			 default:
				 Stop();
				 break;

		  }

*/



			//TODO 엔코더 모터 RPM 테스트 , TIM2에 달려있는 엔코더 모터만...
/*
			Go_Straight();
			//Back();


			if(millis() - tick > 1000L)
			{
				// 1초마다 TIM2 카운터 증가 확인
				TIM2_CNT2 = TIM2->CNT;

				// 회전 방향 확인
				if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2))
				{
					TIM2_DIR = 1;

					// __HAL_TIM_IS_TIM_COUNTING_DOWN 매크로가 방향성을 잘못 알려주는 경우 예외처리
					if((TIM2_CNT2 > TIM2_CNT1) && (TIM2_CNT2 - TIM2_CNT1 < 100)) TIM2_DIR = 0;
				}
				else
				{
					TIM2_DIR = 0;

					// __HAL_TIM_IS_TIM_COUNTING_DOWN 매크로가 방향성을 잘못 알려주는 경우 예외처리
					if((TIM2_CNT1 > TIM2_CNT2) && (TIM2_CNT1 - TIM2_CNT2 < 100)) TIM2_DIR = 1;
				}

				if(TIM2_DIR)
				{
					// Down Counting 방향으로 회전할 때
					if(TIM2_CNT1 >= TIM2_CNT2) TIM2_DIFF = TIM2_CNT1 - TIM2_CNT2;
					else TIM2_DIFF = (TIM2 -> ARR + TIM2_CNT1) - TIM2_CNT2 ;
				}
				else
				{
					// Up Counting 방향으로 회전할 때
					if(TIM2_CNT2 >= TIM2_CNT1) TIM2_DIFF = TIM2_CNT2 - TIM2_CNT1;
					else TIM2_DIFF = (TIM2 -> ARR + TIM2_CNT2) - TIM2_CNT1;
				}

				if((TIM2->SMCR & 0x03) == 0x03)
				{
					// X4 Mode 일때는 카운터가 4 증가할 때, 1개의 Pulse
					TIM2_RPM_HALL = TIM2_DIFF * 60 / 4 / ONE_ROTATION_PULSES; //RPM 계산을 위해서는 x 60
																			  //RPM of the motor shaft
					TIM2_RPM_SHAFT = TIM2_RPM_HALL / 20; // RPM of the gearbox's output shaf

				}
				else
				{
					// X4 Mode 일때는 카운터가 2 증가할 때, 1개의 Pulse
					TIM2_RPM_HALL = TIM2_DIFF * 60 / 2 / ONE_ROTATION_PULSES; //RPM 계산을 위해서는 x 60
		      	  	  	  	  	  	  	  	  	  	  	  	  	  	  		  //RPM of the motor shaft
					TIM2_RPM_SHAFT = TIM2_RPM_HALL / 20; // RPM of the gearbox's output shaf

				}

				tick = millis();
				TIM2_CNT1 = TIM2 -> CNT;
			}

		    uartPrintf(_DEF_UART1, "dir :%d. diff:%d, RPM_HALL:%d, RPM_SHAFT:%d \r\n",TIM2_DIR, TIM2_DIFF,TIM2_RPM_HALL,TIM2_RPM_SHAFT);
*/











					//TODO 엔코더 모터 RPM 테스트 , TIM4에 달려있는 엔코더 모터만...
/*
					Go_Straight();
					//Back();



					if(millis() - tick > 1000L)
					{
					     // 1초마다 TIM2 카운터 증가 확인
					     TIM4_CNT2 = TIM4->CNT;

					      // 회전 방향 확인
					   if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4))
					   {
					        TIM4_DIR = 1;

					        // __HAL_TIM_IS_TIM_COUNTING_DOWN 매크로가 방향성을 잘못 알려주는 경우 예외처리
					   if((TIM4_CNT2 > TIM4_CNT1) && (TIM4_CNT2 - TIM4_CNT1 < 100)) TIM4_DIR = 0;
					   }
					   else
					   {
						   TIM4_DIR = 0;

					     // __HAL_TIM_IS_TIM_COUNTING_DOWN 매크로가 방향성을 잘못 알려주는 경우 예외처리
					     if((TIM4_CNT1 > TIM4_CNT2) && (TIM4_CNT1 - TIM4_CNT2 < 100)) TIM4_DIR = 1;
					   }

					   if(TIM4_DIR)
					   {
					     // Down Counting 방향으로 회전할 때
					     if(TIM4_CNT1 >= TIM4_CNT2) TIM4_DIFF = TIM4_CNT1 - TIM4_CNT2;
					     else TIM4_DIFF = (TIM4 -> ARR + TIM4_CNT1) - TIM4_CNT2 ;
					   }
					   else
					   {
					      // Up Counting 방향으로 회전할 때
					      if(TIM4_CNT2 >= TIM4_CNT1) TIM4_DIFF = TIM4_CNT2 - TIM4_CNT1;
					      else TIM4_DIFF = (TIM4 -> ARR + TIM4_CNT2) - TIM4_CNT1;
					   }

					   if((TIM4->SMCR & 0x03) == 0x03)
					   {
					     // X4 Mode 일때는 카운터가 4 증가할 때, 1개의 Pulse
						   TIM4_RPM_HALL = TIM4_DIFF * 60 / 4 / ONE_ROTATION_PULSES; //RPM 계산을 위해서는 x 60
						   	   	   	   	   	   	   	   	   	   	   	   	   	         //RPM of the motor shaft
					       TIM4_RPM_SHAFT = TIM4_RPM_HALL / 20; // RPM of the gearbox's output shaf

					    }
					    else
					    {
					      // X4 Mode 일때는 카운터가 2 증가할 때, 1개의 Pulse
					      TIM4_RPM_HALL = TIM4_DIFF * 60 / 2 / ONE_ROTATION_PULSES; //RPM 계산을 위해서는 x 60
					      	  	  	  	  	  	  	  	  	  	  	  	  	  	  	//RPM of the motor shaft
					      TIM4_RPM_SHAFT = TIM4_RPM_HALL / 20; // RPM of the gearbox's output shaf

					    }

					     tick = millis();
					     TIM4_CNT1 = TIM4 -> CNT;
					    }

					    uartPrintf(_DEF_UART1, "dir :%d. diff:%d, RPM_HALL:%d, RPM_SHAFT:%d \r\n",TIM4_DIR, TIM4_DIFF,TIM4_RPM_HALL,TIM4_RPM_SHAFT);
*/





					//TODO 엔코더 모터 RPM 테스트 , TIM4, TIM2 에 달려있는 엔코더 모터두개 다

/*					    Go_Straight();
					 //	Back();

		  	  	  	  if(millis() - tick > 1000L)
		  	  	  	  {

		  	  	  		  TIM2_CNT2 = TIM2 -> CNT;
		  	  	  		  TIM4_CNT2 = TIM4 -> CNT;

		  	  	  		  // 회전 방향 확인
		  	  	  		  if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2) && __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4) )
		  	  	  	      {
		  	  	  			  TIM2_DIR = 1;
		  	  	  			  TIM4_DIR = 1;

		  	  	  			  // __HAL_TIM_IS_TIM_COUNTING_DOWN 매크로가 방향성을 잘못 알려주는 경우 예외처리
		  	  	  			  if(((TIM2_CNT2 > TIM2_CNT1) && (TIM2_CNT2 - TIM2_CNT1 < 100)) && ((TIM4_CNT2 > TIM4_CNT1) && (TIM4_CNT2 - TIM4_CNT1 < 100)))
		  	  	  			  {
		  	  	  				  TIM2_DIR = 0;
		  	  	  				  TIM4_DIR = 0;
		  	  	  			  }
		  	  	  	      }
		  	  	  		  else
		  	  	  		  {
		  	  	  			  TIM2_DIR = 0;
		  	  	  			  TIM4_DIR = 0;

		  	  	  			  // __HAL_TIM_IS_TIM_COUNTING_DOWN 매크로가 방향성을 잘못 알려주는 경우 예외처리
		  	  	  			  if(((TIM2_CNT1 > TIM2_CNT2) && (TIM2_CNT1 - TIM2_CNT2 < 100)) && ((TIM4_CNT1 > TIM4_CNT2) && (TIM4_CNT1 - TIM4_CNT2 < 100)))
		  	  	  			  {
		  	  	  				  TIM2_DIR = 1;
		  	  	  			  	  TIM4_DIR = 1;
		  	  	  			  }

		  	  	  		  }

		  	  	  		  if(TIM2_DIR && TIM4_DIR)
		  	  	  		  {
		  	  	  			  // Down Counting 방향으로 회전할 때
		  	  	  			  if((TIM2_CNT1 >= TIM2_CNT2) && (TIM4_CNT1 >= TIM4_CNT2))
		  	  	  			  {
		  	  	  				  TIM2_DIFF = TIM2_CNT1 - TIM2_CNT2;
		  	  	  				  TIM4_DIFF = TIM4_CNT1 - TIM4_CNT2;
		  	  	  			  }
		  	  	  			  else
		  	  	  			  {

		  	  	  				  TIM2_DIFF = (TIM2 -> ARR + TIM2_CNT1) - TIM2_CNT2 ;
		  	  	  				  TIM4_DIFF = (TIM4 -> ARR + TIM4_CNT1) - TIM4_CNT2 ;
		  	  	  			  }
		  	  	  		  }
		  	  	  		  else
		  	  	  		  {
		  	  	  			  // Up Counting 방향으로 회전할 때
		  	  	  			  if((TIM2_CNT2 >= TIM2_CNT1) && (TIM4_CNT2 >= TIM4_CNT1))
		  	  	  			  {
		  	  	  				 TIM2_DIFF = TIM2_CNT2 - TIM2_CNT1;
		  	  	  				 TIM4_DIFF = TIM4_CNT2 - TIM4_CNT1;
		  	  	  			  }
		  	  	  			  else
		  	  	  			  {
		  	  	  				  TIM2_DIFF = (TIM2 -> ARR + TIM2_CNT2) - TIM2_CNT1 ;
		  	  	  				  TIM4_DIFF = (TIM4 -> ARR + TIM4_CNT2) - TIM4_CNT1 ;
		  	  	  			  }
		  	  	  		  }

		  	  	  		  if(((TIM2->SMCR & 0x03) == 0x03) && ((TIM4->SMCR & 0x03) == 0x03))
		  	  	  		  {
		  	  	  			  // X4 Mode 일때는 카운터가 4 증가할 때, 1개의 Pulse
		  	  	  			  TIM2_RPM_HALL = TIM2_DIFF * 60 / 4 / ONE_ROTATION_PULSES;
		  	  	  			  TIM4_RPM_HALL = TIM4_DIFF * 60 / 4 / ONE_ROTATION_PULSES;

		  	  	  			  TIM2_RPM_SHAFT = TIM2_RPM_HALL / 20;
		  	  	  			  TIM4_RPM_SHAFT = TIM4_RPM_HALL / 20;

		  	  	  		  }
		  	  	  		  else
		  	  	  		  {

		  	  	  			  TIM2_RPM_HALL = TIM2_DIFF * 60 / 2 / ONE_ROTATION_PULSES;
		  	  	  			  TIM4_RPM_HALL = TIM4_DIFF * 60 / 2 / ONE_ROTATION_PULSES;

		  	  	  			  TIM2_RPM_SHAFT = TIM2_RPM_HALL / 20;
		  	  	  			  TIM4_RPM_SHAFT = TIM4_RPM_HALL / 20;

		  	  	  		  }

		  	  	  		  tick = millis();

		  	  	  		  TIM2_CNT1 = TIM2 -> CNT;
		  	  	  		  TIM4_CNT1 = TIM4 -> CNT;
		  	  	  	  }

		  	  	  	  uartPrintf(_DEF_UART1, "TIM2_DIR :%1d. TIM2_DIFF:%5d, TIM2_RPM_HALL:%4d, TIM2_RPM_SHAFT:%3d \r\nTIM4_DIR :%1d. TIM4_DIFF:%5d, TIM4_RPM_HALL:%4d, TIM4_RPM_SHAFT:%3d \r\n\n",
											  TIM2_DIR, TIM2_DIFF, TIM2_RPM_HALL, TIM2_RPM_SHAFT,
											  TIM4_DIR, TIM4_DIFF, TIM4_RPM_HALL, TIM4_RPM_SHAFT);


*/



		//TODO 엔코더 거리구하기

		//Go_Straight();
		Back();
		TIM2_CNT = TIM2 -> CNT;
		TIM4_CNT = TIM4 -> CNT;

		if (TIM2_CNT < 560) // ppr * step * gear (7  * 4체배 * 20 )
		{
			Pos_L ++;
			if (Pos_L == 140) // 샤프트 축 한바퀴 회전 시 총 출력되는 엔코더 펄스 수
			{
				Thick_Left  =   One_Thick_Distance;
				Pos_L = 0;
			}
		}

		if (TIM4_CNT < 560)
		{
			Pos_R ++;
			if (Pos_R == 140)
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
		//uartPrintf(_DEF_UART1, " Thick_Center: %.3f  Past_Distance: %.3f \r\n", Thick_Center,Past_Distance);
		uartPrintf(_DEF_UART1, "cnt:%d,%d distance: %.3fM  pos:%d, %d\r\n", TIM2_CNT,TIM4_CNT,Distance,Pos_L, Pos_R);

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

*/


	   // uartPrintf(_DEF_UART1, "l:%.3f, r:%.3f\n\r",Thick_Left, Thick_Right);
	  // uartPrintf(_DEF_UART1, "distance: %.3f  pos:%d\r\n", Distance,Pos);




	}
}




// TODO: 실전 함수

/*

 void apInit(void)
{
   uartOpen(_DEF_UART1, 115200); //UART
}


void apMain(void)
{

	while(1)
	{

	}
}
*/


#endif /* SRC_AP_AP_C_ */
