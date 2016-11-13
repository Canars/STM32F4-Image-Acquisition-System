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
#ifndef __WLAN_MISC_H__
#define __WLAN_MISC_H__
//
// Macros definition
//
enum KeySize {
	KeySizeValue_40_64bit_ASCII     =   5,
	KeySizeValue_40_64bit_HEX       =   10,
	KeySizeValue_104_128bit_ASCII   =   13,
	KeySizeValue_104_128bit_HEX     =   26
};

#define IP2DWORD(a,b,c,d)				((DWORD)(BYTE)(d)|(DWORD)(BYTE)(c)<<8|(DWORD)(BYTE)(b)<<16|(DWORD)(BYTE)(a)<<24)
#define DWORD2IP(val,array)			\
	do {							\
		array[0] = (BYTE)((val >> 24) & 0x000000FF); \
		array[1] = (BYTE)((val >> 16) & 0x000000FF); \
		array[2] = (BYTE)((val >> 8) & 0x000000FF); \
		array[3] = (BYTE)((val >> 0) & 0x000000FF); \
	} while(0)

//
// Exported functions declare
//
UCHAR WlanMisc_ASCII2WEPKey(CHAR *pszKeyASCII, UCHAR *pucKeyMaterial);
BOOL WlanMisc_String2Ip(char *pszString, ULONG *pulIp);
BOOL WlanMisc_String2Mac(char *pszString, PBYTE pbMac);

#endif // __WLAN_MISC_H__
