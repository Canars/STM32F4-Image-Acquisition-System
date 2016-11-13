/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef __WIFIAPI_EXPORT_H__
#define __WIFIAPI_EXPORT_H__
//
// Macros definition
//
typedef enum _WIFISETCMD {
	// Wlan layer
	CMD_SET_SSID,
	CMD_SET_NETWORK_TYPE,
	CMD_SET_AUTH_MODE,
	CMD_SET_ENCRY_MODE,
	CMD_SET_KEY_ASCII,
	CMD_SET_KEY_INDEX,
	CMD_SET_KEY_MATERIAL,
	CMD_SET_EAP_TYPE,
	CMD_SET_MAC_ADDR,
	// Network layer
	CMD_SET_IP_ADDR,
	CMD_SET_SUB_NET,
	CMD_SET_GATEWAY_IPADDR,
} WIFISETCMD, *PWIFISETCMD;

typedef enum _WIFIGETCMD {
	// Wlan layer
	CMD_GET_SSID,
	CMD_GET_NETWORK_TYPE,
	CMD_GET_AUTH_MODE,
	CMD_GET_ENCRY_MODE,
	CMD_GET_KEY_ASCII,
	CMD_GET_KEY_INDEX,
	CMD_GET_KEY_MATERIAL,
	CMD_GET_EAP_TYPE,
	CMD_GET_MAC_ADDR,
	CMD_GET_LIST_SCAN,
	CMD_GET_RSSI,
	CMD_GET_STATUS,
	// Network layer
	CMD_GET_IP_ADDR,
	CMD_GET_SUB_NET,
	CMD_GET_GATEWAY_IPADDR,
} WIFIGETCMD, *PWIFIGETCMD;

typedef enum _WIFICTRLCMD {
	// Wlan layer
	CMD_CTRL_SCAN,
	CMD_CTRL_CONN,
	CMD_CTRL_DISCONN,
	CMD_CTRL_TURN_ON,
	CMD_CTRL_TURN_OFF,
} WIFICTRLCMD, *PWIFICTRLCMD;

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

//
// Structs definition
//

//
// Exported functions declare
//
int WiFiApi_CheckCurrentProfile ();
int WiFiApi_CardSetEncryMode (ENCRYMODE mode);
int WiFiApi_AdapterSetKey (char *pszKey);
int WiFiApi_DoConnect ();
int WiFiApi_ProcessAssoc();

#endif // __WIFIAPI_EXPORT_H__

