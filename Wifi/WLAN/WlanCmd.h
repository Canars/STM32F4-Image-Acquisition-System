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
#ifndef __WLAN_CMD_H__
#define __WLAN_CMD_H__
//
// Macros definition
//
enum _WLANCMD {
	// Cmd ID
	CMD_ID_SSID_NONE            =       0x00,
	CMD_ID_SSID_SCAN,
	CMD_ID_BSSID_SCAN,
	CMD_ID_LIST_SCAN,
	// Cmd status
	CMD_ERROR_SUCCESS           =       0x00,
	CMD_ERROR_HWERROR,
	CMD_ERROR_CMDPROCING,
	CMD_ERROR_NOMEMORY,
	CMD_ERROR_TIMEOUT,
	CMD_ERROR_UNKNOWN,
	// Cmd timeout value
	CMD_TIMEOUT_MIN             =       50,     // 50 ms
	CMD_TIMEOUT_NORMAL          =       100,    // 100 ms
	CMD_TIMEOUT_MAX             =       30000,  // 30 s
	// Paramter for scan
	CMD_SCAN_CHANNEL_MIN        =       1,
	CMD_SCAN_CHANNEL_MAX        =       14,
};

enum _tagCmd
{
	cmdEventWaitTimeout		= 8000,
	cmdHaltCount			= 3,
	cmdPsNumDtims			= 3,
	cmdAdhocChannel			= 6,
	cmdAdhocBacconPeriod	= 0, //ms
	cmdAdhocAtimWindow		= 0, //ms
	cmdAdhocAwakePeriod		= 0
};
	
typedef int CMD_STATUS;

#pragma pack(1)
typedef struct _BaseHostCmd {
	WORD Command;
	WORD Size;
	WORD SeqNum;
	WORD Result;
} BaseHostCmd, *PBaseHostCmd;

typedef struct _SrBssDesc {
	WORD nSize;
	BYTE aApPhyAddr[6];
	BYTE nRssi;
	BYTE aTimeStamp[8];
	WORD nTsInterval;
	WORD nCapability;
} SrBssDesc, *PSrBssDesc;

typedef UCHAR   CIPHEROUI[4];
#pragma pack()

//
// Private functions declare
//
void CmdOnCmdUpLdRdy(PWLAN_ADAPTER Adapter);

//
// Exported functions declare
//
CMD_STATUS CmdSsidScan(PWLAN_ADAPTER Adapter, char* pszSsid, PBSSINFO pBssInfo);
CMD_STATUS CmdAssociateExt(PWLAN_ADAPTER Adapter, PBSSINFO pBssInfo);
CMD_STATUS CmdSetWepKey(PWLAN_ADAPTER Adapter, USHORT nCmdAct);
CMD_STATUS CmdDeauthenticate(PWLAN_ADAPTER Adapter, PBSSINFO pBssInfo);
CMD_STATUS CmdMacAddress(PWLAN_ADAPTER Adapter, USHORT nCmdAct, NDIS_802_11_MAC_ADDRESS* pMA);
CMD_STATUS CmdGSpiBusCfg(PWLAN_ADAPTER Adapter, USHORT nCmdAct, PUSHORT pnDataClk, PUSHORT pnRegClk);
CMD_STATUS CmdSubscribeEvent(PWLAN_ADAPTER Adapter);
CMD_STATUS CmdMacControl(PWLAN_ADAPTER Adapter, USHORT nCmdAct);
CMD_STATUS CmdListScan(PWLAN_ADAPTER Adapter, char* pszSsid);
CMD_STATUS CmdBssidScan(PWLAN_ADAPTER Adapter, char* pszSsid);
CMD_STATUS CmdAdHocStart(PWLAN_ADAPTER Adapter, PBSSINFO pBssInfo);
CMD_STATUS CmdAdHocStop(PWLAN_ADAPTER pAdapter);
CMD_STATUS CmdSetTxPowerLevel(PWLAN_ADAPTER pAdapter, USHORT nPowerLevel);

#endif // __WLAN_CMD_H__
