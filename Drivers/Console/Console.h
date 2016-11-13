/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef __CONSOLE_H__
#define __CONSOLE_H__
//
// Macros define
//
#define CONSOLE_RX_BUFFER_SIZE			128
#define CONSOLE_TX_BUFFER_SIZE			128

#define CONSOLE_STATE_RECEIVED			(1 << 0)
#define CONSOLE_STATE_SENT				(1 << 1)

//
// Structs define
//
typedef struct _Console {
	UCHAR ucConsoleRxBuffer[CONSOLE_RX_BUFFER_SIZE];
	UCHAR ucConsoleTxBuffer[CONSOLE_TX_BUFFER_SIZE];
	UCHAR ucRxCnt;
	UCHAR ucTxCnt;
	UCHAR ucState;
} Console, *PCONSOLE;

//
// Exported functions declare
//
BOOL Console_Init();
void Console_Print(const char *fmt, ...);
BOOL Console_IsReceived();
BOOL Console_IsSent();
BOOL Console_ResetRx();
BOOL Console_ResetTx();

//
// Exported variables declare
//
extern Console g_Console;

#endif // __CONSOLE_H__
