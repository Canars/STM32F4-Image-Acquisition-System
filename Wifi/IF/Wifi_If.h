/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/
#include "Wifi_If_Gspi.h"
#include "Includes.h"
#ifndef __WIFI_IF_H__
#define __WIFI_IF_H__
//
// Headers include
//
//
// Macros definitions
//
#define WLAN_INTR_ENABLE_BITS   (HIS_TxDnLdRdy | HIS_RxUpLdRdy | HIS_CmdDnLdRdy | HIS_CardEvent | HIS_CmdUpLdRdy)

//-------------------------------------------------------------------------------
// Wlan CallBack function type
//-------------------------------------------------------------------------------
typedef void(*WlanInterruptCallback)(PWLAN_ADAPTER);

//
// Exported functions declare
//
BOOL If_Init(PWLAN_ADAPTER Adapter);
void If_Deinit(PWLAN_ADAPTER Adapter);
BOOL If_StartDevice(PWLAN_ADAPTER Adapter);
int If_ReadRegister(int nRegNo, PVOID pBuf);
int If_WriteRegister(int nRegNo, WORD nData);
int If_ReadRegister2(int nRegNo, PVOID pBuf, int nSize);
int If_WriteRegister2(int nRegNo, PVOID pBuf, int nSize);
void If_HostIntrEnable(void);
void If_HostIntrDisable(void);
BOOL If_IsFirmwareLoaded(void);
BOOL If_WaitforHostIntr(int nTimeOut);
BOOL If_FirmwareImageProg(PBYTE pImage, int nImgSize);
BOOL If_WlanImageProg(PBYTE pImage, int nImgSize);
BOOL If_FirmwareDownload(void);
BOOL If_ExitDeepSleep(void);
BOOL If_ResetDeepSleep(void);
void If_OnIoIntr(PWLAN_ADAPTER pAdapter);
void NOP_Process(PWLAN_ADAPTER pAdapter);

#ifdef BUILD_FOR_WRITEFIRMWARE
void If_WriteFirmware(void);
#endif

//
// Exported variables declare
//
extern UCHAR ucSpiDummyClk;
extern WlanInterruptCallback pWlanInterruptCallback;

#endif // __WIFI_IF_H__
