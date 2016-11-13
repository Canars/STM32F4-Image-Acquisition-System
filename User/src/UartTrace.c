/******************************
΢Ƕ���ӹ����� ��Ȩ����
STM32 WIFI ������
������΢Ƕ���ӡ���ͨҼ��WIFI�����塱
�������¼ http://yuikin.taobao.com
Դ����ʹ��Э�飺��������ṩ���ͻ���ѧϰ�����߲ο�WIFIԭ��֮�ã��㲻�����㷢���Ĳ�Ʒ����
������Դ����������ļ����߲���Ƭ�Σ������ܳ��ۻ���ʹ�ñ��������ṩ��Դ����������ͬ���Ͳ�Ʒ��
���磺�����塢ѧϰ�壬Ӫ���Խ�ѧ�����ȵȣ�������Ϊ��Ȩ���������ұ���׷����ط������ε�Ȩ����
*******************************/

#include "Project.h"

#ifndef NO_TRACE

#ifdef _WIN32
static WCHAR wsTraceFileName[256] =
    {
        0,
    };
CRITICAL_SECTION    TraceCriticalSection;

static void PutWiFiTrace(const char* str, ULONG len)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	DWORD tmplen;
	int i = 0;

	if (wsTraceFileName[0] == 0) {
		while (1) {
			wsprintf (wsTraceFileName, L"\\My Documents\\UWFTrace%d.txt", i++);
			hFile = CreateFile(wsTraceFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
				CloseHandle(hFile);
			else
				break;
		}
		InitializeCriticalSection(&TraceCriticalSection);
	}

	EnterCriticalSection(&TraceCriticalSection);

	hFile = CreateFile(wsTraceFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		SetFilePointer(hFile, 0, NULL, FILE_END);
	}

	WriteFile(hFile, str, len, &tmplen, NULL);
	CloseHandle(hFile);

	LeaveCriticalSection(&TraceCriticalSection);

	return;
}

#else // !_WIN32

extern int VsPrintf(char *buf, const char *fmt, va_list args);
static char szBuffer[256];

static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure USARTx_Tx as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure USARTx_Rx as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	return;
}
#endif

BOOL TraceInit()
{
#ifdef _WIN32
	TRACE("+TraceInit()\r\n");
#else
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	// Enable clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	// UART info
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	// Configure USART1
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);

	// Enable the USART1
	USART_Cmd(USART1, ENABLE);

	GPIO_Configuration();
#endif

	return TRUE;
}

void TRACE(const char *fmt, ...)
{
#ifdef _WIN32
	int nLen;
	va_list args;
	char szBuffer[1024];

	va_start(args, fmt);
	nLen = vsprintf(szBuffer, fmt, args);
	va_end(args);

	PutWiFiTrace(szBuffer, nLen);
#else
	int nLen, i;
	va_list args;

	va_start(args, fmt);
	nLen = VsPrintf(szBuffer, fmt, args);
	va_end(args);

	for (i = 0; i < nLen; i ++) {
		USART_SendData(USART1, szBuffer[i]);
		while ((USART1->SR & USART_FLAG_TXE) == RESET);
	}
#endif
}

void TRACEDATA(const char* pszPrompt,PVOID pData,int nSize)
{
	PBYTE p;
	int i;

	TRACE("%s (%d B):\r\n",pszPrompt,nSize);
	for(i=0,p=(PBYTE)(pData);i<nSize;i+=16,p+=16)
	{
		if(i+16<=nSize)
		{
			TRACE("\t%04d: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\r\n",
				i,p[0],p[1],p[2],p[3], p[4],p[5],p[6],p[7], p[8],p[9],p[10],p[11], p[12],p[13],p[14],p[15]);
		}
		else
		{
			int j;

			TRACE("\t%04d: ",i);
			for(j=0;j<nSize-i;j++)
			{
				TRACE("0x%02X,",p[j]);
//				if(j%4==3)
//					TrFmtText(" ");
			}
			TRACE("\r\n");
		}
	}
}

void CTRACE(UCHAR ucFore, UCHAR ucBack, const char *fmt, ...)
{
#ifdef _WIN32
	int nLen;
	char szBuffer[1024];
	va_list args;

	// Trace color open
	TRACE("\033[1;%d;%dm", ucFore, ucBack);

	va_start(args, fmt);
	nLen = vsprintf(szBuffer, fmt, args);
	va_end(args);

	PutWiFiTrace(szBuffer, nLen);

	// Trace color close
	TRACE("\033[0m");
#else
	int nLen, i;
	va_list args;

	// Trace color open
	TRACE("\033[1;%d;%dm", ucFore, ucBack);

	va_start(args, fmt);
	nLen = VsPrintf(szBuffer, fmt, args);
	va_end(args);

	for (i = 0; i < nLen; i ++) {
		USART_SendData(USART1, szBuffer[i]);
		while ((USART1->SR & USART_FLAG_TXE) == RESET);
	}

	// Trace color close
	TRACE("\033[0m");
#endif
}

#endif // NO_TRACE
