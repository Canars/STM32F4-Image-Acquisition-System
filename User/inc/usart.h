#ifndef _USART_H
#define _USART_H
/*******************************INCLUDES******************************/
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>
#include "WifiCfg.h"

#define USART_RX_BUF_SIZE	128
#define USART_TX_BUF_SIZE 128

#define USART_STA_RECEIVED  1<<0
#define USART_STA_SENT      1<<1

typedef struct _USART_STRUCT
{
	u8 USART_RX_BUF[USART_RX_BUF_SIZE];
	u8 USART_TX_BUF[USART_TX_BUF_SIZE];
	u8 USART_RX_Cnt;
	u8 USART_Sta;
}USART_STRUCT;

extern USART_STRUCT usart_struct;

void usart_init(void);
void usart_SendString(char *str);
void usart_sendJPEGdata(void);
#ifndef NO_TRACE
void TRACE(char *fmt, ...);
#else //NO_TRACE
static void TRACE(const char *fmt, ...){}
#endif
void Console_Print(const char *fmt, ...);
#endif
