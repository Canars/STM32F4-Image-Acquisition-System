/******************************
΢Ƕ���ӹ����� ��Ȩ����
STM32 WIFI ������
������΢Ƕ���ӡ���ͨҼ��WIFI�����塱
�������¼ http://yuikin.taobao.com
Դ����ʹ��Э�飺��������ṩ���ͻ���ѧϰ�����߲ο�WIFIԭ��֮�ã��㲻�����㷢���Ĳ�Ʒ����
������Դ����������ļ����߲���Ƭ�Σ������ܳ��ۻ���ʹ�ñ��������ṩ��Դ����������ͬ���Ͳ�Ʒ��
���磺�����塢ѧϰ�壬Ӫ���Խ�ѧ�����ȵȣ�������Ϊ��Ȩ���������ұ���׷����ط������ε�Ȩ����
*******************************/

#include "Includes.h"
#ifndef __WIFI_HW_H__
#define __WIFI_HW_H__
//
// RST: Pin35-PC1, CS: Pin36-PA15, INT: Pin33-PC4, PDN: Pin34-PC0
// SPI: SPI1
#define WIFI_CTRL2_PORT			GPIOC
#define WIFI_CTRL2_PDN_PIN		GPIO_Pin_0
#define WIFI_HW_SET_PDN()		WIFI_CTRL2_PORT->BSRRL=WIFI_CTRL2_PDN_PIN
#define WIFI_HW_CLR_PDN()		WIFI_CTRL2_PORT->BSRRH=WIFI_CTRL2_PDN_PIN

#define WIFI_CTRL3_PORT			GPIOC
#define WIFI_CTRL3_RST_PIN		GPIO_Pin_1
#define WIFI_HW_SET_RST()		WIFI_CTRL3_PORT->BSRRL=WIFI_CTRL3_RST_PIN
#define WIFI_HW_CLR_RST()		WIFI_CTRL3_PORT->BSRRH=WIFI_CTRL3_RST_PIN

#define WIFI_CTRL3_INT_PIN		GPIO_Pin_4

#define WIFI_POWER_UP			WIFI_HW_SET_PDN
#define WIFI_POWER_DOWN			WIFI_HW_CLR_PDN

#define WIFI_CHIPSELECT_ENABLE	WIFI_HW_CLR_CS
#define WIFI_CHIPSELECT_DISABLE WIFI_HW_SET_CS

#define WIFI_GSPICLK_RESET		WIFI_HW_CLR_RST
#define WIFI_GSPICLK_RELEASE_RESETING WIFI_HW_SET_RST

//
// Exported functions declare
//
BOOL Hw_Init(void);
BOOL Hw_Deinit (void);
BOOL Hw_IntrInit (void);
BOOL Hw_DmaInit (void);
BOOL Hw_PowerOn(void);
BOOL Hw_PowerOff(void);
int Hw_WriteRegister(int nRegNo, PVOID pBuf, int nSize);
int Hw_ReadRegister(int nRegNo, PVOID pBuf, int nSize);
BOOL Hw_OpenInterrupts(void);
BOOL Hw_CloseInterrupts(void);
BOOL Hw_Reset(void);

#endif // __WIFI_HW_H__
