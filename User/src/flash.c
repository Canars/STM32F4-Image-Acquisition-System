/**
  ******************************************************************************
  * @file    flash.c
  * @author  ут╡с
  * @version V1.0
  * @date    8-April-2014
  * @brief   This file includes the read and write operation of stm32f4's flash
  ******************************************************************************
*/
#include "flash.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0 ;
/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
	else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }
  return sector;
}

/**
  * @brief  Flash Write 32bit Data from  given address
  * @param  uint32_t User_BaseAddress,uint32_t *p,uint32_t NumByteToWrite
  * @retval The status of write operation
  */
BOOL Flash_Write32BitData(UINT32 User_StartAddress,PDWORD p,UINT32 NumByteToWrite)
{
	uint32_t StartSector = 0, EndSector = 0, Address = 0,i = 0 ;
	__IO uint32_t MemoryProgramStatus = 0;
	/* Get the number of the start and end sectors */
  StartSector = GetSector(User_StartAddress);
  EndSector = GetSector(User_StartAddress + NumByteToWrite);
 /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	for(i=StartSector;i<=EndSector;i+=8)
	{
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
			 be done by word */ 
		if(FLASH_EraseSector(i,VoltageRange_3) != FLASH_COMPLETE)
		{
			while(1);
		}
	};
	/* Program the user Flash area word by word
    (area defined by User_StartAddress and User_EndAddress) ***********/
	Address = User_StartAddress;
	while(Address < User_StartAddress + NumByteToWrite)
	{
		if(FLASH_ProgramWord(Address,*p) == FLASH_COMPLETE)
		{
			Address += 4;
			p++;
		}
	}
	/* Lock the Flash to disable the flash control register access (recommended
		 to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 
	return TRUE;
}

/**
  * @brief  Flash Read 32bit data from  given address
  * @param  uint32_t User_BaseAddress,PDWORD p,uint32_t NumByteToRead
  * @retval None
  */
BOOL Flash_Read32BitData(UINT32 User_StartAddress,PDWORD pBuf,UINT32 NumByteToRead)
{
	uint32_t Address;
  Address	= User_StartAddress;
	while(NumByteToRead-- > 0)
	{
		*pBuf = *(uint32_t*)Address;
		pBuf++;
		Address += 4;
	}
	return TRUE;
}

/**
  * @brief  Flash Write 16bit Data from  given address
  * @param  uint32_t User_BaseAddress,uint32_t *p,uint32_t NumByteToWrite
  * @retval The status of write operation
  */
BOOL Flash_Write16BitData(UINT32 User_StartAddress,PWORD p,UINT32 NumByteToWrite)
{
	uint32_t StartSector = 0, EndSector = 0, Address = 0,i = 0 ;
	__IO uint32_t MemoryProgramStatus = 0;
	/* Get the number of the start and end sectors */
  StartSector = GetSector(User_StartAddress);
  EndSector = GetSector(User_StartAddress + NumByteToWrite);
 /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	for(i=StartSector;i<=EndSector;i+=8)
	{
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
			 be done by word */ 
		if(FLASH_EraseSector(i,VoltageRange_3) != FLASH_COMPLETE)
		{
			while(1);
		}
	};
	/* Program the user Flash area word by word
    (area defined by User_StartAddress and User_EndAddress) ***********/
	Address = User_StartAddress;
	while(Address < User_StartAddress + NumByteToWrite)
	{
		if(FLASH_ProgramHalfWord(Address,*p) == FLASH_COMPLETE)
		{
			Address += 2;
			p++;
		}
	}
	/* Lock the Flash to disable the flash control register access (recommended
		 to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 
	return TRUE;
}
/**
  * @brief  Flash Read 26bit data from  given address
  * @param  uint32_t User_BaseAddress,PWORD p,uint32_t NumByteToRead
  * @retval None
  */
BOOL Flash_Read16BitData(UINT32 User_StartAddress,PWORD pBuf,UINT32 NumByteToRead)
{
	uint32_t Address;
  Address	= User_StartAddress;
	while(NumByteToRead-- > 0)
	{
		*pBuf = *(uint32_t*)Address;
		pBuf++;
		Address += 2;
	}
	return TRUE;
}
/**
  * @brief  Flash Write 8bit Data from  given address
  * @param  uint32_t User_BaseAddress,PBYTE p,uint32_t NumByteToWrite
  * @retval The status of write operation
  */
BOOL Flash_Write8BitData(UINT32 User_StartAddress,PBYTE p,UINT32 NumByteToWrite)
{
	uint32_t StartSector = 0, EndSector = 0, Address = 0,i = 0 ;
	__IO uint32_t MemoryProgramStatus = 0;
	/* Get the number of the start and end sectors */
  StartSector = GetSector(User_StartAddress);
  EndSector = GetSector(User_StartAddress + NumByteToWrite);
 /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
//	for(i=StartSector;i<=EndSector;i+=8)
//	{
//		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
//			be done by word */ 
//		if(FLASH_EraseSector(i,VoltageRange_3) != FLASH_COMPLETE)
//		{
//			while(1);
//		}
//	};
	/* Program the user Flash area word by word
    (area defined by User_StartAddress and User_EndAddress) ***********/
	Address = User_StartAddress;
	while(Address < User_StartAddress + NumByteToWrite)
	{
		if(FLASH_ProgramByte(Address,*p) == FLASH_COMPLETE)
		{
			Address++;
			p++;
		}
	}
	/* Lock the Flash to disable the flash control register access (recommended
		 to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 
	return TRUE;
}
/**
  * @brief  Flash Read 8bit data from  given address
  * @param  uint32_t User_BaseAddress,PBYTE p,uint32_t NumByteToRead
  * @retval None
  */
BOOL Flash_Read8BitData(UINT32 User_StartAddress,PBYTE pBuf,UINT32 NumByteToRead)
{
	uint32_t Address;
  Address	= User_StartAddress;
	while(NumByteToRead-- > 0)
	{
		*pBuf = *(uint32_t*)Address;
		pBuf++;
		Address++;
	}
	return TRUE;
}