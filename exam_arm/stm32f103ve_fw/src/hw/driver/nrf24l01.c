/**
  ******************************************************************************
  * @file    nrf24l01.c
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


#include "nrf24l01.h"
#include "spi.h"



const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};  // Transmit address
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};  // Receive address





/* TODO: nRF24L01 Pin 변경 시 헤더파일만 변경하면 됨 (2)*/
void NRF24L01_Init(void)
{
     /* 클럭 활성화는  bsp.c 에서 처리 함*/

     GPIO_InitTypeDef GPIO_InitStruct = {0};

     /*Configure GPIO pin Output Level */
     HAL_GPIO_WritePin(NRF24L01_CE_PORT , NRF24L01_CE_PIN , GPIO_PIN_RESET);
     HAL_GPIO_WritePin(NRF24L01_SPI_CS_PORT, NRF24L01_SPI_CS_PIN, GPIO_PIN_SET);

     /*Configure GPIO pins : PBPin PBPin */
     GPIO_InitStruct.Pin = NRF24L01_CE_PIN|NRF24L01_SPI_CS_PIN;
     GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
     GPIO_InitStruct.Pull = GPIO_NOPULL;
     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

     /*Configure GPIO pin : PtPin */
     GPIO_InitStruct.Pin =  NRF24L01_IRQ_PIN;
     GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
     GPIO_InitStruct.Pull = GPIO_PULLUP;
     HAL_GPIO_Init(NRF24L01_IRQ_PORT , &GPIO_InitStruct);
}




/**
     * @Function:         SPI 속도 설정 함수
     * @Input parameters: None
     * @Return value:     None
     * @Description:      SPI speed = fAPB2/frequency division factor
     *                    SPI_BaudRate_Prescaler: SPI_BAUDRATEPRESCALER_2 ~ SPI_BAUDRATEPRESCALER_256
     *                 The fAPB2 clock is 72Mhz:(STM32103C8T6: [ APB2 -> SPI1 ])
  */
void SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
         assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler)); //Judging validity
         __HAL_SPI_DISABLE(&NRF24L01_SPI_PORT); //Close SPI
         NRF24L01_SPI_PORT.Instance->CR1&=0XFFC7; //bits 3-5 are cleared, used to set the baud rate
         NRF24L01_SPI_PORT.Instance->CR1|=SPI_BaudRatePrescaler;//Set SPI speed
         __HAL_SPI_ENABLE(&NRF24L01_SPI_PORT); //Enable SPI

}


/**
     * @Function:             데이터 1byte를  SPI로 읽고 쓰고, 1byte의 데이터를 수신하는 함수
     * @Input parameters:  byte: 송신할 데이터
     * @Return value:      uint8_t: 수신한 데이터
     * @Description:       None
  */

uint8_t SPIx_ReadWriteByte(SPI_HandleTypeDef* hspi,uint8_t byte)
{
  uint8_t d_read,d_send=byte;
                            /* 사용하는 SPIx, 송신할 데이터 값, 수신받을 데이터, 데이터의 길이, 타임오버 값*/
  if(HAL_SPI_TransmitReceive(hspi,&d_send,&d_read,1,0xFF)!=HAL_OK)
  {
    d_read=0xFF;
  }
  return d_read;
}


/**
     * Function:        nRF24L01 감지 함수
     * Input parameters: none
     * Return value:     0, success; 1, failure
     * Description:     None
  */

uint8_t NRF24L01_Check(void)
{
   uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
   uint8_t i;

    SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi speed is 9Mhz ((The maximum SPI clock of 24L01 is 10Mhz, it doesn’t matter if it is bigger here)
    NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//Write a 5-byte address.
    NRF24L01_Read_Buf(TX_ADDR,buf,5); //Read the written address
   for(i=0;i<5;i++)
   {
      if(buf[i]!=0XA5)
         break;
   }
    if(i!=5)return 1;//Detect 24L01 error
    return 0; //24L01 detected
}


/**
     * Function:        SPI, 레지스터 값 쓰기 함수
     * Input parameters: reg: 레지스터 주소 / value:레지스터 주소에 쓸 값
     * Return value:     status: 레지스터 상태
     * Description:     none
  *
  */
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
   uint8_t status;
     NRF24L01_SPI_CS_ENABLE(); //Enable SPI transmission
     status =SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,reg);//Send register number
     SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,value); //Write the value of the register
     NRF24L01_SPI_CS_DISABLE(); //Disable SPI transmission
     return(status); //return status value
}


/**
     * Function:       SPI, 레지스터 값 읽기 함수
     * Input parameters: reg: 읽을 레지스터 값
     * Return value:     reg_val:레지스터 값
     * Explanation:     none
  *
  */
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
   uint8_t reg_val;
      NRF24L01_SPI_CS_ENABLE(); //Enable SPI transmission
     SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,reg); //Send register number
     reg_val=SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,0XFF);//Read register content
     NRF24L01_SPI_CS_DISABLE(); //Disable SPI transmission
     return(reg_val); //return status value
}


/**
     * Function:         지정된 위치에서 지정된 길이의 데이터를 읽는 함수
     * Input parameters: reg: 레지스터(위치)/ *pBuf: 데이터 포인터/ len: 데이터 길이
     * Return value:     status: 이번에 읽은 레지스터 상태 값
     * Description:        none
  *
  */
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
   uint8_t status, uint8_t_ctr;

     NRF24L01_SPI_CS_ENABLE(); //Enable SPI transmission
//   HAL_Delay(20);
     status=SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,reg);//Send register value (position) and read status value
    for(uint8_t_ctr=0;uint8_t_ctr<len;uint8_t_ctr++)
  {
         pBuf[uint8_t_ctr]=SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,0XFF);//Read data
  }
     NRF24L01_SPI_CS_DISABLE(); //Close SPI transmission
     return status; //Return the status value read
}



/**
     * Function:         지정된 위치에서 지정된 길이의 데이터를 쓰는 함수
     * Input parameters: reg: 레지스터(위치) *pBuf: 데이터 포인터 len: 데이터 길이
     * Return value:     status: 이번에 쓴 레지스터 상태 값
     * Description:        none
  *
  */
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
   uint8_t status,uint8_t_ctr;
      NRF24L01_SPI_CS_ENABLE(); //Enable SPI transmission
//   HAL_Delay(20);
     status = SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,reg);//Send the register value (position) and read the status value
  for(uint8_t_ctr=0; uint8_t_ctr<len; uint8_t_ctr++)
  {
         SPIx_ReadWriteByte(&NRF24L01_SPI_PORT,*pBuf++); //Write data
  }
     NRF24L01_SPI_CS_DISABLE(); //Close SPI transmission
     return status; //Return the status value read
}



/**
     * Function:          nRF24L01에서 데이터를 한번 송신하는 함수
     * Input parameters:    *txbuf: 전송할 데이터의 첫 번째 주소
     * Return value:      TX_OK: 송신 성공  / 0xff: 송신 실패
     * Description:       none
  *
  */
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
   uint8_t sta;

    SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //The spi speed is 9Mhz (the maximum SPI clock of 24L01 is 10Mhz)
    NRF24L01_CE_LOW();
     NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//write data to TX BUF 32 bytes
     NRF24L01_CE_HIGH();//Start sending

    while(NRF24L01_IRQ_PIN_READ()!=0);//Wait for sending completion

    sta=NRF24L01_Read_Reg(STATUS); //Read the value of the status register
    NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //Clear TX_DS or MAX_RT interrupt flag
    if(sta&MAX_TX)//Maximum number of retransmissions reached
   {
       NRF24L01_Write_Reg(FLUSH_TX,0xff);//Clear TX FIFO register
      return MAX_TX;
   }
    if(sta&TX_OK)//Send completed
   {
      return TX_OK;
   }
    return 0xff;//Failed to send for other reasons
}



/**
     * Function:          nRF24L01에서 데이터를 한번 수신하는 함수
     * Input parameters:    *rxbuf: 수신할 데이터의 첫 번째 주소
     * Return value:      0: 수신 성공  / 0: 수신 실패
     * Description:       none
  *
  */
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
    uint8_t sta;

    SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //The spi speed is 9Mhz (the maximum SPI clock of 24L01 is 10Mhz)
    sta=NRF24L01_Read_Reg(STATUS); //Read the value of the status register
    NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //Clear TX_DS or MAX_RT interrupt flag
    if(sta&RX_OK)//Data received
   {
       NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//Read data
       NRF24L01_Write_Reg(FLUSH_RX,0xff);//Clear RX FIFO register
      return 0;
   }
    return 1;//No data received
}


/**
     * Function:          nRF24L01 RX모드로 초기화 하는 함수
     * Input parameters:    none
     * Return value:       none
     * Description:       nRF24L01 DataSheet 레지스터 맵 참고
  *
  */
void NRF24L01_RX_Mode(void)
{
    NRF24L01_CE_LOW();
     NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0F);//Configure the parameters of the basic working mode; PWR_UP, EN_CRC, 16BIT_CRC
     NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); //Enable automatic response of channel 0
     NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//Enable the receive address of channel 0
     NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40); //Set RF communication frequency
     NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//Set TX transmission parameters, 0db gain, 2Mbps, low noise gain on
     NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//Select the effective data width of channel 0
     NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);//write RX node address
     NRF24L01_CE_HIGH(); //CE is high, enter the receiving mode
     HAL_Delay(1); //안정화 시간
}



/**
     * Function:          nRF24L01 TX모드로 초기화 하는 함수
     * Input parameters:    none
     * Return value:       none
     * Description:       nRF24L01 DataSheet 레지스터 맵 참고
  *
  */
void NRF24L01_TX_Mode(void)
{
    NRF24L01_CE_LOW();
     NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//Write TX node address
     NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //Set the TX node address, mainly to enable ACK

     NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); //Enable automatic response of channel 0
     NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //Enable the receiving address of channel 0
 // NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0xff);//Set the automatic retransmission interval time: 4000us + 86us; the maximum number of automatic retransmissions: 15 times
    NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//Set the interval of automatic retransmission://500us + 86us; the maximum number of automatic retransmissions: 10 times
     NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40); //Set the RF channel to 40
     NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); //Set TX transmission parameters, 0db gain, 2Mbps, low noise gain on
     NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e); //Configure the parameters of the basic working mode; PWR_UP, EN_CRC, 16BIT_CRC, receive mode, open all interrupts
    NRF24L01_CE_HIGH();//CE is high, start sending after 10us
     HAL_Delay(1);//안정화 대기 시간
}
