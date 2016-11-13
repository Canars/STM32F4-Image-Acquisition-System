/******************************
΢Ƕ���ӹ����� ��Ȩ����
STM32 WIFI ������
������΢Ƕ���ӡ���ͨҼ��WIFI�����塱
�������¼ http://yuikin.taobao.com
Դ����ʹ��Э�飺��������ṩ���ͻ���ѧϰ�����߲ο�WIFIԭ��֮�ã��㲻�����㷢���Ĳ�Ʒ����
������Դ����������ļ����߲���Ƭ�Σ������ܳ��ۻ���ʹ�ñ��������ṩ��Դ����������ͬ���Ͳ�Ʒ��
���磺�����塢ѧϰ�壬Ӫ���Խ�ѧ�����ȵȣ�������Ϊ��Ȩ���������ұ���׷����ط������ε�Ȩ����
*******************************/

#ifndef __WIFI_CONFIG_H__
#define __WIFI_CONFIG_H__

// Compile option
//#define BUILD_FOR_WRITEFIRMWARE

#define NO_TRACE

//------------------------------------------------------------------------------
// Firmware in flash
//------------------------------------------------------------------------------
/**
	@Attention:stm32F4��Flashֻ�ܰ�sector������ÿ��дflash��Ҫ������д�������sector��
						 ���Բ��ܰѹ̼�������ͬ��sector�У�ֻ�ֱܷ���벻ͬ��sector��
						 ����ȷʵ���˷ѿռ䣬����û�취 ^ ^
*/
#define SYSTEM_FLASH_ADDR			0x08000000UL
#define WIFI_FW_HELPER_ADDR		0x080A0000UL// ����9
#define WIFI_FW_HELPER_SIZE			KBytes(3) // in bytes
#define WIFI_FW_FW_ADDR				0x080C0000UL //����10
#define WIFI_FW_FW_SIZE				KBytes(120) // in bytes

#define WIFI_PROFILE_ADDR			0x080E0000UL //����11

#define FIRMWARE_IN_FLASH		1

//------------------------------------------------------------------------------
// Hw data buffer
//------------------------------------------------------------------------------
#define HW_IODATA_SIZE				KBytes(1)

//------------------------------------------------------------------------------
// Adapter cmd buffer
//------------------------------------------------------------------------------
#define ADAPTER_CMD_BUFFER_LENGTH	KBytes(1)

//------------------------------------------------------------------------------
// Packet buffers
//------------------------------------------------------------------------------
#define PKT_RCVE_BUFF_LENGTH		KBytes(6)
#define PKT_SEND_BUFF_LENGTH		KBytes(6)

//
// WIFI module select
//
#define WM_G_MR_08					1
#define WM_G_MR_09					2

#define WIFI_MODULE					WM_G_MR_08

#endif // __WIFI_CONFIG_H__
