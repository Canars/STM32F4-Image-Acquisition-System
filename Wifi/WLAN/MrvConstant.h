/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef _MRVCONSTANT_H_
#define _MRVCONSTANT_H_

#define MRVDRV_ETH_ADDR_LEN                         6

#define MRVDRV_MAX_SSID_LENGTH              32

#define MRVDRV_MAX_BSSID_LIST                 0x40  //34.p1  //0x20   

#define MRVDRV_MAX_MULTICAST_LIST_SIZE   0x00000020

// reserve 400 bytes for each AP's variable IE in the scan list
#define MRVDRV_SCAN_LIST_VAR_IE_SPACE       400

// set aside 500 bytes for the association information buffer
#define MRVDRV_ASSOCIATE_INFO_BUFFER_SIZE   500

#define MRVDRV_ASSOCIATION_TIME_OUT      195

#define MRVDRV_MIC_ERROR_PERIOD          60000

#define SET_AUTO_PREAMBLE                           0x05
#define SET_SHORT_PREAMBLE                          0x03
#define SET_LONG_PREAMBLE                           0x01

#define MAX_POWER_ADAPT_GROUP       5

#define COUNTRY_CODE_LEN    3   //3 

#define WMM_PARA_IE_LENGTH          0x0018

#define MRVDRV_WCB_STATUS_USED                   0x00000001 // for WCBRefNode to use

// code_clean_up
// PJG: get these to match FW and then fix all usage.
///crlo: We use this variable to allocate the buffer. For SDIO, we need more buffers to save the SDIO block
///     Because we don't know how much buffers are needed for SPI, just define a big value for safety
#define MRVDRV_MAXIMUM_ETH_PACKET_SIZE             1600  // PJG:
#define MRVDRV_ETH_HEADER_SIZE                      14

///crlo: defined MTU to report to the TCP layer
#define MRVDRV_MTU                              1500
#define MRVDRV_MTU_TOTAL                        (MRVDRV_MTU+MRVDRV_ETH_HEADER_SIZE)

#define MRVDRV_LINK_SPEED_0mbps          0
#define MRVDRV_LINK_SPEED_1mbps          10000 // in unit of 100bps
#define MRVDRV_LINK_SPEED_2mbps          20000
#define MRVDRV_LINK_SPEED_5dot5mbps      55000
#define MRVDRV_LINK_SPEED_6mbps          60000
#define MRVDRV_LINK_SPEED_9mbps          90000
#define MRVDRV_LINK_SPEED_10mbps         100000
#define MRVDRV_LINK_SPEED_11mbps         110000
#define MRVDRV_LINK_SPEED_12mbps         120000
#define MRVDRV_LINK_SPEED_18mbps         180000
#define MRVDRV_LINK_SPEED_22mbps         220000
#define MRVDRV_LINK_SPEED_24mbps         240000
#define MRVDRV_LINK_SPEED_33mbps         330000
#define MRVDRV_LINK_SPEED_36mbps         360000
#define MRVDRV_LINK_SPEED_48mbps         480000
#define MRVDRV_LINK_SPEED_54mbps         540000
#define MRVDRV_LINK_SPEED_72mbps         720000
#define MRVDRV_LINK_SPEED_100mbps        1000000

#define WAKEUP_EVENT_BROADCAST                      0x03UL
#define WAKEUP_EVENT_UNICAST                        0x02UL

#define MRVDRV_MAX_SUBBAND_802_11D      83

#define MRVDRV_802_11_BAND_B        0x00
#define MRVDRV_802_11_BAND_BG       0x01
#define MRVDRV_802_11_BAND_A        0x02

#define B_SUPPORTED_RATES       8
#define BASIC_SUPPORTED_RATES   8
#define G_SUPPORTED_RATES       14
#define NDIS_SUPPORTED_RATES    G_SUPPORTED_RATES

//          INT code register event definition
#define MACREG_INT_CODE_TX_PPA_FREE         0x00000000 // Added 05/28/02
#define MACREG_INT_CODE_TX_DMA_DONE         0x00000001
#define MACREG_INT_CODE_LINK_LOSE_NO_SCAN   0x00000003
#define MACREG_INT_CODE_LINK_SENSED         0x00000004
#define MACREG_INT_CODE_CMD_FINISHED        0x00000005
#define MACREG_INT_CODE_MIB_CHANGED         0x00000006 // Added 01/22/02
#define MACREG_INT_CODE_INIT_DONE           0x00000007 // Added 01/30/02
#define MACREG_INT_CODE_DEAUTHENTICATED     0x00000008 // Added 11/08/02
#define MACREG_INT_CODE_DISASSOCIATED       0x00000009 // Added 11/08/02
#define MACREG_INT_CODE_PS_AWAKE            0x0000000a
#define MACREG_INT_CODE_PS_SLEEP            0x0000000b
#define MACREG_INT_CODE_TX_DONE             0x0000000c
#define MACREG_INT_CODE_WPA_MIC_ERR_UNICAST     0x0000000e
#define MACREG_INT_CODE_WPA_MIC_ERR_MULTICAST   0x0000000d
#define MACREG_INT_CODE_HOST_AWAKE              0x0000000f
#define MACREG_INT_CODE_DS_AWAKE                0x00000010 //Deep Sleep Awake
#define MACREG_INT_CODE_ADHOC_BCN_LOST          0x00000011
#define MACREG_INT_CODE_HOST_SLEEP_AWAKE        0x00000012
#define MACREG_INT_CODE_BG_SCAN_REPORT      0x00000018
#define MACREG_INT_CODE_IBSS_COALESCED      0x0000001e
#define MACREG_INT_CODE_RSSI_LOW                    0x00000019
#define MACREG_INT_CODE_SNR_LOW                     0x0000001a
#define MACREG_INT_CODE_MAX_FAIL                    0x0000001b
#define MACREG_INT_CODE_RSSI_HIGH                   0x0000001c
#define MACREG_INT_CODE_SNR_HIGH                    0x0000001d
#define MACREG_INT_CODE_WMM_STATUS_CHANGE   0x00000017 // tt wled

#define TLV_TYPE_SSID                               0x0000
#define TLV_TYPE_RATES                              0x0001
#define TLV_TYPE_PHY_FH                             0x0002
#define TLV_TYPE_PHY_DS                             0x0003
#define TLV_TYPE_CF                                 0x0004
#define TLV_TYPE_IBSS                               0x0006
#define TLV_TYPE_DOMAIN                             0x0007
#define TLV_TYPE_POWER_CAPABILITY                   0x0021

#define PROPRIETARY_TLV_BASE_ID     0x0100
#define TLV_TYPE_KEY_MATERIAL       (PROPRIETARY_TLV_BASE_ID + 0)
#define TLV_TYPE_CHANLIST           (PROPRIETARY_TLV_BASE_ID + 1)
#define TLV_TYPE_NUMPROBES          (PROPRIETARY_TLV_BASE_ID + 2)
#define TLV_TYPE_RSSI               (PROPRIETARY_TLV_BASE_ID + 4)
#define TLV_TYPE_SNR                (PROPRIETARY_TLV_BASE_ID + 5)
#define TLV_TYPE_FAILCOUNT          (PROPRIETARY_TLV_BASE_ID + 6)
#define TLV_TYPE_BCNMISS            (PROPRIETARY_TLV_BASE_ID + 7)
#define TLV_TYPE_LED_GPIO           (PROPRIETARY_TLV_BASE_ID + 8)
#define TLV_TYPE_LEDBEHAVIOR        (PROPRIETARY_TLV_BASE_ID + 9)
#define TLV_TYPE_PASSTHROUGH        (PROPRIETARY_TLV_BASE_ID + 10)
#define TLV_TYPE_REASSOCAP          (PROPRIETARY_TLV_BASE_ID + 11)
#define TLV_TYPE_POWER_TBL_2_4GHZ   (PROPRIETARY_TLV_BASE_ID + 12)
#define TLV_TYPE_POWER_TBL_5GHZ     (PROPRIETARY_TLV_BASE_ID + 13)
#define TLV_TYPE_BCASTPROBE         (PROPRIETARY_TLV_BASE_ID + 14)
#define TLV_TYPE_NUMSSID_PROBE      (PROPRIETARY_TLV_BASE_ID + 15)
#define TLV_TYPE_CRYPTO_DATA        (PROPRIETARY_TLV_BASE_ID + 17)
#define TLV_TYPE_RSSI_HIGH          (PROPRIETARY_TLV_BASE_ID + 22)
#define TLV_TYPE_SNR_HIGH           (PROPRIETARY_TLV_BASE_ID + 23)
#define TLV_TYPE_TSFTIMESTAMP       (PROPRIETARY_TLV_BASE_ID + 19)
#define TLV_TYPE_AUTH_TYPE          (PROPRIETARY_TLV_BASE_ID + 31)
#define TLV_TYPE_PREBCNMISS         (PROPRIETARY_TLV_BASE_ID + 73)

#define TLV_PAYLOAD_SIZE    2
#define PRE_BEACON_LOST     0x0800
#define SNR_HIGH            0x0020
#define RSSI_HIGH           0x0010
#define LINK_LOSS           0x0008
#define MAX_FAIL            0x0004
#define SNR_LOW             0x0002
#define RSSI_LOW            0x0001
#define LINK_LOST_BEACONCNT 60 // 120

#define  RSN_IE_AES         1
#define  RSN_IE_TKIP        2

#define LEN_OF_PMKID        16
#define MAX_PMKID_CACHE 8

//      11/08/02 - Add WEP list data structures
#define MRVL_KEY_BUFFER_SIZE_IN_BYTE  16
// max key length is 32 bytes acording to current WPA document
#define MRVL_MAX_WPA_KEY_LENGTH         32
// support 4 keys per key set
#define MRVL_NUM_WPA_KEY_PER_SET        4
// support 5 key sets
#define MRVL_NUM_WPA_KEYSET_SUPPORTED   5

#define WEP_KEY_40_BIT_LEN                          5
#define WEP_KEY_104_BIT_LEN                         13
#define WPA_AES_KEY_LEN         16
#define WPA_TKIP_KEY_LEN        32
#define WPA_CCKM_KEY_LEN        13

typedef enum {
	KEY_TYPE_ID_WEP = 0,
	KEY_TYPE_ID_TKIP,
	KEY_TYPE_ID_AES
} KEY_TYPE_ID;

typedef enum {
	KEY_INFO_WEP_DEFAULT_KEY = 0x01
} KEY_INFO_WEP;

typedef enum {
	KEY_INFO_TKIP_MCAST = 0x01,
	KEY_INFO_TKIP_UNICAST = 0x02,
	KEY_INFO_TKIP_ENABLED = 0x04
} KEY_INFO_TKIP;

typedef enum {
	KEY_INFO_AES_MCAST = 0x01,
	KEY_INFO_AES_UNICAST = 0x02,
	KEY_INFO_AES_ENABLED = 0x04
} KEY_INFO_AES;

#define fNDIS_GUID_ALLOW_READ       0x00000020
#define fNDIS_GUID_ALLOW_WRITE      0x00000040

typedef enum _FSW_CCX_CCKM_RESULT_CODE {
	FswCcx_CckmSuccess = 0,
	FswCcx_CckmFailure,
	FswCcx_CckmNotInUse
} FSW_CCX_CCKM_RESULT_CODE;

typedef enum {
	OID_FSW_CCX_CONFIGURATION = 0xFFCCA000,
	OID_FSW_CCX_NETWORK_EAP,
	OID_FSW_CCX_ROGUE_AP_DETECTED,
	OID_FSW_CCX_REPORT_ROGUE_APS,
	OID_FSW_CCX_AUTH_SUCCESS,
	OID_FSW_CCX_CCKM_START,     /* not an OID - Status message */
	OID_FSW_CCX_CCKM_REQUEST,   /* new one */
	OID_FSW_CCX_CCKM_RESULT
} FUNK_CCX_OID;

typedef enum {
	NOTIFY_IAPP,            //Passing the IAPP  packet
	NOTIFY_ROAMING,         //Roaming criteria matched
	NOTIFY_ASSOCIATED,      //Pass the association paramters
	NOTIFY_DISCONNECT,      //Pass the disconnected parameter
	NOTIFY_HS_ACTIVATED,    //Notify Application the host sleep mode is activated in both driver & FW
	NOTIFY_HS_DEACTIVATED,  //Notify Application the host sleep mode is deactivated in both driver & FW
	NOTIFY_SCAN_RDY,         //Notify Application the BG SCAN completed.
	NOTIFY_FW_RELOADED,    //Notify Fw re-reload completed    012207
	NOTIFY_CCX4_S56_TSM      //Notify the ccx4 s56 traffic stream metric IE
} NOTIFY_UI_TYPE;

#define OID_MRVL_OEM_GET_ULONG                  0xff010201
#define OID_MRVL_OEM_SET_ULONG                  0xff010202
#define OID_MRVL_OEM_GET_STRING                 0xff010203
#define OID_MRVL_OEM_COMMAND                    0xff010204

#define OID_MRVL_MAC_ADDRESS                    0xFF010210

#endif //_MRVCONSTANT_H_
