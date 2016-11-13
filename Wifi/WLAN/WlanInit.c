/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#include "WlanInit.h"

VOID InitAdapterObject(
    PWLAN_ADAPTER Adapter
)
{
	// Reset all flags
	Adapter->m_dwFlags = 0;
	Adapter->nCurMacControl = MAC_CTRL_DEFAULT;

	return;
}

BOOL Wlan_Init(PWLAN_ADAPTER Adapter)
{
	// Zero out the adapter object space
	ZeroMemory(Adapter, sizeof(WLAN_ADAPTER));
	InitAdapterObject(Adapter);

	// interface initialize
	if (!If_Init(Adapter)) {
		TRACE("Interface init failed!!\r\n");
		return FALSE;
	}
	if (!If_StartDevice(Adapter)) {
		TRACE("Interface start device failed!!\r\n");
		return FALSE;
	}
	CmdSubscribeEvent(Adapter);

	return TRUE;
}
