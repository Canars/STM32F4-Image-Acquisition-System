/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
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
