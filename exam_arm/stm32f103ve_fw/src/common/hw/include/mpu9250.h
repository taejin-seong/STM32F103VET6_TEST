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


   /* Target: STM32F103C8T6
    *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                                             *
    *            MPU-9250 GPIO Configuration                *
    *                                            		    *
    *                SCL   <------ PB10(I2C1)               *
    *                SDA   <------ PB11(I2C1)               *
    *                                                		*
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                 	 	 	 */


#include "hw_def.h"



#ifdef _USE_HW_MPU9250


/* I2C Setting */

#define  _MPU9250_I2C			 hi2c2
#define _i2cRate 				 400000 	//400 kHz

/*MPU9250 addr */
#define _dev_add 				 208

/* MPU9250 CMD Set */
#define READWRITE_CMD 			 0x80
#define MULTIPLEBYTE_CMD 		 0x40
#define DUMMY_BYTE 				 0x00


/* MPU9250 registers */
#define ACCEL_OUT				 0x3B
#define GYRO_OUT 				 0x43
#define TEMP_OUT  				 0x41
#define EXT_SENS_DATA_00  		 0x49
#define ACCEL_CONFIG  			 0x1C
#define ACCEL_FS_SEL_2G  		 0x00
#define ACCEL_FS_SEL_4G 		 0x08
#define ACCEL_FS_SEL_8G 		 0x10
#define ACCEL_FS_SEL_16G 		 0x18
#define GYRO_CONFIG 			 0x1B
#define GYRO_FS_SEL_250DPS 		 0x00
#define GYRO_FS_SEL_500DPS 		 0x08
#define GYRO_FS_SEL_1000DPS  	 0x10
#define GYRO_FS_SEL_2000DPS  	 0x18
#define ACCEL_CONFIG2	  		 0x1D
#define DLPF_184 				 0x01
#define DLPF_92  				 0x02
#define DLPF_41  				 0x03
#define DLPF_20  				 0x04
#define DLPF_10  				 0x05
#define DLPF_5  				 0x06
#define CONFIG_M  				 0x1A // nRF24L01.h의 CONFIG와 중복되어 CONFIG_M으로 수정
#define SMPDIV  				 0x19
#define INT_PIN_CFG  			 0x37
#define INT_ENABLE  			 0x38
#define INT_DISABLE  			 0x00
#define INT_PULSE_50US  		 0x00
#define INT_WOM_EN  			 0x40
#define INT_RAW_RDY_EN 		  	 0x01
#define PWR_MGMNT_1  			 0x6B
#define PWR_CYCLE  				 0x20
#define PWR_RESET  			     0x80
#define CLOCK_SEL_PLL  			 0x01
#define PWR_MGMNT_2  			 0x6C
#define SEN_ENABLE  			 0x00
#define DIS_GYRO  				 0x07
#define USER_CTRL  				 0x6A
#define I2C_MST_EN  			 0x20
#define I2C_MST_CLK  			 0x0D
#define I2C_MST_CTRL  			 0x24
#define I2C_SLV0_ADDR  			 0x25
#define I2C_SLV0_REG  			 0x26
#define I2C_SLV0_DO  			 0x63
#define I2C_SLV0_CTRL   		 0x27
#define I2C_SLV0_EN  			 0x80
#define I2C_READ_FLAG  			 0x80
#define MOT_DETECT_CTRL  		 0x69
#define ACCEL_INTEL_EN  		 0x80
#define ACCEL_INTEL_MODE  		 0x40
#define LP_ACCEL_ODR  			 0x1E
#define WOM_THR  				 0x1F
#define WHO_AM_I  				 0x75
#define FIFO_EN  				 0x23
#define FIFO_TEMP  				 0x80
#define FIFO_GYRO  				 0x70
#define FIFO_ACCEL  			 0x08
#define FIFO_MAG  				 0x01
#define FIFO_COUNT  			 0x72
#define FIFO_READ  				 0x74

/* AK8963 registers */
#define AK8963_I2C_ADDR 		 0x0C
#define AK8963_HXL 				 0x03
#define AK8963_CNTL1 			 0x0A
#define AK8963_PWR_DOWN 	 	 0x00
#define AK8963_CNT_MEAS1 		 0x12
#define AK8963_CNT_MEAS2 		 0x16
#define AK8963_FUSE_ROM 		 0x0F
#define AK8963_CNTL2 			 0x0B
#define AK8963_RESET 			 0x01
#define AK8963_ASA 				 0x10
#define AK8963_WHO_AM_I 		 0x00


typedef enum GyroRange_ {
	GYRO_RANGE_250DPS = 0,
	GYRO_RANGE_500DPS,
	GYRO_RANGE_1000DPS,
	GYRO_RANGE_2000DPS,
} GyroRange;

typedef enum AccelRange_ {
	ACCEL_RANGE_2G = 0,
	ACCEL_RANGE_4G,
	ACCEL_RANGE_8G,
	ACCEL_RANGE_16G,
} AccelRange;

typedef enum DLPFBandwidth_ {
	DLPF_BANDWIDTH_184HZ = 0,
	DLPF_BANDWIDTH_92HZ,
	DLPF_BANDWIDTH_41HZ,
	DLPF_BANDWIDTH_20HZ,
	DLPF_BANDWIDTH_10HZ,
	DLPF_BANDWIDTH_5HZ,
} DLPFBandwidth;

typedef enum SampleRateDivider_ {
	LP_ACCEL_ODR_0_24HZ = 0,
	LP_ACCEL_ODR_0_49HZ,
	LP_ACCEL_ODR_0_98HZ,
	LP_ACCEL_ODR_1_95HZ,
	LP_ACCEL_ODR_3_91HZ,
	LP_ACCEL_ODR_7_81HZ,
	LP_ACCEL_ODR_15_63HZ,
	LP_ACCEL_ODR_31_25HZ,
	LP_ACCEL_ODR_62_50HZ,
	LP_ACCEL_ODR_125HZ,
	LP_ACCEL_ODR_250HZ,
	LP_ACCEL_ODR_500HZ,
} SampleRateDivider;

uint8_t MPU9250_Init(void);
/* read the data, each argiment should point to a array for x, y, and x */
//void MPU9250_GetData(int16_t* AccData, int16_t* MagData, int16_t* GyroData);

/* sets the sample rate divider to values other than default */
void MPU9250_SetSampleRateDivider(SampleRateDivider srd);
/* sets the DLPF bandwidth to values other than default */
void MPU9250_SetDLPFBandwidth(DLPFBandwidth bandwidth);
/* sets the gyro full scale range to values other than default */
void MPU9250_SetGyroRange(GyroRange range);
/* sets the accelerometer full scale range to values other than default */
void MPU9250_SetAccelRange(AccelRange range);

/*21-03-16 STJ 수정 */
void MPU6050_GetData_Axis(int16_t* Ac_X, int16_t* Ac_Y, int16_t* Ac_Z, int16_t* Gy_X, int16_t* Gy_Y, int16_t* Gy_Z, int16_t* Ma_X,int16_t* Ma_Y, int16_t* Ma_Z);
void calibrate(int16_t* Base_Ax , int16_t* Base_Ay, int16_t* Base_Az, int16_t*Base_Gx, int16_t* Base_Gy, int16_t* Base_Gz);


#endif /* _USE_HW_MPU9250 */
