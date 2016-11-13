/**
  ******************************************************************************
  * @file    GSPI.c
  * @author  赵灿
  * @version V1.0
  * @date    8-April-2014
  * @brief   This file includes the spi driver for WM631
  ******************************************************************************
*/

#include "GSPI.h"

void GSPI_Init(SPI_TypeDef* SPIx)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* SPI1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	/* GPIOB clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC,ENABLE);

	/* Connect SPI1 pins to AF5 */
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);//PB3--SPI_SCK
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);//PB4--SPI_MISO
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);//PB5--SPI_MOSI
	
	/* Configure SPI1 GPIOs */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//SPI_CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);	
	
  /* Configure SPI1 */
  /* SPI1 DeInit */
	SPI_DeInit(SPIx);
		
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //全双工模式
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   //作为主机使用
#ifdef GSPI_USE_8BIT
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //数据长度8
#else
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;   //数据长度16
#endif
  SPI_InitStructure.SPI_CPOL  = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //软件设置NSS功能
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//2分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx,&SPI_InitStructure);
	/* Enable the SPI1 peripheral */
	SPI_Cmd(SPIx,ENABLE);
}

uint16_t GSPI_WriteByte(SPI_TypeDef* SPIx, uint16_t usData)
{
	// Loop while DR register in not emplty
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

	// Send byte through the SPI peripheral
	SPI_I2S_SendData(SPIx, usData);

	// Wait to receive a byte
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

	// Return the byte read from the SPI bus
	return SPI_I2S_ReceiveData(SPIx);
}

uint16_t GSPI_ReadByte(SPI_TypeDef* SPIx)
{
	return GSPI_WriteByte(SPIx, 0xFFFF);
}

void GSPI_Write (SPI_TypeDef* SPIx, unsigned char* pBuffer, u32 nSize)
{
	u32 i;
#ifdef GSPI_USE_8BIT
	unsigned char * p = pBuffer;
#else
	short* p = (short*)pBuffer;
	nSize >>= 1;
#endif
	for (i = 0; i < nSize; i ++)
		GSPI_WriteByte (SPIx, p[i]);
}

void GSPI_Read (SPI_TypeDef* SPIx, unsigned char* pBuffer, u32 nSize)
{
	u32 i;
#ifdef GSPI_USE_8BIT
	unsigned char * p = pBuffer;
#else
	short* p = (short*)pBuffer;
	nSize >>= 1;
#endif
	for (i = 0; i < nSize; i ++)
		p[i] = GSPI_ReadByte(SPIx);
}
