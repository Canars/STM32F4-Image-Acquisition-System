/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef _MRVSTRUCT_H_
#define _MRVSTRUCT_H_
#pragma pack(1)

///////////////////////////////////////////////////////////////////////////
//
//		OID struct
//

typedef struct _OID_MRVL_DS_RATE_ADAPT_RATESET {
	USHORT      EnableHwAuto;
	USHORT      Bitmap;
	USHORT      Threshold;
	USHORT      FinalRate;
} OID_MRVL_DS_RATE_ADAPT_RATESET, *POID_MRVL_DS_RATE_ADAPT_RATESET;

typedef struct _OID_MRVL_DS_TPC_CFG {
	NDIS_OID    Oid;
	UCHAR       Enable;
	UCHAR       P0;
	UCHAR       P1;
	UCHAR       P2;
	UCHAR       UseSNR;
} OID_MRVL_DS_TPC_CFG,  *POID_MRVL_DS_TPC_CFG;


///////////////////////////////////////////////////////////////////////////
//
//		Information elements struct
//

typedef struct _MrvlIEtypesHeader {
	USHORT  Type;
	USHORT  Len;
} MrvlIEtypesHeader_t;

typedef struct _PA_Group_t {
	USHORT      PowerAdaptLevel;
	USHORT      RateBitmap;
	ULONG       Reserved;
} PA_Group_t;
typedef struct _MrvlIEtypes_PowerAdapt_Group_t {
	MrvlIEtypesHeader_t Header;
	PA_Group_t      PA_Group[MAX_POWER_ADAPT_GROUP];
} MrvlIEtypes_PowerAdapt_Group_t;

typedef struct  _MrvlIEtypes_SsIdParamSet_t {
	MrvlIEtypesHeader_t Header;
	UCHAR   SsId[1];
} MrvlIEtypes_SsIdParamSet_t;

typedef struct _FhParamSet_t {
	USHORT  DwellTime;
	UCHAR   HopSet;
	UCHAR   HopPattern;
	UCHAR   HopIndex;
}  FhParamSet_t;
typedef struct _DsParamSet_t {
	UCHAR   CurrentChan;
}  DsParamSet_t;
typedef struct _MrvlIEtypes_PhyParamSet_t {
	MrvlIEtypesHeader_t Header;
	union {
		FhParamSet_t    FhParamSet[1];
		DsParamSet_t    DsParamSet[1];
	} fh_ds;
}  MrvlIEtypes_PhyParamSet_t;


typedef struct _CfParamSet_t {
	UCHAR   CfpCnt;
	UCHAR   CfpPeriod;
	USHORT  CfpMaxDuration;
	USHORT  CfpDurationRemaining;
} CfParamSet_t;
typedef struct _IbssParamSet_t {
	USHORT  AtimWindow;
} IbssParamSet_t;
typedef struct _MrvlIEtypes_SsParamSet_t {
	MrvlIEtypesHeader_t Header;
	union {
		CfParamSet_t    CfParamSet[1];
		IbssParamSet_t  IbssParamSet[1];
	} cf_ibss;
} MrvlIEtypes_SsParamSet_t;

typedef struct  _MrvlIEtypes_RatesParamSet_t {
	MrvlIEtypesHeader_t Header;
	UCHAR   Rates[1];
} MrvlIEtypes_RatesParamSet_t;


typedef struct  _MrvlIEtypes_RsnParamSet_t {
	MrvlIEtypesHeader_t Header;
	UCHAR   RsnIE[1];
}  MrvlIEtypes_RsnParamSet_t;

typedef struct  _MrvlIEtypes_WmmParamSet_t {
	MrvlIEtypesHeader_t Header;
	UCHAR   WmmIE[1];
}  MrvlIEtypes_WmmParamSet_t;

typedef struct  _MrvlIEtypes_WmmUapsd_t {
	MrvlIEtypesHeader_t Header;
	UCHAR   WmmIE[1];
}  MrvlIEtypes_WmmUapsd_t;

typedef struct  _MrvlIEtypes_AuthType_t {
	MrvlIEtypesHeader_t Header;
	USHORT  AuthType;
}  MrvlIEtypes_AuthType_t;

typedef struct _MrvlIEtype_KeyParamSet_t {
	USHORT  Type;       // Type ID
	USHORT  Length;     // Length of Payload
	USHORT  KeyTypeId;  // Type of Key: WEP=0, TKIP=1, AES=2
	USHORT  KeyInfo;    // Key Control Info specific to a KeyTypeId
	USHORT  KeyLen;     // Length of key
	UCHAR   Key[32];    // Key material of size KeyLen
}  MrvlIEtype_KeyParamSet_t, *PMrvlIEtype_KeyParamSet_t;


typedef struct _ChanScanParamSet_t {
	UCHAR   RadioType;
	UCHAR   ChanNumber;
	UCHAR   ScanType;
	USHORT  MinScanTime;
	USHORT  ScanTime;
} ChanScanParamSet_t;
typedef struct  _MrvlIEtypes_ChanListParamSet_t {
	MrvlIEtypesHeader_t Header;
	ChanScanParamSet_t  *ChanScanParam;
} MrvlIEtypes_ChanListParamSet_t;
typedef struct  _MrvlIEtypes_NumProbes_t {
	MrvlIEtypesHeader_t Header;
	USHORT              NumProbes;
} MrvlIEtypes_NumProbes_t;
typedef struct _MrvlIEtypes_BcastProbe_t {
	MrvlIEtypesHeader_t Header;
	USHORT              BcastProbe;
} MrvlIEtypes_BcastProbe_t;

typedef struct _MrvlIEtypes_NumSSIDProbe_t {
	MrvlIEtypesHeader_t Header;
	USHORT          NumSSIDProbe;
} MrvlIEtypes_NumSSIDProbe_t;

typedef struct IEEEtypes_CapInfo_t {
	USHORT Ess: 1;
	USHORT Ibss: 1;
	USHORT CfPollable: 1;
	USHORT CfPollRqst: 1;
	USHORT Privacy: 1;
	USHORT ShortPreamble: 1;
	USHORT Pbcc: 1;
	USHORT ChanAgility: 1 ;
	USHORT  SpectrumMgmt: 1;
	USHORT  QoS: 1;
	USHORT ShortSlotTime: 1;
	USHORT Rsrvd1112: 2;
	USHORT DSSSOFDM: 1;
	USHORT Rsrvd1415: 2;
} IEEEtypes_CapInfo_t;

typedef struct IEEEtypes_FhParamSet_t {
	UCHAR  ElementId;
	UCHAR  Len;
	USHORT DwellTime;
	UCHAR  HopSet;
	UCHAR  HopPattern;
	UCHAR  HopIndex;
} IEEEtypes_FhParamSet_t;
typedef struct IEEEtypes_DsParamSet_t {
	UCHAR ElementId;
	UCHAR Len;
	UCHAR CurrentChan;
} IEEEtypes_DsParamSet_t;

typedef struct IEEEtypes_CfParamSet_t {
	UCHAR  ElementId;
	UCHAR  Len;
	UCHAR  CfpCnt;
	UCHAR  CfpPeriod;
	USHORT CfpMaxDuration;
	USHORT CfpDurationRemaining;
} IEEEtypes_CfParamSet_t;
typedef struct IEEEtypes_IbssParamSet_t {
	UCHAR  ElementId;
	UCHAR  Len;
	USHORT AtimWindow;
} IEEEtypes_IbssParamSet_t;

typedef struct _IEEEtypes_SubbandSet {
	UCHAR   FirstChan;
	UCHAR   NoOfChan;
	UCHAR   MaxTxPwr;

} IEEEtypes_SubbandSet_t;
typedef struct _IEEEtypes_CountryInfoFullSet {
	UCHAR   ElementId;
	UCHAR   Len;
	UCHAR   CountryCode[COUNTRY_CODE_LEN];
	IEEEtypes_SubbandSet_t  Subband[MRVDRV_MAX_SUBBAND_802_11D];
}  IEEEtypes_CountryInfoFullSet_t;

typedef union IEEEtypes_SsParamSet_t {
	IEEEtypes_CfParamSet_t    CfParamSet;
	IEEEtypes_IbssParamSet_t  IbssParamSet;
} IEEEtypes_SsParamSet_t;
typedef union IEEEtypes_PhyParamSet_t {
	IEEEtypes_FhParamSet_t  FhParamSet;
	IEEEtypes_DsParamSet_t  DsParamSet;
} IEEEtypes_PhyParamSet_t;
// Define data structure for Join Command in Ad Hoc mode
// v9 adhoc join
typedef struct _IEEEtypes_AdHoc_BssDesc_t {
	UCHAR                     BSSID[MRVDRV_ETH_ADDR_LEN];
	UCHAR                     SSID[MRVDRV_MAX_SSID_LENGTH];
	UCHAR                     BSSType; // v9 linux driver uses this size.
	USHORT                   BeaconPeriod;
	UCHAR                     DTIMPeriod;
	UCHAR                     TimeStamp[8];
	UCHAR                     LocalTime[8];
	IEEEtypes_DsParamSet_t      DsParamSet;
	UCHAR                                Reserved1[4];
	IEEEtypes_IbssParamSet_t    IbssParamSet;
	UCHAR                                Reserved2[4];
	IEEEtypes_CapInfo_t            Cap;
	UCHAR                                DataRates[NDIS_SUPPORTED_RATES];
} IEEEtypes_AdHoc_BssDesc_t, *PIEEEtypes_AdHoc_BssDesc_t;

///////////////////////////////////////////////////////////////////////////
//
//		Other Mrvell struct
//
typedef struct _MRV_BSSID_IE_LIST {
	NDIS_802_11_FIXED_IEs       FixedIE;
	UCHAR                       VariableIE[MRVDRV_SCAN_LIST_VAR_IE_SPACE];
} MRV_BSSID_IE_LIST, *PMRV_BSSID_IE_LIST;

typedef struct _WPA_SUPPLICANT2 {
	UCHAR   Wpa_ie[256];
	UCHAR   Wpa_ie_len;
} WPA_SUPPLICANT2, *PWPA_SUPPLICANT2;

typedef struct {
	UCHAR ccxEnabled;
	UCHAR cckmEnabled;
	UCHAR maxPowerValid;
	UCHAR maxPower;
	ULONGLONG   CurrentTSF;
	BOOLEAN     isMediaConnected;
} CCX_BSS_Info_t;

typedef struct _MRVL_WEP_KEY {
	ULONG Length;
	ULONG KeyIndex;
	ULONG KeyLength;
	UCHAR KeyMaterial[MRVL_KEY_BUFFER_SIZE_IN_BYTE];
} MRVL_WEP_KEY, *PMRVL_WEP_KEY;

typedef struct _MRVL_WPA_KEY {
	ULONG           KeyIndex;
	ULONG           KeyLength;          // length of key in bytes
	NDIS_802_11_KEY_RSC KeyRSC;
	// variable length depending on above field
	UCHAR           KeyMaterial[MRVL_MAX_WPA_KEY_LENGTH];
} MRVL_WPA_KEY, *PMRVL_WPA_KEY;

typedef struct _MRVL_WPA_KEY_SET {
	// BSSID is common within the set
	NDIS_802_11_MAC_ADDRESS     BSSID;
	MRVL_WPA_KEY                Key[MRVL_NUM_WPA_KEY_PER_SET];
} MRVL_WPA_KEY_SET, *PMRVL_WPA_KEY_SET;

typedef struct _MRVL_NDIS_WPA_KEY {
	UCHAR   EncryptionKey[16];
	UCHAR   MICKey1[8];
	UCHAR   MICKey2[8];
} MRVL_NDIS_WPA_KEY, *PMRVL_NDIS_WPA_KEY;


typedef struct _PMKID_CACHE {
	UCHAR       bssid[MRVDRV_ETH_ADDR_LEN];
	UCHAR       pad[2]; // for 4 bytes boundary. ?do we need it?
	UCHAR       pmkid[LEN_OF_PMKID];
} PMKID_CACHE, *PPMKID_CACHE;

typedef struct _FSW_CCX_ROGUE_AP_DETECTED {
	UINT16 FailureReason;
	NDIS_802_11_MAC_ADDRESS RogueAPMacAddress;
	INT8 RogueAPName[16];
} FSW_CCX_ROGUE_AP_DETECTED, *PFSW_CCX_ROGUE_AP_DETECTED;
typedef struct _FSW_CCX_AUTH_SUCCESS {
	NDIS_802_11_SSID Ssid;
	NDIS_802_11_MAC_ADDRESS MacAddress;
} FSW_CCX_AUTH_SUCCESS;
typedef struct _FSW_CCX_CCKM_RESULT {
	FSW_CCX_CCKM_RESULT_CODE ResultCode;
} FSW_CCX_CCKM_RESULT, *PFSW_CCX_CCKM_RESULT;

typedef struct _KeyMaterial_AES_t {
	UCHAR   AesKey[16];         // AES encryption/decryption key
}  KeyMaterial_AES_t, *PKeyMaterial_AES_t;

typedef struct _KeyMaterial_TKIP_t {
	UCHAR   TkipKey[16];        // TKIP encryption/decryption key
	UCHAR   TkipTxMicKey[8];    // TKIP TX MIC Key
	UCHAR   TkipRxMicKey[8];    // TKIP RX MIC Key
}  KeyMaterial_TKIP_t, *PKeyMaterial_TKIP_t;

//          WCB descriptor
//
//          Status                : Current Tx packet transmit status
//          PktPtr                : Physical address of the Tx Packet on host PC memory
//          PktLen                : Tx packet length
//          UCHAR DestMACAdrHi[2] : First 2 byte of destination MAC address
//          DestMACAdrLow[4]      : Last 4 byte of destination MAC address
//          DataRate              : Driver uses this field to specify data rate for the Tx packet
//          NextWCBPtr            : Address to next WCB (Used by the driver)
//
typedef struct _WCB {
	ULONG Status;
	ULONG TxControl;
	// Packet offset in CF
	ULONG PktPtr;
	USHORT PktLen;
	UCHAR DestMACAdrHi[2];
	UCHAR DestMACAdrLow[4];
	UCHAR Priority;
	UCHAR PowerMgmt;
	UCHAR Reserved[2];

} WCB, *PWCB;

//
// RxPD descirptor
//
// Status      : Rx packet reception status
// RSSI        : Receive RF signal strength for this packet (dbm)
// Control     : Not used in CF and SDIO
// PktLen      : Number of bytes in the payload
// NF          : Noise floor for this packet
// Rate        : Rate at which this packet is received
// PktPtr      : Offset from the start of the packet to the begining of the payload data
// NextRxPDPtr : Not used in CF and SDIO
//
typedef struct _RxPD {
	USHORT   Status;
	UCHAR    SNR;
	UCHAR    Control;
	USHORT   PktLen;
	UCHAR    NF;
	UCHAR    RxRate;
	ULONG    PktPtr;
	// Based On TX/RX PD Document Ver1.1
	UCHAR    RxPacketType;
	UCHAR    Reserved_1[3];
	UCHAR    Priority;
	UCHAR    Reserved[3];
} RxPD, *PRxPD;

#pragma pack()

#endif //_MRVSTRUCT_H_
