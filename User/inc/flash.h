/**
  ******************************************************************************
  * @file    flash.h
  * @author  �Բ�
  * @version V1.0
  * @date    7-April-2014
  * @brief   Header for flash.c
  ******************************************************************************
  */
#ifndef __FLASH_H__
#define __FLASH_H__

#include "stm32f4xx.h"
#include "BaseTypes.h"
#include "BaseDefs.h"
#include <stdlib.h>
/* Private define ------------------------------------------------------------*/

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

//
// Exported functions declare
//
BOOL Flash_Write32BitData(UINT32 User_StartAddress,PDWORD p,UINT32 NumByteToWrite);
BOOL Flash_Read32BitData(UINT32 User_StartAddress,PDWORD pBuf,UINT32 NumByteToRead);
BOOL Flash_Write16BitData(UINT32 User_StartAddress,PWORD p,UINT32 NumByteToWrite);
BOOL Flash_Read16BitData(UINT32 User_StartAddress,PWORD p,UINT32 NumByteToRead);
BOOL Flash_Write8BitData(UINT32 User_StartAddress,PBYTE p,UINT32 NumByteToWrite);
BOOL Flash_Read8BitData(UINT32 User_StartAddress,PBYTE p,UINT32 NumByteToRead);
static uint32_t GetSector(uint32_t Address);

#endif // __FLASH_H__

