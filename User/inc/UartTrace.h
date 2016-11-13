/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef __UART_TRACE_H__
#define __UART_TRACE_H__
//
// Macros definitions
//
#define TR_CLR_FORE_BLACK		30
#define TR_CLR_FORE_RED			31
#define TR_CLR_FORE_GREEN		32
#define TR_CLR_FORE_YELLOW		33
#define TR_CLR_FORE_BLUE		34
#define TR_CLR_FORE_PURPLE		35
#define TR_CLR_FORE_CYAN		36
#define TR_CLR_FORE_WHITE		37

#define TR_CLR_BACK_BLACK		40
#define TR_CLR_BACK_RED			41
#define TR_CLR_BACK_GREEN		42
#define TR_CLR_BACK_YELLOW		43
#define TR_CLR_BACK_BLUE		44
#define TR_CLR_BACK_PURPLE		45
#define TR_CLR_BACK_CYAN		46
#define TR_CLR_BACK_WHITE		47

//
// Exported functions declare
//
#ifndef NO_TRACE
BOOL TraceInit();
void TRACE(const char *fmt, ...);
void TRACEDATA(const char* pszPrompt,PVOID pData,int nSize);
void CTRACE(UCHAR ucFore, UCHAR ucBack, const char *fmt, ...);
#else // NO_TRACE
#define TraceInit()
static void TRACE(const char *fmt, ...){}
static void TRACEDATA(const char* pszPrompt,PVOID pData,int nSize){}
static void CTRACE(UCHAR ucFore, UCHAR ucBack, const char *fmt, ...){}
#endif // NO_TRACE

#ifndef NO_DEBUG
#undef ASSERT
#define ASSERT(x)						\
	do {								\
		if (!(x)) {						\
			TRACE("ASSERT error!\r\n");	\
			while(1);					\
		}								\
	} while(0)
#else // NO_DEBUG
#define ASSERT(x)
#endif

#endif
