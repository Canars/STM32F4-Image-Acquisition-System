/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef __UART_H__
#define __UART_H__
//
// Macros define
//
#define UART_MODE_POLL						0	// 普通模式
#define UART_MODE_INT						1	// 中断模式

#define UART_INT_TYPE_RX					0
#define UART_INT_TYPE_TX					1
//
// Structs define
//
typedef void (*UartIrqHandler) (UCHAR ucType, UCHAR ucCharRx);

typedef struct _STM32UART {
	USART_TypeDef* UARTx;
	GPIO_TypeDef* pGPIOPort;
	USHORT	usRxPin;
	USHORT	usTxPin;
	DWORD dwBaud;
	UCHAR ucMode;
	UartIrqHandler pUartIrqHandler;
} Stm32Uart, *PSTM32UART;

//
// Exported functions declare
//
BOOL Uart_Init(PSTM32UART pUart);
void Uart_SendByte(PSTM32UART pUart, USHORT usData);
void Uart_SendBuffer(PSTM32UART pUart, PUCHAR pucBuffer, int nLen);
void Uart_SendString(PSTM32UART pUart, char* pszBuffer);

#endif // __UART_H__
