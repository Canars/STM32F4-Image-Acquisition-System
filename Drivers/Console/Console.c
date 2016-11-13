/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "Project.h"

Console g_Console;
void Console_IRQHandler(UCHAR ucIntType, UCHAR ucCharRx);
const Stm32Uart uart = {USART1, GPIOA, GPIO_Pin_10, GPIO_Pin_9, 115200, UART_MODE_INT, Console_IRQHandler};
#define pUart	((PSTM32UART)&uart)

BOOL Console_Init()
{
	ZeroMemory(&g_Console, sizeof(Console));
	Uart_Init(pUart);
		
	return TRUE;
}

void Console_IRQHandler(UCHAR ucIntType, UCHAR ucCharRx)
{
	if(ucIntType == UART_INT_TYPE_RX) {
		switch (ucCharRx) {
			case '\r':	 // Enter		  
			case '\n':
				g_Console.ucConsoleRxBuffer[g_Console.ucRxCnt]  = '\0';
				Uart_SendString(pUart, "\r\n");
				g_Console.ucState |= CONSOLE_STATE_RECEIVED;
				break;
			case '\0': // nul			  
				break;
			case 0x03: // ^C - break		  
				g_Console.ucConsoleRxBuffer[0] = '\0';	// discard input
				g_Console.ucRxCnt = 0;
				break;
			case 0x15: // ^U - erase line
			{
				while (g_Console.ucRxCnt) {
					Uart_SendString (pUart, "\b \b");
					g_Console.ucRxCnt --;
				}
				break;
			}
			case 0x08: // ^H  - backspace	  
			case 0x7F: // DEL - backspace	  
			{
				Uart_SendString (pUart, "\b \b");
				if (g_Console.ucRxCnt)
					g_Console.ucRxCnt --;

				break;
			}
			default:
				if (ucCharRx >= 32 && ucCharRx <= 126)
				{
					if (g_Console.ucRxCnt < CONSOLE_RX_BUFFER_SIZE - 1) {
						g_Console.ucConsoleRxBuffer[g_Console.ucRxCnt]  = ucCharRx;
						g_Console.ucRxCnt ++;
						Uart_SendByte(pUart, ucCharRx);
					}
					else
						Uart_SendByte(pUart, '\a'); // Buffer full
				}
				break;
		}
	}
}

void Console_Print(const char *fmt, ...)
{
	char szBuffer[256];
	va_list args;

	va_start(args, fmt);
	vsprintf(szBuffer, fmt, args);
	va_end(args);

	Uart_SendString(pUart, szBuffer);
}

BOOL Console_IsReceived()
{
	return (g_Console.ucState & CONSOLE_STATE_RECEIVED ? TRUE : FALSE);
}

BOOL Console_IsSent()
{
	return (g_Console.ucState & CONSOLE_STATE_SENT ? TRUE : FALSE);
}

BOOL Console_ResetRx()
{
	g_Console.ucState &= ~CONSOLE_STATE_RECEIVED;
	g_Console.ucRxCnt = 0;
	
	return TRUE;
}

BOOL Console_ResetTx()
{
	g_Console.ucState &= ~CONSOLE_STATE_SENT;
	g_Console.ucTxCnt = 0;
		
	return TRUE;
}

BOOL Console_ProcCmd()
{
		
	return TRUE;
}

