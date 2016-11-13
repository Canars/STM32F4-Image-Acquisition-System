/******************************
΢Ƕ���ӹ����� ��Ȩ����
STM32 WIFI ������
������΢Ƕ���ӡ���ͨҼ��WIFI�����塱
�������¼ http://yuikin.taobao.com
Դ����ʹ��Э�飺��������ṩ���ͻ���ѧϰ�����߲ο�WIFIԭ��֮�ã��㲻�����㷢���Ĳ�Ʒ����
������Դ����������ļ����߲���Ƭ�Σ������ܳ��ۻ���ʹ�ñ��������ṩ��Դ����������ͬ���Ͳ�Ʒ��
���磺�����塢ѧϰ�壬Ӫ���Խ�ѧ�����ȵȣ�������Ϊ��Ȩ���������ұ���׷����ط������ε�Ȩ����
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
