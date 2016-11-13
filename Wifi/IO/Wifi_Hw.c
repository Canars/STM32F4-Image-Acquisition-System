/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "Wifi_Hw.h"

static unsigned char ucSpiBuf[HW_IODATA_SIZE];

static int Hw_Write(int nSize)
{
	GSPI_Write (SPI1, ucSpiBuf, nSize);

	return nSize;
}

static int Hw_Read(int nSize)
{
	GSPI_Read (SPI1, ucSpiBuf, nSize);

	return nSize;
}

BOOL Hw_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GSPI_Init(SPI1);
	
	// Enable GPIO clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	// PDN: PC0
	GPIO_InitStructure.GPIO_Pin = WIFI_CTRL2_PDN_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(WIFI_CTRL2_PORT, &GPIO_InitStructure);

	// RST: PC1
	GPIO_InitStructure.GPIO_Pin = WIFI_CTRL3_RST_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(WIFI_CTRL3_PORT, &GPIO_InitStructure);
	
	if (Hw_IntrInit() != TRUE)
		return FALSE;
	if (Hw_DmaInit() != TRUE)
		return FALSE;

	TRACE("-Hw_Init()\r\n");

	return TRUE;
}

BOOL Hw_Deinit(void)
{
	TRACE("+Hw_Deinit()\r\n");

	return TRUE;
}

BOOL Hw_IntrInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
	TRACE("+Hw_IntrInit()\r\n");

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	// SPI interrupt pin PC4 GPIO config
	GPIO_InitStructure.GPIO_Pin = WIFI_CTRL3_INT_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(WIFI_CTRL3_PORT, &GPIO_InitStructure);

	// Ext interrupt config
#ifdef  VECT_TAB_RAM
	// Set the Vector Table base location at 0x20000000
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  // VECT_TAB_FLASH
	// Set the Vector Table base location at 0x08000000
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Configure EXTI Line4 to generate an interrupt on falling edge
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource4);/*连接EXTI4到PC4*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_GenerateSWInterrupt(EXTI_Line4);
	// Disable hw interrupt first
	Hw_CloseInterrupts();

	TRACE("-Hw_IntrInit()\r\n");

	return TRUE;
}

BOOL Hw_DmaInit(void)
{
	TRACE("+Hw_DmaInit()\r\n");

	return TRUE;
}

BOOL Hw_PowerOn()
{
	TRACE("+Hw_PowerOn()\r\n");

	// WIFI power up.
	WIFI_POWER_UP();
	delay_ms(1);
	// Chipselect Enable.
	GSPI_CS_ENABLE();
	delay_ms(1);
	Hw_Reset();
	// Chipselect disable first.
	GSPI_CS_DISABLE();
#if 1
	TRACE("SPI testing...\r\nPlease confirm that the value read is equal with write...\r\n");
	{
		int i;
		WORD stat, stat0 = 0;

		for (i = 0 ; i < 100; i ++) {
			stat = stat0;
			TRACE("Write: 0x%04X\r\n", stat);
			Hw_WriteRegister(0x64, (PVOID)&stat, 2);
			stat = 0;
			Hw_ReadRegister(0x64, (PVOID)&stat, 2);
			TRACE("Read: 0x%04X\r\n", stat);

			if (stat != stat0) {
				TRACE("SPI test failed!");
				break;
			}
			stat0 ++;
		}
	}
	TRACE("SPI test done.\r\n");
#endif

	TRACE("-Hw_PowerOn()\r\n");

	return TRUE;
}

BOOL Hw_PowerOff()
{
	WIFI_POWER_DOWN();

	return TRUE;
}

int Hw_WriteRegister(int nRegNo, PVOID pBuf, int nSize)
{
	PBYTE pCur, pEnd, pBufPos;
	PBYTE aData = ucSpiBuf;
	int nBufLen, nDmaLen, nResidue;

	GSPI_CS_ENABLE();

	nResidue = nSize;
	pBufPos = (PBYTE)pBuf;

#if (/*defined(SPI_USE_DMA) || */defined(GSPI_USE_8BIT))
	aData[0] = HIBYTE(nRegNo) | 0x80;
	aData[1] = LOBYTE(nRegNo);
#else // else for 16BIT
	aData[1] = HIBYTE(nRegNo) | 0x80;
	aData[0] = LOBYTE(nRegNo);
#endif
	pCur = aData + 2;
	while (nResidue > 0) {
		pEnd = aData + HW_IODATA_SIZE;
		nBufLen = pEnd - pCur;
		if (nResidue < nBufLen) {
			nBufLen = nResidue;
			pEnd = pCur + nResidue;
		}
		while (pCur < pEnd) {
#if (/*defined(SPI_USE_DMA) || */defined(GSPI_USE_8BIT))
			pCur[1] = *pBufPos ++;
			pCur[0] = *pBufPos ++;
#else // else for 16BIT
			pCur[0] = *pBufPos ++;
			pCur[1] = *pBufPos ++;
#endif
			pCur += 2;
		}
		nDmaLen = pEnd - aData;
		if (Hw_Write(nDmaLen) != nDmaLen)
			break;
		nResidue -= nBufLen;
		pCur = aData;
	}

	GSPI_CS_DISABLE();

	return nSize - nResidue;
}

int Hw_ReadRegister(int nRegNo, PVOID pBuf, int nSize)
{
	PBYTE pCur,pEnd,pBufPos;
	PBYTE aData = ucSpiBuf;
	int nBufLen,nDmaLen,nResidue;

	GSPI_CS_ENABLE();

	nResidue = nSize;
	nDmaLen = (int)ucSpiDummyClk * 2 + 2;
	FillMemory(aData, 0xFF, nDmaLen);
#if (/*defined(SPI_USE_DMA) || */defined(GSPI_USE_8BIT))
	aData[0] = HIBYTE(nRegNo);
	aData[1] = LOBYTE(nRegNo);
#else // else for 16BIT
	aData[1] = HIBYTE(nRegNo);
	aData[0] = LOBYTE(nRegNo);
#endif
	if(Hw_Write(nDmaLen) == nDmaLen) {
		pBufPos = (PBYTE)pBuf;
		pCur = aData;
		while(nResidue > 0) {
			pEnd = aData + HW_IODATA_SIZE;
			nBufLen = pEnd - pCur;
			if(nResidue < nBufLen) {
				nBufLen = nResidue;
				pEnd = pCur + nResidue;
			}
			nDmaLen = pEnd - aData;
#ifndef GSPI_GPIO_MODE
			if(Hw_Read(nDmaLen) != nDmaLen)
				break;
#else
			while (nDmaLen --)
				*pCur ++ = (BYTE)GSPI_ReadByte(&Spi);
			pCur = aData;
#endif
			while(pCur < pEnd) {
#if (/*defined(SPI_USE_DMA) || */defined(GSPI_USE_8BIT))
				*pBufPos ++ = pCur[1];
				*pBufPos ++ = pCur[0];
#else // else for 16BIT
				*pBufPos ++ = pCur[0];
				*pBufPos ++ = pCur[1];
#endif
				pCur += 2;
			}
			nResidue -= nBufLen;
			pCur = aData;
		}
	}

	GSPI_CS_DISABLE();

	return nSize;
}

BOOL Hw_OpenInterrupts(void)
{
	TRACE("+Hw_OpenInterrupts()\r\n");

	// STM32 IMR write 1 is ENABLE!!!!!,0 is DISABLE!!!!
	EXTI->IMR |= (1 << 4);

	return TRUE;
}

BOOL Hw_CloseInterrupts(void)
{
	TRACE("+Hw_CloseInterrupts()\r\n");

	// STM32 IMR write 1 is ENABLE!!!!!,0 is DISABLE!!!!
	EXTI->IMR &= ~(1 << 4);

	return TRUE;
}

BOOL Hw_Reset(void)
{
	TRACE("+Hw_Reset()\r\n");

	WIFI_GSPICLK_RESET();
	delay_ms(10);
	WIFI_GSPICLK_RELEASE_RESETING();
	delay_ms(10);

	TRACE("-Hw_Reset()\r\n");

	return TRUE;
}
