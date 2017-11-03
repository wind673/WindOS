/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Flash.h
* @Description : None
* @Date        : 2016/4/18
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_FLASH_H
#define __DRIVE_FLASH_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
/* FLASH��ʼ��ַ ---------------------------*/
#define STM32_FLASH_BASE ADDR_FLASH_SECTOR_9 	//STM32 FLASH����ʼ��ַ
 
/* FLASH ��������ʼ��ַ --------------------*/ 
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	//����0��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	//����1��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	//����2��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	//����3��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	//����4��ʼ��ַ, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	//����5��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000) 	//����6��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000) 	//����7��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     ((u32)0x08080000) 	//����8��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     ((u32)0x080A0000) 	//����9��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    ((u32)0x080C0000) 	//����10��ʼ��ַ,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    ((u32)0x080E0000) 	//����11��ʼ��ַ,128 Kbytes  

 
/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
u32 InFLASH_ReadWord(u32 addr);
u16 InFLASH_GetFlashSector(u32 addr);
void InFLASH_Write(u32 Addr,u32 *pBuffer,u32 DataLenth);
void InFLASH_Read(u32 Addr,u32 *pBuffer,u32 DataLenth);


#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



