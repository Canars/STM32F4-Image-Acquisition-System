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
#ifndef __WLAN_ADAPTER_H__
#define __WLAN_ADAPTER_H__

//
// Macros definitions//
//
#define FLAG_SCANINPROGRESS_SHIFT               0
#define FLAG_SCANINPROGRESS                     	(1UL << FLAG_SCANINPROGRESS_SHIFT)
#define FLAG_BGSCANENABLED_SHIFT                1
#define FLAG_BGSCANENABLED                      	(1UL << FLAG_BGSCANENABLED_SHIFT)
#define FLAG_ASSOCIATEINPROGRESS_SHIFT     2
#define FLAG_ASSOCIATEINPROGRESS                	(1UL << FLAG_ASSOCIATEINPROGRESS_SHIFT)
#define FLAG_ASSOCIATIONBLOCKEDBYSCAN_SHIFT     3
#define FLAG_ASSOCIATIONBLOCKEDBYSCAN      (1UL << FLAG_ASSOCIATIONBLOCKEDBYSCAN_SHIFT)
#define FLAG_SCANWHILECONNECT_SHIFT          4
#define FLAG_SCANWHILECONNECT                   	(1UL << FLAG_SCANWHILECONNECT_SHIFT)
#define FLAG_PASSIVESCAN_SHIFT                  	5  // Passive/Active scan
#define FLAG_PASSIVESCAN                        		(1UL << FLAG_PASSIVESCAN_SHIFT)
#define FLAG_PSCONFIRM_SHIFT                    	6
#define FLAG_PSCONFIRM                          		(1UL << FLAG_PSCONFIRM_SHIFT)
#define FLAG_SETACTIVESCANBSSID_SHIFT       7
#define FLAG_SETACTIVESCANBSSID                 	(1UL << FLAG_SETACTIVESCANBSSID_SHIFT)
#define FLAG_SETACTIVESCANSSID_SHIFT         8
#define FLAG_SETACTIVESCANSSID                  	(1UL << FLAG_SETACTIVESCANSSID_SHIFT)
#define FLAG_CMDPROCESSING_SHIFT                9
#define FLAG_CMDPROCESSING                      	(1UL << FLAG_CMDPROCESSING_SHIFT)
#define FLAG_INTRETURN_SHIFT                    	10
#define FLAG_INTRETURN                          		(1UL << FLAG_INTRETURN_SHIFT)
#define FLAG_PKTRCVED_SHIFT                     	11
#define FLAG_PKTRCVED                           		(1UL << FLAG_PKTRCVED_SHIFT)
#define FLAG_EAPOLPKT_RCVED_SHIFT          	12
#define FLAG_EAPOLPKT_RCVED                       	(1UL << FLAG_EAPOLPKT_RCVED_SHIFT)

#define FLAG_MEDIA_CONNECTED_SHIFT          	13
#define FLAG_MEDIA_CONNECTED                       	(1UL << FLAG_MEDIA_CONNECTED_SHIFT)

#define MAC_CTRL_DEFAULT   (HostCmd_ACT_MAC_RX_ON|HostCmd_ACT_MAC_TX_ON|HostCmd_ACT_MAC_MULTICAST_ENABLE|HostCmd_ACT_MAC_WMM_ENABLE|HostCmd_ACT_MAC_BROADCAST_ENABLE)

//
// Structs definitions
//
typedef struct _CUR_CMD_INFO {
	WORD nCommand;
	PVOID pTxBuffer;
	PVOID pRxBuffer;
	WORD nCmdNo;
	WORD nTxSize;
	WORD nRxSize;
} CUR_CMD_INFO;

typedef struct _BSSINFO {
	NDIS_WLAN_BSSID Bssid;
	BYTE Bssid_SupportedRates2[NDIS_802_11_LENGTH_RATES_EX-NDIS_802_11_LENGTH_RATES];
	ULONG IELength;
	NDIS_802_11_FIXED_IEs IEsFixed;
	BYTE IEsVariable[MRVDRV_SCAN_LIST_VAR_IE_SPACE];
	ULONGLONG nNetworkTSF;
	CCX_BSS_Info_t ccx_bss_info;
	BYTE nERPFlags;
	INT nChannel;
	IEEEtypes_CfParamSet_t* pCfParamSet;
	IEEEtypes_IbssParamSet_t* pIbssParamSet;
	IEEEtypes_CountryInfoFullSet_t* pCountryInfo;
	UCHAR ucGroupCipher;
	UCHAR ucPairwiseCipher;
	UCHAR ucKeyMgmt;
	DWORD nScanCounter;
} BSSINFO, *PBSSINFO;

typedef struct _KeyMaterial {
	UCHAR ucKeyLength;
	UCHAR ucMaterial[32];
} KeyMaterial, *PKEYMATERIAL;
typedef enum _NETWORKTYPE {
	NetworkType_Infrastructure = 1,
	NetworkType_AdHoc
} NETWORKTYPE, *PNETWORKTYPE;

typedef enum _AUTHMODE {
	AuthMode_Open = 1,
	AuthMode_Shared,
} AUTHMODE, *PAUTHMODE;

typedef enum _ENCRYMODE {
	EncryMode_Disable = 1,
	EncryMode_WEP,
} ENCRYMODE, *PENCRYMODE;

typedef enum _WIFISTATUS {
	WIFI_STAT_CONN = 1,
	WIFI_STAT_DISCONN,
	WIFI_STAT_OFF
} WIFISTATUS, *PWIFISTATUS;

typedef struct _WiFiProfile
{
	char szSSID[33];
	NETWORKTYPE NetworkType;
	AUTHMODE AuthMode;
	ENCRYMODE EncMode;
	UCHAR BSSID[6];
	char szKey[65];

	UCHAR ucMacAddr[6];
	ULONG ulIP;
	ULONG ulSubNet;
	ULONG ulGatewayIp;
} WiFiProfile,*PWIFIPROFILE;

//-----------------------------------------------------------------------------
// Adapter struct
//-----------------------------------------------------------------------------
typedef struct _WLAN_ADAPTER {
	// Cmd related
	CUR_CMD_INFO m_cmd;
	USHORT nCurMacControl;
	// Cmd buffer
	UCHAR m_ucCmdBuffer[ADAPTER_CMD_BUFFER_LENGTH];
	UCHAR m_ucAssocInfo[MRVDRV_ASSOCIATE_INFO_BUFFER_SIZE];
	// The current connected AP's info
	BSSINFO m_CurApInfo;
	// Wlan profile
	WiFiProfile m_CurProfile;
	KeyMaterial m_KeyMaterial;
	// Flags
	volatile DWORD m_dwFlags;
} WLAN_ADAPTER, *PWLAN_ADAPTER;

//
// Exported functions declare
//
BOOL WlanAdapter_MacAddr(PWLAN_ADAPTER Adapter, UCHAR* pMa, BOOL bSet);
BOOL WlanAdapter_SendPkt(PWLAN_ADAPTER Adapter, PVOID pBuf, UINT nBufLen);
BOOL WlanAdapter_RcvePkt(PWLAN_ADAPTER Adapter, PVOID pBuf, PUINT pnLen);

//
// Exported variables declare
//
extern WLAN_ADAPTER g_WlanAdapter;
extern PWLAN_ADAPTER g_pWlanAdapter;

#endif // __WLAN_ADAPTER_H__
