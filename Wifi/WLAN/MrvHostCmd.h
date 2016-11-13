/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef _MRVHOSTCMD_H_
#define _MRVHOSTCMD_H_

#define CMD_ACT_GET     0
#define CMD_ACT_SET     1
#define CMD_DISABLED    0
#define CMD_ENABLED     1

//***************************************************************************
//
//          16 bit host command code - HHH updated on 110201
//
#define HostCmd_CMD_NONE                            0x0000
#define HostCmd_CMD_CODE_DNLD                       0x0001
#define HostCmd_CMD_OP_PARAM_DNLD                   0x0002
#define HostCmd_CMD_GET_HW_SPEC                     0x0003
#define HostCmd_CMD_EEPROM_ACCESS                   0x0004
#define HostCmd_CMD_802_11_RESET                    0x0005
#define HostCmd_CMD_802_11_SCAN                     0x0006
#define HostCmd_CMD_802_11_QUERY_SCAN_RESULT        0x0029
#define HostCmd_CMD_802_11_QUERY_TRAFFIC            0x0009
#define HostCmd_CMD_802_11_QUERY_STATUS             0x000a
#define HostCmd_CMD_802_11_GET_LOG                  0x000b
#define HostCmd_CMD_MAC_CONTROL                     0x0028
#define HostCmd_CMD_MAC_MULTICAST_ADR               0x0010
#define HostCmd_CMD_802_11_AUTHENTICATE             0x0011
#define HostCmd_CMD_802_11_DEAUTHENTICATE           0x0024
#define HostCmd_CMD_802_11_ASSOCIATE                0x0012
#define HostCmd_CMD_802_11_REASSOCIATE              0x0025
#define HostCmd_CMD_802_11_DISASSOCIATE             0x0026
#define HostCmd_CMD_802_11_SET_WEP                  0x0013
#define HostCmd_CMD_802_11_GET_STAT                 0x0014
#define HostCmd_CMD_802_3_GET_STAT                  0x0015
#define HostCmd_CMD_802_11_SNMP_MIB                 0x0016
#define HostCmd_CMD_MAC_REG_MAP                     0x0017
#define HostCmd_CMD_BBP_REG_MAP                     0x0018
#define HostCmd_CMD_RF_REG_MAP                      0x0023
#define HostCmd_CMD_MAC_REG_ACCESS                  0x0019
#define HostCmd_CMD_BBP_REG_ACCESS                  0x001a
#define HostCmd_CMD_RF_REG_ACCESS                   0x001b
#define HostCmd_CMD_802_11_RADIO_CONTROL            0x001c
#define HostCmd_CMD_802_11_RF_CHANNEL               0x001d
#define HostCmd_CMD_802_11_RF_TX_POWER              0x001e
#define HostCmd_CMD_802_11_RSSI                     0x001f
#define HostCmd_CMD_802_11_RF_ANTENNA               0x0020
#define HostCmd_CMD_802_11_PS_MODE                  0x0021
#define HostCmd_CMD_802_11_DATA_RATE                0x0022
#define HostCmd_CMD_802_11_AD_HOC_START             0x002B
#define HostCmd_CMD_802_11_AD_HOC_JOIN              0x002C
//#define HostCmd_CMD_SET_ACTIVE_SCAN_SSID          0x002D

#define HostCmd_CMD_802_11_QUERY_RSN_OPTION         0x002d
#define HostCmd_CMD_802_11_QUERY_TKIP_REPLY_CNTRS   0x002e
#define HostCmd_CMD_802_11_ENABLE_RSN               0x002f

#define HostCmd_CMD_MFG_COMMAND                     0x0040

#define HostCmd_CMD_802_11_AD_HOC_STOP              0x0040

#define HostCmd_CMD_802_11_DEEP_SLEEP               0x003E

#define HostCmd_CMD_802_11_HOST_SLEEP_CFG           0x0043
#define HostCmd_CMD_802_11_HOST_SLEEP_AWAKE_CONFIRM 0x0044
#define HostCmd_CMD_802_11_HOST_SLEEP_ACTIVATE      0x0045

// test mode
#define HostCmd_CMD_TEST_TX_MODE                    0x004A
#define HostCmd_CMD_TEST_RX_MODE                    0x004B //It's value is the same as TX_CONTROL_MODE (ref. linux driver)

// read or write region code
#define HostCmd_CMD_REGION_CODE                     0x004C

// read or write MAC address
#define HostCmd_CMD_MAC_ADDRESS                     0x004D

// set LED Control
#define HostCmd_CMD_802_11_LED_CONTROL              0x004E

// Extended Associate CMD
#define HostCmd_CMD_802_11_ASSOCIATE_EXT            0x0050

#define HostCmd_CMD_GSPI_BUS_CONFIG                 0x005A

#define HostCmd_CMD_802_11D_DOMAIN_INFO             0x005b

#define HostCmd_CMD_802_11_KEY_MATERIAL             0x005e

// BT mode configuration (value could change)
#define HostCmd_CMD_BCA_CONFIG                      0x0065

#define HostCmd_CMD_802_11_SLEEP_PARAMS             0x0066

#define HostCmd_CMD_802_11_INACTIVITY_TIMEOUT       0x0067

#define HostCmd_CMD_802_11_SLEEP_PERIOD             0x0068

#define HostCmd_CMD_802_11_BCA_CONFIG_TIMESHARE     0x0069

#define HostCmd_CMD_802_11_BG_SCAN_CONFIG           0x006b
#define HostCmd_CMD_802_11_BG_SCAN_QUERY            0x006c

#define HostCmd_CMD_802_11_CAL_DATA_EXT             0x006d

#define HostCmd_CMD_802_11_TPC_CFG                  0x0072
#define HostCmd_CMD_802_11_PWR_CFG                  0x0073

#define HostCmd_CMD_802_11_FW_WAKE_METHOD           0x0074

#define HostCmd_CMD_802_11_RATE_ADAPT_RATESET       0x0076
#define HostCmd_CMD_802_11_SUBSCRIBE_EVENT          0x0075

#define HostCmd_CMD_802_11_WMM_ACK_POLICY           0x005C
#define HostCmd_CMD_802_11_WMM_GET_STATUS           0x0071

#define HostCmd_CMD_802_11_KEY_ENCRYPT              0x0054
#define HostCmd_CMD_802_11_CRYPTO                   0x0078

//dralee_20060601
#define HostCmd_CMD_802_11_IBSS_COALESING_STATUS    0x0083

//dralee 20061016

#define HostCmd_CMD_802_11_TX_RATE_QUERY            0x007f

#define HostCmd_CMD_802_11_POWER_ADAPT_CFG_EXT      0x007e

#define HostCmd_CMD_802_11_GET_TSF                  0x0080
#define HostCmd_CMD_802_11_WMM_ADDTS_REQ            0x006e
#define HostCmd_CMD_802_11_WMM_DELTS_REQ            0x006f
#define HostCmd_CMD_802_11_WMM_QUEUE_CONFIG         0x0070
#define HostCmd_CMD_802_11_WMM_QUEUE_STATS          0x0081


//***************************************************************************
//
//          Command constant
//

// Define action or option for HostCmd_CMD_802_11_RF_ANTENNA
#define HostCmd_ACT_SET_RX                          0x0001
#define HostCmd_ACT_SET_TX                          0x0002
#define HostCmd_ACT_SET_BOTH                        0x0003
#define HostCmd_ACT_GET_RX                          0x0004
#define HostCmd_ACT_GET_TX                          0x0008
#define HostCmd_ACT_GET_BOTH                        0x000c

// Define action or option for HostCmd_CMD_802_11_SET_WEP
#define HostCmd_ACT_ADD                             0x0002
#define HostCmd_ACT_REMOVE                          0x0004
#define HostCmd_ACT_USE_DEFAULT                     0x0008

#define HostCmd_WEP_KEY_INDEX_MASK                  0x3fffffff
#define HostCmd_NUM_OF_WEP_KEYS                     4
#define HostCmd_TYPE_WEP_40_BIT                     0x0001 // 40 bit
#define HostCmd_TYPE_WEP_104_BIT                    0x0002 // 104 bit
#define HostCmd_TYPE_WEP_128_BIT                    0x0003 // 128 bit
#define HostCmd_TYPE_WEP_TX_KEY                     0x0004 // TX WEP

// Define action or option for HostCmd_CMD_MAC_CONTROL
#define HostCmd_ACT_MAC_RX_ON                       0x0001
#define HostCmd_ACT_MAC_TX_ON                       0x0002
#define HostCmd_ACT_MAC_LOOPBACK_ON                 0x0004
#define HostCmd_ACT_MAC_WEP_ENABLE                  0x0008
#define HostCmd_ACT_MAC_FRAME_TYPE                  0x0010
// #define HostCmd_ACT_MAC_INT_ENABLE               0x0010 // v8, v9 firmware doesn't need this anymore.
#define HostCmd_ACT_MAC_MULTICAST_ENABLE            0x0020
#define HostCmd_ACT_MAC_BROADCAST_ENABLE            0x0040
#define HostCmd_ACT_MAC_PROMISCUOUS_ENABLE          0x0080
#define HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE        0x0100
#define HostCmd_ACT_MAC_WMM_ENABLE                  0x0800
#define HostCmd_ACT_MAC_STRICT_PROTECTION_ENABLE    0x0400
#define HostCmd_ACT_MAC_ADHOC_G_PROTECTION_ON       0x2000
//BugFix
#define HostCmd_ACT_MAC_WEP_TYPE                    0x8000

#define HostCmd_STATUS_MAC_RX_ON                    0x0001
#define HostCmd_STATUS_MAC_TX_ON                    0x0002
#define HostCmd_STATUS_MAC_LOOP_BACK_ON             0x0004
#define HostCmd_STATUS_MAC_WEP_ENABLE               0x0008
#define HostCmd_STATUS_MAC_INT_ENABLE               0x0010

// Define action or option or constant for HostCmd_CMD_MAC_MULTICAST_ADR
#define HostCmd_SIZE_MAC_ADR                        6
#define HostCmd_MAX_MCAST_ADRS                      32


// Define action or option for HostCmd_CMD_802_11_SCAN
#define HostCmd_SCAN_TYPE_ACTIVE                    0x0000
#define HostCmd_SCAN_TYPE_PASSIVE                   0x0001
#define HostCmd_SCAN_MIN_CH_TIME                    100  //60
#define HostCmd_SCAN_MAX_CH_TIME                    100  //60
#define HostCmd_SCAN_PROBE_DELAY_TIME               0
#define HostCmd_SCAN_RADIO_TYPE_BG                  0
#define HostCmd_SCAN_RADIO_TYPE_A                   1
#define HostCmd_SCAN_PASSIVE_MAX_CH_TIME            100

#define HostCmd_BSS_TYPE_BSS                        0x0001
#define HostCmd_BSS_TYPE_IBSS                       0x0002
#define HostCmd_BSS_TYPE_ANY                        0x0003

#define HostCmd_SubCmd_Enter_PS                     0x0030
#define HostCmd_SubCmd_Exit_PS                      0x0031
#define HostCmd_SubCmd_TxPend_PS                    0x0032
#define HostCmd_SubCmd_ChangeSet_PS                 0x0033
#define HostCmd_SubCmd_Sleep_Confirmed              0x0034
#define HostCmd_SubCmd_Full_PowerDown               0x0035
#define HostCmd_SubCmd_Full_PowerUp                 0x0036

#define MAX_HOST_SLEEP_WAKEUP_FILETER_ENTRY  20
#define Host_Sleep_Filter_Type 0x0115

#define WMM_AC_NUMBER                           4
#define WMM_TSPEC               2
#define WMM_ACK_POLICY              3
#define WMM_PARA_IE             4
#define WMM_ACK_POLICY_PRIO         4

#define WMM_IE_LENGTH               0x0009
#define WMM_PARA_IE_LENGTH          0x0018
#define WMM_QOS_INFO_OFFSET         (0x08)
#define WMM_QOS_INFO_UAPSD_BIT          (0x80)

typedef enum {
	DesiredBssType_i = 0,
	OpRateSet_i,
	BcnPeriod_i,
	DtimPeriod_i,
	AssocRspTimeOut_i,
	RtsThresh_i,
	ShortRetryLim_i,
	LongRetryLim_i,
	FragThresh_i,
	//MaxTxMsduLife_i,
	//MaxRxLife_i,
	Dot11D_i,
	Dot11HTPC_i,
	ManufId_i,
	ProdId_i,
	ManufOui_i,
	ManufName_i,
	ManufProdName_i,
	ManufProdVer_i
} SNMP_MIB_INDEX_e;

typedef enum {
	Wlan802_11AuthModeOpen = 0x00,
	Wlan802_11AuthModeShared = 0x01,
	Wlan802_11AuthModeNetworkEAP = 0x80
} WLAN_802_11_AUTHENTICATION_MODE;

// In station FW code, enum type is 1 byte UCHAR,
typedef enum {
	SSID = 0,
	SUPPORTED_RATES,
	FH_PARAM_SET,
	DS_PARAM_SET,
	CF_PARAM_SET,
	TIM,
	IBSS_PARAM_SET,

	COUNTRY_INFO = 7,
	CHALLENGE_TEXT = 16,
	POWER_CONSTRAINT = 32,
	POWER_CAPABILITY = 33,
	TPC_REQUEST  = 34,
	TPC_REPORT   = 35,
	SUPPORTED_CHANNELS = 36,
	CHANNEL_SWITCH_ANN = 37,
	QUIET              = 40,
	IBSS_DFS           = 41,
	ERP_INFO = 42,
	EXTENDED_SUPPORTED_RATES = 50,
	VENDOR_SPECIFIC_221 = 221,
	RM_CAPABILITY = 221,            ///ref: S36.6 of CCX specification v2.8
	WPA_IE = 221,
	WPA_OUI_TYPE = 2,
	WPA2_IE = 48,
	EXTRA_IE = 133,
	WMM_OUI_TYPE = 2
} IEEEtypes_ElementId_e;

/* Information Element IDs */
typedef enum tagINFO_ELEMENT_CCX_IDS {
	ELE_CISCO_AIRONET                   =   133, /* 0x85 */
	ELE_CISCO_ENCAPTRANS                =   136, /* 0x88 (S20 in spec */
	ELE_CISCO_APIP_ADDR                 =   149, /* 0x95 (S21 in spec */
	ELE_CISCO_CLIENT_TX_PWR             =   150, /* 0x96 */
	ELE_CISCO_FAST_HANDOFF              =   156, /* 0x9c */
	ELE_CISCO_SYMBOL                    =   173, /* 0xAD (S22 in spec)*/
	ELE_CISCO_MEASUREMENT_REQUEST       =   38,  /* 0x26 */
	ELE_CISCO_MEASUREMENT_REPORT        =   39,  /* 0x27 */
}  INFO_ELEMENT_CCX_IDS;

typedef struct _SubscibeEvent_t {
	USHORT          EventMap;
	UCHAR           RSSILowValue;
	UCHAR           RSSILowFreq;
	UCHAR           SNRLowValue;
	UCHAR           SNRLowFreq;
	UCHAR           FailValue;
	UCHAR           FailFreq;
	UCHAR           BeaconMissed;
	UCHAR           Reserved;
	UCHAR           RSSIHighValue;
	UCHAR           RSSIHighFreq;
	UCHAR           SNRHighValue;
	UCHAR           SNRHighFreq;
	UCHAR           PreBeaconMissed;
	UCHAR           Reserved2;
} SubscibeEvent_t;


#pragma pack(1)
//***************************************************************************
//
//          Command Data Struct
//
typedef struct _HostCmd_DS_802_11_ASSOCIATE_EXT {
	USHORT                      Command;
	USHORT                      Size;
	USHORT                      SeqNum;
	USHORT                      Result;
	UCHAR                       PeerStaAddr[6];
	IEEEtypes_CapInfo_t         CapInfo;
	USHORT                      ListenInterval;
	USHORT                      BcnPeriod;
	UCHAR                       DtimPeriod;

	MrvlIEtypes_SsIdParamSet_t  SsIdParamSet;
	MrvlIEtypes_PhyParamSet_t   PhyParamSet;
	MrvlIEtypes_SsParamSet_t    SsParamSet;
	MrvlIEtypes_RatesParamSet_t RatesParamSet;

	MrvlIEtypes_RsnParamSet_t   RsnParamSet;

	MrvlIEtypes_WmmParamSet_t   WmmParamSet;
	MrvlIEtypes_WmmUapsd_t    WmmUapsd;

} HostCmd_DS_802_11_ASSOCIATE_EXT,
*PHostCmd_DS_802_11_ASSOCIATE_EXT;

typedef struct _HostCmd_DS_802_11_ASSOCIATE_RESULT {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT  CapInfo;
	USHORT  StatusCode;
	USHORT  AssociationID;
	USHORT  IELength;
	UCHAR   IE[1];
} HostCmd_DS_802_11_ASSOCIATE_RESULT, *PHostCmd_DS_802_11_ASSOCIATE_RESULT;

typedef struct _HostCmd_DS_802_11_POWER_ADAPT_CFG_EXT {
	USHORT       Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	USHORT      Action;     /* 0 = ACT_GET; 1 = ACT_SET; */
	USHORT      EnablePA;   /* 0 = disable; 1 = enable; */
	MrvlIEtypes_PowerAdapt_Group_t  PowerAdaptGroup;
} HostCmd_DS_802_11_POWER_ADAPT_CFG_EXT, *PHostCmd_DS_802_11_POWER_ADAPT_CFG_EXT;

typedef struct _HostCmd_TX_RATE_QUERY {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;
	USHORT      TxRate;
} HostCmd_TX_RATE_QUERY, *PHostCmd_TX_RATE_QUERY;

typedef struct _HostCmd_DS_802_11_RSSI {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	/* weighting factor */
	SHORT  N;

	SHORT Reserved_0;
	SHORT Reserved_1;
	SHORT Reserved_2;
} HostCmd_DS_802_11_RSSI, *PHostCmd_DS_802_11_RSSI;

typedef struct _HostCmd_DS_802_11_RSSI_RSP {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	SHORT  SNR;
	SHORT  NoiseFloor;
	SHORT  AvgSNR;
	SHORT  AvgNoiseFloor;
} HostCmd_DS_802_11_RSSI_RSP, *PHostCmd_DS_802_11_RSSI_RSP;

typedef struct _HostCmd_DS_802_11_SNMP_MIB {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT QueryType;
	USHORT OID;
	USHORT BufSize;
	UCHAR Value[128];
} HostCmd_DS_802_11_SNMP_MIB, *PHostCmd_DS_802_11_SNMP_MIB;

typedef struct _HostCmd_DS_802_11_RF_ANTENNA {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT Action;
	USHORT AntennaMode;             // Number of antennas or 0xffff(diversity)
} HostCmd_DS_802_11_RF_ANTENNA, *PHostCmd_DS_802_11_RF_ANTENNA;

typedef struct _HostCmd_RATE_ADAPT_RATESET {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	USHORT      Action;         // 0: GET; 1: SET

	USHORT      EnableHwAuto;   //0327
	USHORT      Bitmap;
	USHORT      Threshold;
	USHORT      FinalRate;
} HostCmd_RATE_ADAPT_RATESET , *PHostCmd_RATE_ADAPT_RATESET;

typedef struct _HostCmd_DS_802_11_GET_STAT {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	ULONG       Length;

	ULONG       TransmittedFragmentCount;
	ULONG       MulticastTransmittedFrameCount;
	ULONG       FailedCount;
	ULONG       RetryCount;
	ULONG       MultipleRetryCount;
	ULONG       RTSSuccessCount;
	ULONG       RTSFailureCount;
	ULONG       ACKFailureCount;
	ULONG       FrameDuplicateCount;
	ULONG       ReceivedFragmentCount;
	ULONG       MulticastReceivedFrameCount;
	ULONG       FCSErrorCount;
	ULONG       TKIPLocalMICFailures;
	ULONG       TKIPICVErrorCount;
	ULONG       TKIPCounterMeasuresInvoked;
	ULONG       TKIPReplays;
	ULONG       CCMPFormatErrors;
	ULONG       CCMPReplays;
	ULONG       CCMPDecryptErrors;
	ULONG       FourWayHandshakeFailures;
	ULONG       WEPUndecryptableCount;
	ULONG       WEPICVErrorCount;
	ULONG       DecryptSuccessCount;
	ULONG       DecryptFailureCount;
} HostCmd_DS_802_11_GET_STAT , *PHostCmd_DS_802_11_GET_STAT;

typedef struct _HostCmd_DS_MAC_CONTROL {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT Action;                  // RX, TX, INT, WEP, LOOPBACK on/off
	USHORT Reserved;
} HostCmd_DS_MAC_CONTROL, *PHostCmd_DS_MAC_CONTROL;

typedef struct _HostCmd_DS_MAC_MULTICAST_ADR {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT Action;
	USHORT NumOfAdrs;
	UCHAR MACList[HostCmd_SIZE_MAC_ADR*HostCmd_MAX_MCAST_ADRS];
} HostCmd_DS_MAC_MULTICAST_ADR, *PHostCmd_DS_MAC_MULTICAST_ADR;

typedef struct _HostCmd_DS_802_11_TPC_CFG {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	USHORT  Action;
	UCHAR   Enable;
	UCHAR   P0;
	UCHAR   P1;
	UCHAR   P2;
	UCHAR   UseSNR;
} HostCmd_DS_802_11_TPC_CFG, *PHostCmd_DS_802_11_TPC_CFG;

typedef struct _HostCmd_DS_802_11_SET_WEP {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT Action;                      // ACT_ADD, ACT_REMOVE or ACT_ENABLE
	USHORT KeyIndex;                    // Key Index selected for Tx
	UCHAR WEPTypeForKey1;               // 40, 128bit or TXWEP
	UCHAR WEPTypeForKey2;
	UCHAR WEPTypeForKey3;
	UCHAR WEPTypeForKey4;
	UCHAR WEP1[16];                     // WEP Key itself
	UCHAR WEP2[16];
	UCHAR WEP3[16];
	UCHAR WEP4[16];
} HostCmd_DS_802_11_SET_WEP, *PHostCmd_DS_802_11_SET_WEP;

typedef struct _HostCmd_DS_802_11_DEAUTHENTICATE {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	UCHAR MacAddr[6];
	ULONG ReasonCode;
} HostCmd_DS_802_11_DEAUTHENTICATE, *PHostCmd_DS_802_11_DEAUTHENTICATE;

typedef struct _HostCmd_DS_802_11_SCAN {
	USHORT  Command;
	USHORT  Size;
	USHORT  SeqNum;
	USHORT  Result;
	UCHAR   BSSType;
	UCHAR   BSSID[MRVDRV_ETH_ADDR_LEN];
	MrvlIEtypes_SsIdParamSet_t      SsIdParamSet;
	MrvlIEtypes_ChanListParamSet_t  ChanListParamSet;
	MrvlIEtypes_RatesParamSet_t     OpRateSet;
} HostCmd_DS_802_11_SCAN, *PHostCmd_DS_802_11_SCAN;

typedef struct _HostCmd_DS_802_11_SCAN_RSP {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT BSSDescriptSize;
	UCHAR  NumberOfSets;
} HostCmd_DS_802_11_SCAN_RSP, *PHostCmd_DS_802_11_SCAN_RSP;

typedef struct _IEEEtypes_ERPInfo_t {
	UCHAR   ElementId;
	UCHAR   Len;
	UCHAR   ERPFlags;
} IEEEtypes_ERPInfo_t;

typedef struct _HostCmd_DS_802_11_KEY_MATERIAL {
	USHORT  Command;
	USHORT  Size;
	USHORT  SeqNum;
	USHORT  Result;
	USHORT  Action;

	MrvlIEtype_KeyParamSet_t    KeyParamSet;

}  HostCmd_DS_802_11_KEY_MATERIAL, *PHostCmd_DS_802_11_KEY_MATERIAL;

typedef struct _HostCmd_DS_CMD_GSPI_BUS_CONFIG {
	USHORT Command;                 // Command number
	USHORT Size;                    // Size of the data structure
	USHORT SeqNum;                  // Command sequence number
	USHORT Result;                  // Result code

	USHORT Action;  /* ACT_GET / ACT_SET */
	USHORT BusDelayMode; /* Data format Bit[1:0], Delay method Bit[2] */
	USHORT HostTimeDelayToReadPort; /* Number of dummy clocks
                        to wait for read r/w port */
	USHORT HostTimeDelayToReadregister; /* Number of dummy
                        clocks to wait for read reg */
} HostCmd_DS_CMD_GSPI_BUS_CONFIG, *PHostCmd_DS_CMD_GSPI_BUS_CONFIG;

typedef struct _HostCmd_DS_GET_HW_SPEC {
	USHORT Command;                 // Command number
	USHORT Size;                    // Size of the data structure
	USHORT SeqNum;                  // Command sequence number
	USHORT Result;                  // Result code

	USHORT  HWIfVersion;            // version of the hardware interface

	USHORT  Version;                 // HW version
	USHORT  NumOfWCB;                // Max. number of WCB FW can handle
	USHORT  NumOfMCastAdr;           // Max. number of Multicast address FW can handle
	UCHAR   PermanentAddr[6];        // MAC address
	USHORT  RegionCode;              // Region Code
	USHORT  NumberOfAntenna;         // Number of antenna used
	ULONG   FWReleaseNumber;         // 4 byte of FW release number, example 0x1234=1.2.3.4
	ULONG   WcbBase;
	ULONG   RxPdRdPtr;
	ULONG   RxPdWrPtr;
	ULONG   fwCapInfo;              /* Firmware Capability Info */
} HostCmd_DS_GET_HW_SPEC, *PHostCmd_DS_GET_HW_SPEC;

typedef struct _HostCmd_DS_802_11_BG_SCAN_CONFIG {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	USHORT      Action;

	// Enable
	// 0 - Disable 1 - Enable
	UCHAR       Enable;

	// bssType
	//  1 - Infrastructure
	//  2 - IBSS
	//  3 - any
	UCHAR       BssType;

	// ChannelsPerScan
	// No of channels to scan at one scan
	UCHAR       ChannelsPerScan;

	// 0 - Discard old scan results
	// 1 - Discard new scan results
	UCHAR       DiscardWhenFull;

	USHORT      Reserved;

	// ScanInterval
	ULONG       ScanInterval;

	// StoreCondition
	// - SSID Match
	// - Exceed RSSI threshold
	// - SSID Match & Exceed RSSI Threshold
	// - Always
	ULONG       StoreCondition;

	// ReportConditions
	// - SSID Match
	// - Exceed RSSI threshold
	// - SSID Match & Exceed RSSIThreshold
	// - Exceed MaxScanResults
	// - Entire channel list scanned once
	// - Domain Mismatch in country IE
	//
	ULONG       ReportConditions;

	// MaxScanResults
	// Max scan results that will trigger
	// a scn completion event
	USHORT      MaxScanResults;

	//  attach TLV based parameters as needed, e.g.
	//  MrvlIEtypes_SsIdParamSet_t  SsIdParamSet;
	//  MrvlIEtypes_ChanListParamSet_t  ChanListParamSet;
	//  MrvlIEtypes_NumProbes_t     NumProbes;
	//
	UCHAR           TlvData[1];
}  HostCmd_DS_802_11_BG_SCAN_CONFIG, *PHostCmd_DS_802_11_BG_SCAN_CONFIG;

typedef struct _HostCmd_DS_802_11_BG_SCAN_QUERY {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	UCHAR           Flush;
} HostCmd_DS_802_11_BG_SCAN_QUERY, *PHostCmd_DS_802_11_BG_SCAN_QUERY;

/** HostCmd_DS_802_11_BG_SCAN_QUERY_RSP */
typedef struct _HostCmd_DS_802_11_BG_SCAN_QUERY_RSP {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;

	ULONG           ReportCondition;
	USHORT      BSSDescriptSize;
	UCHAR       NumberOfSets;
	//UCHAR           BssDescAndTlvBuffer[1]; 022607 dralee
} HostCmd_DS_802_11_BG_SCAN_QUERY_RSP, *PHostCmd_DS_802_11_BG_SCAN_QUERY_RSP;

typedef struct _HostCmd_DS_802_11_RADIO_CONTROL {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	USHORT Action;
	//dralee_20060613
	//UCHAR  Control; // @bit0: 1/0,on/off, @bit1: 1/0, long/short @bit2: 1/0,auto/fix
	//UCHAR  Reserved;
	USHORT   Control;
} HostCmd_DS_802_11_RADIO_CONTROL, *PHostCmd_DS_802_11_RADIO_CONTROL;

typedef struct _WakeUpFilterEntry {
	USHORT     AddressType;
	USHORT     EthType;
	ULONG      Ipv4Addr;
} WakeUpFilterEntry, *PWakeUpFilterEntry;
typedef struct _HostCmd_DS_HOST_WAKEUP_FILTER {
	MrvlIEtypesHeader_t   Header;
	WakeUpFilterEntry     entry[MAX_HOST_SLEEP_WAKEUP_FILETER_ENTRY];
} HostCmd_DS_HOST_WAKEUP_FILTER, *PHostCmd_DS_HOST_WAKEUP_FILTER;
typedef struct _HostCmd_DS_HOST_SLEEP {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	ULONG  Criteria;
	UCHAR  GPIO;
	UCHAR  Gap;
	HostCmd_DS_HOST_WAKEUP_FILTER Filter;
} HostCmd_DS_HOST_SLEEP, *PHostCmd_DS_HOST_SLEEP;

typedef struct _HostCmd_DS_802_11_PS_MODE {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	//Dralee_20061115
	USHORT SubCommand;  //Action.

	//Dralee_20061115
	USHORT NullPktInterval; //USHORT reserved1;  //PowerMode; dralee_20060220      /*CAM, Max.PSP or Fast PSP */
	USHORT PSNumDtims;
	USHORT reserved2;
	USHORT LocalListenInterval;
	USHORT AdhocAwakePeriod;

} HostCmd_DS_802_11_PS_MODE, *PHostCmd_DS_802_11_PS_MODE;

typedef struct _MrvlIEtypes_RssiThreshold_t {
	MrvlIEtypesHeader_t Header;
	UCHAR           RSSIValue;
	UCHAR           RSSIFreq;
} MrvlIEtypes_RssiParamSet_t;
typedef struct _MrvlIEtypes_SnrThreshold_t {
	MrvlIEtypesHeader_t Header;
	UCHAR           SNRValue;
	UCHAR           SNRFreq;
} MrvlIEtypes_SnrThreshold_t;
typedef struct _MrvlIEtypes_FailureCount_t {
	MrvlIEtypesHeader_t Header;
	UCHAR           FailValue;
	UCHAR           FailFreq;
} MrvlIEtypes_FailureCount_t;
typedef struct _MrvlIEtypes_BeaconsMissed_t {
	MrvlIEtypesHeader_t Header;
	UCHAR           BeaconMissed;
	UCHAR           Reserved;
} MrvlIEtypes_BeaconsMissed_t;
typedef struct _MrvlIEtypes_PreBeaconsMissed_t {
	MrvlIEtypesHeader_t Header;
	UCHAR           PreBeaconMissed;
	UCHAR           Reserved;
} MrvlIEtypes_PreBeaconsMissed_t;
typedef struct _MrvlIEtypes_EventTLV_t {
	MrvlIEtypesHeader_t Header;
	UCHAR           data1;
	UCHAR           data2;
} MrvlIEtypes_EventTLV_t;
typedef struct _HostCmd_DS_802_11_SUBSCRIBE_EVENT {
	USHORT      Command;
	USHORT      Size;
	USHORT      SeqNum;
	USHORT      Result;
	USHORT      Action;
	USHORT      Events;
	MrvlIEtypes_RssiParamSet_t      RssiLow;
	MrvlIEtypes_SnrThreshold_t      SnrLow;
	MrvlIEtypes_FailureCount_t      FailCnt;
	MrvlIEtypes_BeaconsMissed_t     BcnMiss;
	MrvlIEtypes_RssiParamSet_t      RssiHigh;
	MrvlIEtypes_SnrThreshold_t      SnrHigh;
	MrvlIEtypes_PreBeaconsMissed_t  PreBcnMiss;
} HostCmd_DS_802_11_SUBSCRIBE_EVENT, *PHostCmd_DS_802_11_SUBSCRIBE_EVENT;

typedef struct _HostCmd_DS_CMD_MAC_REG_ACCESS {
	USHORT  Command;
	USHORT  Size;
	USHORT  SeqNum;
	USHORT  Result;
	USHORT  Action;     // ACTION_GET or ACTION_SET
	USHORT  Offset;
	ULONG   Value;
} HostCmd_DS_CMD_MAC_REG_ACCESS, *PHostCmd_DS_CMD_MAC_REG_ACCESS;

typedef struct _HostCmd_DS_CMD_MAC_ADDRESS {
	USHORT  Command;
	USHORT  Size;
	USHORT  SeqNum;
	USHORT  Result;
	USHORT  Action;     // ACTION_GET or ACTION_SET
	UCHAR   MacAddress[MRVDRV_ETH_ADDR_LEN];
} HostCmd_DS_CMD_MAC_ADDRESS, *PHostCmd_DS_CMD_MAC_ADDRESS;

typedef struct _HostCmd_DS_802_11_AD_HOC_START {
	USHORT                    Command;
	USHORT                    Size;
	USHORT                    SeqNum;
	USHORT                    Result;
	UCHAR                     SSID[MRVDRV_MAX_SSID_LENGTH];
	UCHAR                     BSSType;
	USHORT                    BeaconPeriod;
	UCHAR                     DTIMPeriod;
	IEEEtypes_SsParamSet_t    SsParamSet;
	IEEEtypes_PhyParamSet_t   PhyParamSet;
	USHORT                    ProbeDelay;
	IEEEtypes_CapInfo_t       Cap;
	UCHAR                     BasicDataRates[14];
	// UCHAR                     OpDataRates[8];
} HostCmd_DS_802_11_AD_HOC_START, *PHostCmd_DS_802_11_AD_HOC_START;
typedef struct _HostCmd_DS_802_11_AD_HOC_RESULT {
	USHORT Command;
	USHORT Size;
	USHORT SeqNum;
	USHORT Result;
	UCHAR  ResultCode;
	// changed due to FW mismatch
	//UCHAR  Reserved[3];
	UCHAR   Reserved[2];
	UCHAR  BSSID[MRVDRV_ETH_ADDR_LEN];
} HostCmd_DS_802_11_AD_HOC_RESULT, *PHostCmd_DS_802_11_AD_HOC_RESULT;

typedef struct _HostCmd_DS_802_11_AD_HOC_JOIN {
	USHORT                          Command;
	USHORT                          Size;
	USHORT                          SeqNum;
	USHORT                          Result;
	IEEEtypes_AdHoc_BssDesc_t  BssDescriptor;
	USHORT                          FailTimeOut;
	USHORT                          ProbeDelay;
	/*
	    TODO: There are 2 more members here for DFS. v9 linux driver doesn't use it. Let me skip them first.
	*/
} HostCmd_DS_802_11_AD_HOC_JOIN, *PHostCmd_DS_802_11_AD_HOC_JOIN;

typedef struct _HostCmd_DS_802_11_IBSS_Coalesing_Status {
	USHORT  Command;
	USHORT  Size;
	USHORT  SeqNum;
	USHORT  Result;
	USHORT  Action;

	USHORT  Enable;
	UCHAR   bssid[6];
	USHORT  BeanconInterval;
	USHORT  AtimWindow;
	USHORT  UseGRateProtection;
} HostCmd_802_11_IBSS_Coalesing_Status, *PHostCmd_802_11_IBSS_Coalesing_Status;

#define HostCmd_ACT_SET                         	0x0001
#define HostCmd_ACT_GET                         	0x0000
#define HostCmd_ENABLE_RSN                      	0x0001
#define HostCmd_DISABLE_RSN                     	0x0000
typedef struct _HostCmd_DS_802_11_ENABLE_RSN
{
    USHORT Command;
    USHORT Size;
    USHORT SeqNum;
    USHORT Result;
    USHORT Action;
    USHORT Enable;     
} HostCmd_DS_802_11_ENABLE_RSN, *PHostCmd_DS_802_11_ENABLE_RSN;

#pragma pack()

#endif //_MRVHOSTCMD_H_
