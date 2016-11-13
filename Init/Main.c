/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

//
// Created by csword 2011/01/13
// All rights reserved
//
#include "Project.h"

#include "uip.h"
#include "uIP_App.h"
#include "tapdev.h"
#include "clock-arch.h"
#include "lingtone_app.h"

UCHAR ucNetworkPktBuffer[KBytes(2)];
volatile unsigned int uIP_RunTime;//__IO == volatile

void main(void)
{
	BOOL bStatus;

	// Bsp Init
	Set_System();
	TraceInit();

#ifdef BUILD_FOR_WRITEFIRMWARE
	If_WriteFirmware ();
	while (1);
#endif
	
	SysClockInit();
	Board_Init ();

	// Drivers init
	Flash_Init();
	Buzzer_Init ();
	Relay_Init ();
	LED_Init ();
	Console_Init ();

	Console_Print("WiFi Hello world!!\r\n");
	//
	// Wifi start!
	//
	bStatus = Wlan_Init(g_pWlanAdapter);
	if (!bStatus) {
		TRACE("Wlan init failed!!\r\n");
		return;
	}

	// uIP Init
	uIP_Net_Init();
	
	if (1) { // Create default profile
		WiFiCmd_RunCommand ("set ssid WiFiTest_AdHoc");
		WiFiCmd_RunCommand ("set networktype adhoc");
		WiFiCmd_RunCommand ("set authmode open");
		WiFiCmd_RunCommand ("set encrymode wep");
		WiFiCmd_RunCommand ("set keyascii 1234567890");
	}
	WiFiCmd_RunCommand ("ctrl connect");
	
	while (1) {
		if (WIFI_GET_FLAG(g_pWlanAdapter, FLAG_PKTRCVED)) {
			WIFI_CLR_FLAG(g_pWlanAdapter, FLAG_PKTRCVED);
			UipPro();
		}
		if (g_Console.ucState & CONSOLE_STATE_RECEIVED) {
			WiFiCmd_RunCommand ((char*)g_Console.ucConsoleRxBuffer);
			Console_ResetRx();
		}
	}
}
