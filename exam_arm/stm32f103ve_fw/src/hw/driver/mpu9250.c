/**
  ******************************************************************************
  * @file    mpu9250.h
  * @author  Edit by Sung Tae-jin
  * @version V1.0
  * @date    15-March-2021
  * @brief   Using STM32F103C8T6 & mpu9250 module
  ******************************************************************************
  * @attention
  *
  * Modified :  https://github.com/xtr0d3m0n/MPU9250-STM32-HAL-libary
  *
  ******************************************************************************
**/


#include "mpu9250.h"
#include "i2c.h"


//const uint16_t _dev_add = 208;
// 400 kHz
//const uint32_t _i2cRate = 400000;



static uint8_t _buffer[21];
static uint8_t _mag_adjust[3];

__weak void MPU9250_OnActivate()
{
}


bool MPU9250_IsConnected()
{
	if(HAL_I2C_IsDeviceReady(&_MPU9250_I2C,_dev_add,1,HAL_MAX_DELAY)==HAL_OK)
		return true;
	else
		return false;
}

void MPU_I2C_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
	HAL_I2C_Mem_Write(&_MPU9250_I2C,_dev_add,WriteAddr,I2C_MEMADD_SIZE_8BIT,pBuffer,NumByteToWrite,HAL_MAX_DELAY);
}

void MPU_I2C_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
	uint8_t data = ReadAddr | READWRITE_CMD;
	HAL_I2C_Master_Transmit(&_MPU9250_I2C,_dev_add,&data,1,HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&_MPU9250_I2C,_dev_add,pBuffer,NumByteToRead,HAL_MAX_DELAY);
}




/* writes a byte to MPU9250 register given a register address and data */
void writeRegister(uint8_t subAddress, uint8_t data)
{

	MPU_I2C_Write(&data, subAddress, 1);
	HAL_Delay(10);
}

/* reads registers from MPU9250 given a starting register address, number of bytes, and a pointer to store data */
void readRegisters(uint8_t subAddress, uint8_t count, uint8_t* dest){

	MPU_I2C_Read(dest, subAddress, count);

}

/* writes a register to the AK8963 given a register address and data */
void writeAK8963Register(uint8_t subAddress, uint8_t data)
{
	// set slave 0 to the AK8963 and set for write
	writeRegister(I2C_SLV0_ADDR,AK8963_I2C_ADDR);

	// set the register to the desired AK8963 sub address
	writeRegister(I2C_SLV0_REG,subAddress);

	// store the data for write
	writeRegister(I2C_SLV0_DO,data);

	// enable I2C and send 1 byte
	writeRegister(I2C_SLV0_CTRL,I2C_SLV0_EN | (uint8_t)1);
}

/* reads registers from the AK8963 */
void readAK8963Registers(uint8_t subAddress, uint8_t count, uint8_t* dest)
{
	// set slave 0 to the AK8963 and set for read
	writeRegister(I2C_SLV0_ADDR, AK8963_I2C_ADDR | I2C_READ_FLAG);

	// set the register to the desired AK8963 sub address
	writeRegister(I2C_SLV0_REG,subAddress);

	// enable I2C and request the bytes
	writeRegister(I2C_SLV0_CTRL,I2C_SLV0_EN | count);

	// takes some time for these registers to fill
	HAL_Delay(1);

	// read the bytes off the MPU9250 EXT_SENS_DATA registers
	readRegisters(EXT_SENS_DATA_00,count,dest);
}

/* gets the MPU9250 WHO_AM_I register value, expected to be 0x71 */
static uint8_t whoAmI(){
	// read the WHO AM I register
	readRegisters(WHO_AM_I,1,_buffer);

	// return the register value
	return _buffer[0];
}

/* gets the AK8963 WHO_AM_I register value, expected to be 0x48 */
static int whoAmIAK8963(){
	// read the WHO AM I register
	readAK8963Registers(AK8963_WHO_AM_I,1,_buffer);
	// return the register value
	return _buffer[0];
}

/* starts communication with the MPU-9250 */
uint8_t MPU9250_Init()
{

	// select clock source to gyro
	writeRegister(PWR_MGMNT_1, CLOCK_SEL_PLL);
	// enable I2C master mode
	writeRegister(USER_CTRL, I2C_MST_EN);
	// set the I2C bus speed to 400 kHz
	writeRegister(I2C_MST_CTRL, I2C_MST_CLK);

	// set AK8963 to Power Down
	writeAK8963Register(AK8963_CNTL1,AK8963_PWR_DOWN);
	// reset the MPU9250
	writeRegister(PWR_MGMNT_1,PWR_RESET);
	// wait for MPU-9250 to come back up
	HAL_Delay(10);
	// reset the AK8963
	writeAK8963Register(AK8963_CNTL2,AK8963_RESET);
	// select clock source to gyro
	writeRegister(PWR_MGMNT_1,CLOCK_SEL_PLL);

	// check the WHO AM I byte, expected value is 0x71 (decimal 113) or 0x73 (decimal 115)
	uint8_t who = whoAmI();
	if((who != 0x71) && ( who != 0x73))
	{
		return 1;
	}

	// enable accelerometer and gyro
	writeRegister(PWR_MGMNT_2,SEN_ENABLE);

	// setting accel range to 16G as default
	writeRegister(ACCEL_CONFIG,ACCEL_FS_SEL_16G);

	// setting the gyro range to 2000DPS as default
	writeRegister(GYRO_CONFIG,GYRO_FS_SEL_250DPS);

	// setting bandwidth to 184Hz as default
	//TODO: 21-03-21 STJ 수정 184Hz에서 10Hz로
	writeRegister(ACCEL_CONFIG2,DLPF_10); //184

	// setting gyro bandwidth to 184Hz
	//TODO: 21-03-21 STJ 수정 184Hz에서 10Hz로
	writeRegister(CONFIG_M,DLPF_10); //184

	// setting the sample rate divider to 0 as default
	writeRegister(SMPDIV,0x00);

	// enable I2C master mode
	writeRegister(USER_CTRL,I2C_MST_EN);

	// set the I2C bus speed to 400 kHz
	writeRegister(I2C_MST_CTRL,I2C_MST_CLK);

	// check AK8963 WHO AM I register, expected value is 0x48 (decimal 72)
	if( whoAmIAK8963() != 0x48 )
	{
		return 1;
	}

	/* get the magnetometer calibration */
	// set AK8963 to Power Down
	writeAK8963Register(AK8963_CNTL1,AK8963_PWR_DOWN);

	HAL_Delay(100); // long wait between AK8963 mode changes

	// set AK8963 to FUSE ROM access
	writeAK8963Register(AK8963_CNTL1,AK8963_FUSE_ROM);

	// long wait between AK8963 mode changes
	HAL_Delay(100);

	// read the AK8963 ASA registers and compute magnetometer scale factors
	readAK8963Registers(AK8963_ASA, 3, _mag_adjust);


	// set AK8963 to Power Down
	writeAK8963Register(AK8963_CNTL1,AK8963_PWR_DOWN);

	// long wait between AK8963 mode changes
	HAL_Delay(100);

	// set AK8963 to 16 bit resolution, 100 Hz update rate
	writeAK8963Register(AK8963_CNTL1,AK8963_CNT_MEAS2);

	// long wait between AK8963 mode changes
	HAL_Delay(100);

	// select clock source to gyro
	writeRegister(PWR_MGMNT_1,CLOCK_SEL_PLL);

	// instruct the MPU9250 to get 7 bytes of data from the AK8963 at the sample rate
	readAK8963Registers(AK8963_HXL,7,_buffer);

	// successful init, return 0
	return 0;
}

/* sets the accelerometer full scale range to values other than default */
void MPU9250_SetAccelRange(AccelRange range)
{
	writeRegister(ACCEL_CONFIG, range);
}

/* sets the gyro full scale range to values other than default */
void MPU9250_SetGyroRange(GyroRange range)
{
	writeRegister(GYRO_CONFIG, range);
}

/* sets the DLPF bandwidth to values other than default */
void MPU9250_SetDLPFBandwidth(DLPFBandwidth bandwidth)
{
	writeRegister(ACCEL_CONFIG2,bandwidth);
	writeRegister(CONFIG_M,bandwidth);
}

/* sets the sample rate divider to values other than default */
void MPU9250_SetSampleRateDivider(SampleRateDivider srd)
{
	/* setting the sample rate divider to 19 to facilitate setting up magnetometer */
	writeRegister(SMPDIV,19);

	if(srd > 9)
	{
		// set AK8963 to Power Down
		writeAK8963Register(AK8963_CNTL1,AK8963_PWR_DOWN);

		// long wait between AK8963 mode changes
		HAL_Delay(100);

		// set AK8963 to 16 bit resolution, 8 Hz update rate
		writeAK8963Register(AK8963_CNTL1,AK8963_CNT_MEAS1);

		// long wait between AK8963 mode changes
		HAL_Delay(100);

		// instruct the MPU9250 to get 7 bytes of data from the AK8963 at the sample rate
		readAK8963Registers(AK8963_HXL,7,_buffer);

	}
	else
	{
		// set AK8963 to Power Down
		writeAK8963Register(AK8963_CNTL1,AK8963_PWR_DOWN);
		// long wait between AK8963 mode changes
		HAL_Delay(100);
		// set AK8963 to 16 bit resolution, 100 Hz update rate
		writeAK8963Register(AK8963_CNTL1,AK8963_CNT_MEAS2);

		// long wait between AK8963 mode changes
		HAL_Delay(100);

		// instruct the MPU9250 to get 7 bytes of data from the AK8963 at the sample rate
		readAK8963Registers(AK8963_HXL,7,_buffer);
	}

	writeRegister(SMPDIV, srd);
}

/* read the data, each argiment should point to a array for x, y, and x */
void MPU9250_GetData(int16_t* AccData, int16_t* MagData, int16_t* GyroData)
{
	// grab the data from the MPU9250
	readRegisters(ACCEL_OUT, 21, _buffer);

	// combine into 16 bit values
	AccData[0] = (((int16_t)_buffer[0]) << 8) | _buffer[1];
	AccData[1] = (((int16_t)_buffer[2]) << 8) | _buffer[3];
	AccData[2] = (((int16_t)_buffer[4]) << 8) | _buffer[5];
	GyroData[0] = (((int16_t)_buffer[8]) << 8) | _buffer[9];
	GyroData[1] = (((int16_t)_buffer[10]) << 8) | _buffer[11];
	GyroData[2] = (((int16_t)_buffer[12]) << 8) | _buffer[13];

	int16_t magx = (((int16_t)_buffer[15]) << 8) | _buffer[14];
	int16_t magy = (((int16_t)_buffer[17]) << 8) | _buffer[16];
	int16_t magz = (((int16_t)_buffer[19]) << 8) | _buffer[18];

	MagData[0] = (int16_t)((float)magx * ((float)(_mag_adjust[0] - 128) / 256.0f + 1.0f));
	MagData[1] = (int16_t)((float)magy * ((float)(_mag_adjust[1] - 128) / 256.0f + 1.0f));
	MagData[2] = (int16_t)((float)magz * ((float)(_mag_adjust[2] - 128) / 256.0f + 1.0f));
}


/* 상보 필터 계산을 위한 축 구하기 함수*/

void MPU6050_GetData_Axis(int16_t* Ac_X, int16_t* Ac_Y, int16_t* Ac_Z, int16_t* Gy_X, int16_t* Gy_Y, int16_t* Gy_Z, int16_t* Ma_X,int16_t* Ma_Y, int16_t* Ma_Z)
{

	uint8_t Buffer[19] = {0};
	int16_t InBuffer[8] = {0};

	readRegisters(ACCEL_OUT, 19, Buffer);


	/* 가속도계 */
	InBuffer[0] = (((int16_t)Buffer[0]) << 8) | Buffer[1];
	InBuffer[1] = (((int16_t)Buffer[2]) << 8) | Buffer[3];
	InBuffer[2] = (((int16_t)Buffer[4]) << 8) | Buffer[5];

	/* 자이로계 */
	InBuffer[3] = (((int16_t)Buffer[8]) << 8) |  Buffer[9];
	InBuffer[4] = (((int16_t)Buffer[10]) << 8) | Buffer[11];
	InBuffer[5] = (((int16_t)Buffer[12]) << 8) | Buffer[13];

	/* 지자기계 */
	InBuffer[6] = (((int16_t)Buffer[15]) << 8) | Buffer[14];
	InBuffer[7] = (((int16_t)Buffer[17]) << 8) | Buffer[16];
	InBuffer[8] = (((int16_t)Buffer[19]) << 8) | Buffer[18];



	/* 가속도  스케일 비조정  */
    *Ac_X = *(InBuffer + 0);
	*Ac_Y = *(InBuffer + 1);
	*Ac_Z = *(InBuffer + 2);

	/* 자이로 스케일 비조정 */
	*Gy_X = *(InBuffer + 3);
	*Gy_Y = *(InBuffer + 4);
	*Gy_Z = *(InBuffer + 5);

	/* 지자계 스케일 조정 */
	*Ma_X = *(InBuffer + 6)* ((float)(_mag_adjust[0] - 128) / 256.0f + 1.0f);
	*Ma_Y = *(InBuffer + 7)* ((float)(_mag_adjust[1] - 128) / 256.0f + 1.0f);
	*Ma_Z = *(InBuffer + 8)* ((float)(_mag_adjust[2] - 128) / 256.0f + 1.0f);


}


 void calibrate(int16_t* Base_Ax , int16_t* Base_Ay, int16_t* Base_Az, int16_t*Base_Gx, int16_t* Base_Gy, int16_t* Base_Gz)	//초기값 읽기
{
	int8_t   cal = 10;
	int16_t  Ac_X,    Ac_Y,   Ac_Z,   Gy_X,   Gy_Y,   Gy_Z ;
	int16_t	 TempAx , TempAy, TempAz, TempGx, TempGy, TempGz, TempMx, TempMy, TempMz;

	for(int i=0; i<cal; i++)	//평균
	{
 		 MPU6050_GetData_Axis(&TempAx, &TempAy, &TempAz, &TempGx, &TempGy, &TempGz, &TempMx, &TempMy, &TempMz);

		 Ac_X  +=  -TempAx - 16383;
		 Ac_Y  +=  -TempAy;
		 Ac_Z  +=   TempAz;

		 Gy_X  +=   TempGx;
		 Gy_Y  +=   TempGy;
		 Gy_Z  +=   TempGz;

		 delay(100);
	}

	Ac_X /= cal;
	Ac_Y /= cal;
	Ac_Z /= cal;

	Gy_X /= cal;
	Gy_Y /= cal;
	Gy_Z /= cal;

	*Base_Ax = Ac_X;	//초기 값으로 저장
	*Base_Ay = Ac_Y;
	*Base_Az = Ac_Z;

	*Base_Gx = Gy_X;
	*Base_Gy = Gy_Y;
	*Base_Gz = Gy_Z;


}
