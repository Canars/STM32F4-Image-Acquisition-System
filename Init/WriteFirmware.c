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

#include "helper_spi_8385.h"
#include "gspi8385.h"

BYTE ucBuffer[FLASH_PAGE_SIZE];

void main(void)
{
	UINT16 usID;

	// Bsp Init
	Set_System();

	TraceInit();
	Board_Init ();
	Flash_Init();

	if (1) {
		UINT32 ReadAddrOffset, AddrBase, DataSize, i;
		PBYTE pOriginalData;
		UINT32 usLength;

		if (1) {
			// Write data to flash
			AddrBase = 0;
			Flash_Write (WIFI_FW_HELPER_ADDR, (UINT8*)helperimage, sizeof (helperimage));
			// Read back data for checking...
			ReadAddrOffset = 0;
			pOriginalData = (PBYTE)helperimage;
			DataSize = sizeof (helperimage);
			while (ReadAddrOffset < DataSize) {
				if (ReadAddrOffset + FLASH_PAGE_SIZE < DataSize)
					usLength = FLASH_PAGE_SIZE;
				else
					usLength = DataSize - ReadAddrOffset;
				Flash_Read(AddrBase + ReadAddrOffset, ucBuffer, usLength);
				for (i = 0; i < usLength; i ++) {
					if (ucBuffer[i] != pOriginalData[ReadAddrOffset + i])
						break;
				}
				ReadAddrOffset += usLength;
				if ((i != usLength) && (ReadAddrOffset != DataSize))
					TRACE("Data Verify failed1!\r\n");
			}
		}

		if (1) {
			// Write data to flash
			AddrBase = WIFI_FW_FW_ADDR;
			Flash_Write (AddrBase, (UINT8*)fmimage, sizeof (fmimage));
			// Read back data for checking...
			ReadAddrOffset = 0;
			pOriginalData = (PBYTE)fmimage;
			DataSize = sizeof (fmimage);
			while (ReadAddrOffset < DataSize) {
				if (ReadAddrOffset + FLASH_PAGE_SIZE < DataSize)
					usLength = FLASH_PAGE_SIZE;
				else
					usLength = DataSize - ReadAddrOffset;
				Flash_Read(AddrBase + ReadAddrOffset, ucBuffer, usLength);
				for (i = 0; i < usLength; i ++) {
					if (ucBuffer[i] != pOriginalData[ReadAddrOffset + i])
						break;
				}
				ReadAddrOffset += usLength;
				if ((i != usLength) && (ReadAddrOffset != DataSize))
					TRACE("Data Verify failed1!2\r\n");
			}
		}
	}

	while (1);
}
