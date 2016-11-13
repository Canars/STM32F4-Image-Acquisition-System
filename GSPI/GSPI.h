/**
  ******************************************************************************
  * @file    GSPI.h
  * @author  赵灿
  * @version V1.0
  * @date    8-April-2014
  * @brief   The header of GSPI.c
  ******************************************************************************
*/

#ifndef __GSPI_H__
#define __GSPI_H__
//
#include "stm32f4xx.h"
// Macros define
//

// Compile config
/*定义SPI使用8位数据位或16位数据位*/
#define GSPI_USE_8BIT
//#define GSPI_USE_16BIT  16位暂时不好用，原因不明

#define GSPI_CS_ENABLE()				GPIOC->BSRRH = GPIO_Pin_5 //PC5--CS
#define GSPI_CS_DISABLE()				GPIOC->BSRRL = GPIO_Pin_5

//#define GSPI_GPIO_GET_PIN(pSpi, pin)			pSpi->pGPIOPort->IDR&pin
//#define GSPI_GPIO_SET_PIN(pSpi, pin)			pSpi->pGPIOPort->BSRRL=pin
//#define GSPI_GPIO_CLR_PIN(pSpi, pin)			pSpi->pGPIOPort->BSRRH=pin

//
// Structs define
//
#define GSPI_MODE_SPI						0
#define GSPI_MODE_GPIO						1

typedef struct _STM32SPI {
	SPI_TypeDef* SPIx;
	GPIO_TypeDef* pGPIOPort;
	uint16_t	usCsPin;
	uint16_t	usClkPin;
	uint16_t	usMisoPin;
	uint16_t	usMosiPin;
	uint8_t ucMode;
} Stm32Spi, *PSTM32SPI;

//
// Exported functions declare
//
void GSPI_Init(SPI_TypeDef* SPIx);
uint16_t GSPI_WriteByte(SPI_TypeDef* SPIx, uint16_t usData);
uint16_t GSPI_ReadByte(SPI_TypeDef* SPIx);
#ifdef GSPI_USE_DMA
void GSPI_WriteDMA (PSTM32SPI pSpi, unsigned char* pBuffer, u32 nSize);
void GSPI_ReadDMA (PSTM32SPI pSpi, unsigned char* pBuffer, u32 nSize);
#endif
void GSPI_Write (SPI_TypeDef* SPIx, unsigned char* pBuffer, u32 nSize);
void GSPI_Read (SPI_TypeDef* SPIx, unsigned char* pBuffer, u32 nSize);

#endif // __GSPI_H__
