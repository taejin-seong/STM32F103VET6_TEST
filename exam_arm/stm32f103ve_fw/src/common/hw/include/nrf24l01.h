/**
  ******************************************************************************
  * @file    nrf24l01.h
  * @author  Edit by Sung Tae-jin
  * @version V1.0
  * @date    25-February-2021
  * @brief   Using STM32F103C8T6 & nRF24L01 module

  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
**/


   /* Target: STM32F103C8T6
    *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                                             *
    *            nRF24L01 GPIO Configuration                *
    *                                            		    *
    *                CE   <------ PB5                 		*
    *                CSN  <------ PB4                       *
    *                SCK  <------ PA5                       *
    *                MO   <------ PA7 (SPI1)                *
    *                MI   <------ PA6 (SPI1)                *
    *               IRQ   <------ PB3                       *
    *                                                		*
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                 	 	 	 */



#include "hw_def.h"



#ifdef _USE_HW_NRF24L01



/* Select the SPIx port, you used */
#define NRF24L01_SPI_PORT                         hspi1
//#define NRF24L01_SPI_PORT                       hspi2


/* GPIO configuration */
													  /* TODO: nRF24L01 GPIO Pin 변경 시 수정 (1)*/

#define NRF24L01_SPI_GPIO_CLK_ENABLE()                __HAL_RCC_GPIOA_CLK_ENABLE()
#define NRF24L01_SPI_GPIO_PORT                        GPIOA
#define NRF24L01_SPI_SCK_PIN                          GPIO_PIN_5  // 21.03.21 STJ 수정
#define NRF24L01_SPI_MISO_PIN                         GPIO_PIN_6  // 21.03.21 STJ 수정
#define NRF24L01_SPI_MOSI_PIN                         GPIO_PIN_7  // 21.03.21 STJ 수정

#define NRF24L01_SPI_CS_CLK_ENABLE()                  __HAL_RCC_GPIOB_CLK_ENABLE()
#define NRF24L01_SPI_CS_PORT                          GPIOB
#define NRF24L01_SPI_CS_PIN                           GPIO_PIN_4 // 21.03.21 STJ 수정
#define NRF24L01_SPI_CS_ENABLE()                      HAL_GPIO_WritePin(NRF24L01_SPI_CS_PORT, NRF24L01_SPI_CS_PIN, GPIO_PIN_RESET)
#define NRF24L01_SPI_CS_DISABLE()                     HAL_GPIO_WritePin(NRF24L01_SPI_CS_PORT, NRF24L01_SPI_CS_PIN, GPIO_PIN_SET)

#define NRF24L01_CE_CLK_ENABLE()                      __HAL_RCC_GPIOB_CLK_ENABLE()
#define NRF24L01_CE_PORT                              GPIOB
#define NRF24L01_CE_PIN                               GPIO_PIN_5 // 21.03.21 STJ 수정
#define NRF24L01_CE_LOW()                             HAL_GPIO_WritePin(NRF24L01_CE_PORT, NRF24L01_CE_PIN, GPIO_PIN_RESET)
#define NRF24L01_CE_HIGH()                            HAL_GPIO_WritePin(NRF24L01_CE_PORT, NRF24L01_CE_PIN, GPIO_PIN_SET)

#define NRF24L01_IRQ_CLK_ENABLE()                     __HAL_RCC_GPIOA_CLK_ENABLE()
#define NRF24L01_IRQ_PORT                             GPIOB
#define NRF24L01_IRQ_PIN                              GPIO_PIN_3 // 21.03.21 STJ 수정
#define NRF24L01_IRQ_PIN_READ()                       HAL_GPIO_ReadPin(NRF24L01_IRQ_PORT,NRF24L01_IRQ_PIN)


/* nRF24L01 송수신 데이터 크기 정의*/
#define TX_ADR_WIDTH                             5         // 5-byte 주소  크기
#define RX_ADR_WIDTH                         	 5         // 5 byte 주소  크기
#define TX_PLOAD_WIDTH                           32        // 32-byte 사용자 데이터 크기
#define RX_PLOAD_WIDTH                           32        // 32-byte 사용자  데이터 크기


/* nRF24L01 레지스터  작동 커맨드(마스크)  */
#define NRF_READ_REG                          	0x00        // 레지스터에 값을 읽어오며, 하위 5bit는 레지스터 주소
#define NRF_WRITE_REG                           0x20        // 레지스터에 값을 쓰며, 하위 5bit는 레지스터 주소
#define RD_RX_PLOAD                          	0x61        // RX-payload 를 읽기 (1~32 bytes)
#define WR_TX_PLOAD                             0xA0        // TX-payload 를 쓰기 (1~32 bytes)
#define FLUSH_TX                              	0xE1        // TX FIFO 레지스터를 지움, TX mode에서 사용 할 것.
#define FLUSH_RX                              	0xE2        // RX FIFO 레지스터를 지움, RX mode에서 사용 할 것 .
#define REUSE_TX_PL                           	0xE3        // 마지막 데이터 패킷을 재사용하기, 데이터 패킷이 지속적으로 전송됨.
#define NOP                                 	0xFF        // 작동 안하게하기,상태 레지스터를 읽는데 사용할 수 있음.




/* SPI(nRF24L01) 레지스터 주소 */
#define CONFIG                                	0x00       /* Configuration register address

                                                                 bit0: 1 receiving mode
                                                                       0 transmitting mode
                                                       	   	     bit1: electrical selection
                                                          	     bit2: CRC mode
                                                        	     bit3: CRC enable
                                                       	   	     bit4: Interrupt MAX_RT (Maximum Retransmission Interrupt) enable
                                                       	   	   	 bit5: Interrupt TX_DS enable
                                                      	  	  	 bit6: Interrupt RX_DR enable  */



#define EN_AA                                  0x01       // 채널 0~5에 해당되는 자동 응답 ('Auto Acknowledgment') 기능  bit 0~5  활성화
#define EN_RXADDR                              0x02       // RX 주소는 채널 0~5에 해당하는 bit 0~5만 가능.
#define SETUP_AW                               0x03       // 주소 크기 설정(모든 데이터 채널) bit1,0: 00 x /  01 3bytes / 10 4bytes / 11 5bytes
#define SETUP_RETR                             0x04       // 자동 재전송 설정, bit3:0: 자동 재전송 카운터 mode 설정 / bit7:4: 자동 재전송 지연  250*x+86u
#define RF_CH                                  0x05       // RF 채널, bit6:0: 작동 채널 주파수 설정
#define RF_SETUP                               0x06       // RF 설정, bit0: low noise amplifier gain 설정 / bit2:1: 전송전력 mode 설정(-18,-12,-6,0dBm) / bit3: 전송 속도 설정(0: 1Mbps, 1: 2Mbps)
#define STATUS                                 0x07        /* Status register

                                         	   	      	      bit0:   TX FIFO full flag
                                                   	   	      bit3:1: receiving data channel number (maximum: 6)
                                                   	   	   	  bit4:   reaching the maximum retransmission
                                                              bit5:   data transmission complete interrupt
                                                              bit6:   receive data interrupt
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 */
/*                                                     			  ↓   ↓   ↓   ↓   ↓
 STATUS 레지스터 Bit 설정 (MAX_TX ~ RX_OK) */
#define MAX_TX                                0x10       // The maximum number of sending interrupts /* STATUS bit4 설정 */
#define TX_OK                                 0x20       // TX transmission complete interrupt       /* STATUS bit5 설정 */
#define RX_OK                                 0x40       // Data interrupt received                  /* STATUS bit6 설정 */



#define OBSERVE_TX                            0x08       // 전송 감시 레지스터, bit3:0: 재전송된 패킷 카운터(새로운 패킷이 시작되어 전송되면 리셋됨) / bit7:4: 패킷 손실 카운터
#define CD                                    0x09       // 반송파 감지 레지스터
#define RX_ADDR_P0                            0x0A       // 데이터 채널 0 수신 주소, 최대 길이 5bytes, LSB에 먼저 쓰여짐
#define RX_ADDR_P1                            0x0B       // 데이터 채널 1 수신 주소, 최대 길이 5bytes, LSB에 먼저 쓰여임
#define RX_ADDR_P2                            0x0C       // 데이터 채널 2 수신 주소, lowest byte 를 설정 할 수 있으며  high byte는 반드시 RX_ADDR_P1[39:8]와 같아야함
#define RX_ADDR_P3                            0x0D       // 데이터 채널 3 수신 주소, lowest byte 를 설정 할 수 있으며,high byte는 반드시 RX_ADDR_P1[39:8]와 같아야함
#define RX_ADDR_P4                            0x0E       // 데이터 채널 4 수신 주소, lowest byte 를 설정 할 수 있으며  high byte는 반드시 RX_ADDR_P1[39:8]와 같아야함
#define RX_ADDR_P5                            0x0F       // 데이터 채널 5 수신 주소, lowest byte 를 설정 할 수 있으며  high byte는 반드시 RX_ADDR_P1[39:8]와 같아야함
#define TX_ADDR                               0x10       // 송신 주소(ShockBurstTM mode에서),RX_ADDR_P0 주소와 같음
#define RX_PW_P0                              0x11       // 수신 데이터 채널 0에 있는  payload byte의 수(1~32bytes) 0으로 설정 x (0: Pipe not used)
#define RX_PW_P1                              0x12       // 수신 데이터 채널 1에 있는  payload byte의 수(1~32bytes) 0으로 설정 x (0: Pipe not used)
#define RX_PW_P2                              0x13       // 수신 데이터 채널 2에 있는  payload byte의 수(1~32bytes) 0으로 설정 x (0: Pipe not used)
#define RX_PW_P3                              0x14       // 수신 데이터 채널 3에 있는  payload byte의 수(1~32bytes) 0으로 설정 x (0: Pipe not used)
#define RX_PW_P4                              0x15       // 수신 데이터 채널 4에 있는  payload byte의 수(1~32bytes) 0으로 설정 x (0: Pipe not used)
#define RX_PW_P5                              0x16       // 수신 데이터 채널 5에 있는  payload byte의 수(1~32bytes) 0으로 설정 x (0: Pipe not used)
#define NRF_FIFO_STATUS                       0x17       /* FIFO status register

                                                           bit0:   RX FIFO register empty flag;
                                                           bit1:    RX FIFO full flag
                                                           bit2:3:  reserved
                                                           bit4:    TX FIFO empty flag
                                                           bit5:    TX FIFO full flag
                                                           bit6:    1 cyclically send the last packet.
                                                                    0 not cyclic
                                                                				*/





void NRF24L01_Init(void);                                         // Configure to NRF24L01 GPIO
void NRF24L01_RX_Mode(void);                                     // Configure to receive mode
void NRF24L01_TX_Mode(void);                                     // Configure to transmit mode
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uint8_ts);   // write data area
uint8_t NRF24L01_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uint8_ts);    // Read data area
uint8_t NRF24L01_Read_Reg(uint8_t reg);                            // Read register
uint8_t NRF24L01_Write_Reg(uint8_t reg, uint8_t value);                // Write register
uint8_t NRF24L01_Check(void);                                     // Check if 24L01 exists
uint8_t NRF24L01_TxPacket(uint8_t *txbuf);                         // Send a packet of data
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf);                         // Receive a packet of data





#endif /*_USE_HW_NRF24L01 */
