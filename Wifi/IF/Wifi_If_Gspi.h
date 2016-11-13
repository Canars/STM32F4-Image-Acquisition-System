/******************************
微嵌电子工作室 版权所有
STM32 WIFI 开发板
适用于微嵌电子“灵通壹号WIFI开发板”
详情请登录 http://yuikin.taobao.com
源代码使用协议：本代码仅提供给客户做学习、或者参考WIFI原理之用，你不能在你发布的产品里面
包含本源代码的完整文件或者部分片段），不能出售或者使用本工作室提供的源代码制作相同类型产品，
例如：开发板、学习板，营利性教学讲座等等，否则视为侵权，本工作室保留追究相关法律责任的权利。
*******************************/

#ifndef __WIFI_IF_GSPI_H__
#define __WIFI_IF_GSPI_H__
//
// Macros definitions
//
#define DW_BIT_0        0x00000001
#define DW_BIT_1        0x00000002
#define DW_BIT_2        0x00000004
#define DW_BIT_3        0x00000008
#define DW_BIT_4        0x00000010
#define DW_BIT_5        0x00000020
#define DW_BIT_6        0x00000040
#define DW_BIT_7        0x00000080
#define DW_BIT_8        0x00000100
#define DW_BIT_9        0x00000200
#define DW_BIT_10       0x00000400
#define DW_BIT_11       0x00000800
#define DW_BIT_12       0x00001000
#define DW_BIT_13       0x00002000
#define DW_BIT_14       0x00004000
#define DW_BIT_15       0x00008000
#define DW_BIT_16       0x00010000
#define DW_BIT_17       0x00020000
#define DW_BIT_18       0x00040000
#define DW_BIT_19       0x00080000
#define DW_BIT_20       0x00100000
#define DW_BIT_21       0x00200000
#define DW_BIT_22       0x00400000
#define DW_BIT_23       0x00800000
#define DW_BIT_24       0x01000000
#define DW_BIT_25       0x02000000
#define DW_BIT_26       0x04000000
#define DW_BIT_27       0x08000000
#define DW_BIT_28       0x10000000
#define DW_BIT_29       0x20000000
#define DW_BIT_30       0x30000000
#define DW_BIT_31       0x80000000

#define W_BIT_0         0x0001
#define W_BIT_1         0x0002
#define W_BIT_2         0x0004
#define W_BIT_3         0x0008
#define W_BIT_4         0x0010
#define W_BIT_5         0x0020
#define W_BIT_6         0x0040
#define W_BIT_7         0x0080
#define W_BIT_8         0x0100
#define W_BIT_9         0x0200
#define W_BIT_10        0x0400
#define W_BIT_11        0x0800
#define W_BIT_12        0x1000
#define W_BIT_13        0x2000
#define W_BIT_14        0x4000
#define W_BIT_15        0x8000

#define B_BIT_0         0x01
#define B_BIT_1         0x02
#define B_BIT_2         0x04
#define B_BIT_3         0x08
#define B_BIT_4         0x10
#define B_BIT_5         0x20
#define B_BIT_6         0x40
#define B_BIT_7         0x80
#define B_BIT_8		0x100
#define B_BIT_9		0X200
#define B_BIT_10		0x400

#define SPI_API_STATUS							int
#define SD_API_STATUS							int
#define SD_API_STATUS_SUCCESS					0
#define SD_API_STATUS_UNSUCCESSFUL				-1
#define SD_API_SUCCESS(x)						((x)==TRUE)

//=============================================================================
//                                Special DEFINITIONS
//=============================================================================

#define GSPI_WRITE								0x8000

#define CMD_READBASE_REG						0x10
#define CMD_WRITEBASE_REG						0x14
#define CMD_RDWRPORT_REG						0x18

#define DATA_READBASE_REG						0x1C
#define DATA_WRITEBASE_REG						0x20
#define DATA_RDWRPORT_REG						0x24

#define SCRATCH_1_REG							0x28
#define SCRATCH_2_REG							0x2C
#define SCRATCH_3_REG							0x30
#define SCRATCH_4_REG							0x34

#define HOST_INT_CTRL_REG						0x40

#define CARD_INT_CAUSE_REG						0x44
#define CARD_INT_STATUS_REG						0x48
#define CARD_INT_EVENT_REG						0x4A
#define CARD_INT_EVENT_MASK_REG					0x4C
#define CARD_INT_STATUS_MASK_REG				0x50
#define CARD_INT_RESET_SELECT_REG				0x54

#define HOST_INT_CAUSE_REG						0x58
#define HOST_INT_STATUS_REG						0x5C
#define HOST_INT_EVENT_REG						0x5E
#define HOST_INT_EVENT_MASK_REG					0x60
#define HOST_INT_STATUS_MASK_REG				0x64
#define HOST_INT_RESET_SELECT_REG				0x68

/* Bit definition for CARD_INT_CAUSE (Card Interrupt Cause) */
#define CIC_TxDnLdOvr							B_BIT_0
#define CIC_RxUpLdOvr							B_BIT_1
#define CIC_CmdDnLdOvr							B_BIT_2
#define CIC_HostEvent							B_BIT_3
#define CIC_CmdUpLdOvr							B_BIT_4
#define CIC_PwrDown								B_BIT_5

#define HIS_MASK								0xFF
#define HIS_TxDnLdRdy							B_BIT_0
#define HIS_RxUpLdRdy							B_BIT_1
#define HIS_CmdDnLdRdy							B_BIT_2
#define HIS_CardEvent							B_BIT_3
#define HIS_CmdUpLdRdy							B_BIT_4
#define HIS_WrFifoOvrflow						B_BIT_5
#define HIS_RdFifoUndrflow						B_BIT_6
#define HIS_WlanReady							B_BIT_7

#define HIC_DEFAULT_VALUE						0

/* Bit definition for HOST_INT_CTRL_REG (Host Interrupt Control) */
#define HIC_WakeUp								B_BIT_0
#define HIC_WlanRdy								B_BIT_1
#define HIC_TxDnldAuto							B_BIT_5
#define HIC_RxUpldAuto							B_BIT_6
#define HIC_CmdDnldAuto							B_BIT_7
#define HIC_CmdUpldAuto							B_BIT_8

#define DOWNLOAD_HOST_INT_STATUS_RDY			B_BIT_0
#define UPLOAD_HOST_INT_STATUS_RDY				B_BIT_1


/* Value to check once the firmware is downloaded */
#define FIRMWARE_DNLD_OK 						0x88888888

// block size of FW download
#define SPI_FW_DOWNLOAD_PKTCNT					64
#define FIRMWARE_DNLD_END 						0x0000

//=============================================================================
//                                DEFINITIONS
//=============================================================================
#define MRVL_8100_SPI_VER_ID					0x02 // TODO: what should this be?

// amount of time to wait in ms to check FW again if it is not ready
#define SPI_FW_NOT_READY_WAIT_TIME				5

#define CF_READ_CMD_BUF_SIZE					128
#define CF_WRITE_CMD_BUF_SIZE					128

#define SPI_EXTENDED_IO_BLOCK_SIZE				32  //256  //128	//512  //32

#define SPI_IO_READY							0x08
#define SPI_CIS_CARD_READY						0x04
#define SPI_UPLOAD_CARD_READY					0x02
#define SPI_DOWNLOAD_CARD_READY					0x01
#define SPI_IO_PORT								0x10000


#define UPLOADDOWNLOAD_HOST_INT_STATUS_RDY		0x03

// host control register
#define HCR_HOST_INT_STATUS_REGISTER			0x5C
//#define HCR_HOST_INT_STATUS_RSR_REGISTER		0x6
#define HCR_HOST_INT_MASK_REGISTER				0x64
//#define HCR_HOST_CONFIGURATION_REGISTER		0x3

// card control register
//#define CCR_CARD_STATUS_REGISTER				0x20

//#define LENGTH_SCRATCH_REGISTER               0x80FE
#define PACKET_TYPE_MAC_EVENT_SCRATCH_REGISTER  0x80FC

// code which will be in the scratch register after FW is initialized
#define SPI_FW_INIT_CODE						0xFEDC

// 50 ms wait time
#define PKT_WAIT_TIME							50000   // number of 10 us units

///Used by SDIO interface. Define an empty one
#define MRVL_SOFT_INT_ChipReset					(1<<0)
#define MRVL_SOFT_INT_AutoDeepSleep				(1<<2)
#define MRVL_SOFT_INT_TxRequest         		0x08

//
// Exported functions declare
//


//
// Exported variables declare
//


#endif // __WIFI_IF_GSPI_H__
