/**
  ******************************************************************************
  * @file    usart.c
  * @author  赵灿
  * @version V1.0
  * @date    1-April-2014
  * @brief   This file includes the driver for STM32F407VGT6's usart
	* @attention:          
						 1、使用stm32f4discovery时，不能使用USART1，USART1的PA9脚已经作为VBUS_FS使用，强行使用串口会出现乱码。
							  如若使用串口，请使用其他串口。参见stm32f4 dicovery原理图。
						 2、stm32f4固件库默认HSE_VALUE为25MHZ，而板载晶振为8MHZ,需修改stm32f4xx_conf.h，重定义HSE_VALUE为8MHZ。否则串口也会出现乱码。
								#if defined  (HSE_VALUE) 
								#undef HSE_VALUE 
								#define HSE_VALUE    ((uint32_t)8000000) 
								#endif
  ******************************************************************s************
*/
#include "usart.h"
#include "dcmi_ov2640.h"
USART_STRUCT usart_struct;
/**
  * @brief  Initializes the usart GPIO
  * @param  None
  * @retval None
  */
void usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	/* Connect USART pins to AF7 */
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART1);//USART2_TX
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART1);//USART2_RX
	/*USART2_TX Configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHZ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*USART2_RX Configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2,&USART_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
}

void USART2_IRQHandler(void)
{
	u8 data;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART2);//读取接收到的数据
		switch(data)
		{
			case '\r':
			case '\n':
				usart_struct.USART_RX_BUF[usart_struct.USART_RX_Cnt] = '\0';
			  usart_SendString("\r\n");
				usart_struct.USART_Sta |= USART_STA_RECEIVED;
				break;
			case '\0'://nul
				break;
			case 0x03: //^C - break
				usart_struct.USART_RX_BUF[0] = '\0';//discard input
				usart_struct.USART_RX_Cnt = 0;
				break;
			case 0x15: //^U - erase line
			{
				while(usart_struct.USART_RX_Cnt)
				{
					usart_SendString("\b \b");
					usart_struct.USART_RX_Cnt -- ;
				}
				break;
			}
			case 0x08: //^H - backspace
			case 0x7F: //DEL- backspace
			{
				usart_SendString("\b \b");
				if(usart_struct.USART_RX_Cnt)
					usart_struct.USART_RX_Cnt --;
				break;
			}
			default:
			{
				if(data >= 32 && data <= 126)//可显示字符的ASCII码
				{
					if(usart_struct.USART_RX_Cnt < USART_RX_BUF_SIZE - 1)
					{
						usart_struct.USART_RX_BUF[usart_struct.USART_RX_Cnt] = data;
						usart_struct.USART_RX_Cnt ++;
						USART_SendData(USART2,data);
						while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
					}
					else
					{
						USART_SendData(USART2,'\a');//buffer full
						while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
					}
				}
	    }
    }
  }
}
/**
  * @brief  usart put string 
  * @param  None
  * @retval None
  */
void usart_SendString(char *str)
{
	while(*str)
	{
		USART_SendData(USART2,*str++);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	}
}

#ifndef NO_TRACE
void TRACE(char *fmt, ...)
{
	char szBuffer[256];
	int nLen, i;
	va_list args;

	va_start(args, fmt);
	nLen = vsnprintf(szBuffer,256, fmt, args);
	va_end(args);

	for (i = 0; i < nLen; i ++) 
	{
		USART_SendData(USART2, szBuffer[i]);
		while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	}
}
#endif

void Console_Print(const char *fmt, ...)
{
	char szBuffer[256];
	va_list args;

	va_start(args, fmt);
	vsnprintf(szBuffer,256, fmt, args);
	va_end(args);

	usart_SendString(szBuffer);
}
	
/**
  * @brief  usart send jpeg data
  * @param  None
  * @retval None
  */
extern u32 Image_Buffer1[IMAGE_BUFFER_SIZE];
extern u8 Dma_FreeBuf_No;
void usart_sendJPEGdata(void)
{
	u32 i;
	if(DMA_GetCurrentMemoryTarget(DMA2_Stream1) == 1)
	{
		for(i=0;i<IMAGE_BUFFER_SIZE;i++)
		{
			USART_SendData(USART2,Image_Buffer1[i]);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			USART_SendData(USART2,Image_Buffer1[i]>>8);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			USART_SendData(USART2,Image_Buffer1[i]>>16);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			USART_SendData(USART2,Image_Buffer1[i]>>24);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
		}
	}
	else
	{
		for(i=0;i<IMAGE_BUFFER_SIZE;i++)
		{
			USART_SendData(USART2,Image_Buffer2[i]);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			USART_SendData(USART2,Image_Buffer2[i]>>8);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			USART_SendData(USART2,Image_Buffer2[i]>>16);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			USART_SendData(USART2,Image_Buffer2[i]>>24);
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);			
		}
	}
}

