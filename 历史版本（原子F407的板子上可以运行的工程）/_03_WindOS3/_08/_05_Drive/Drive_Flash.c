/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Flash.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : оƬ�ڲ�Flash����
*=============================================================================*/
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Flash.h"		
			
/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : FLASH_ReadWord()    	 
* @Description   : None 	
* @Data          : 2016/4/18	
* @Explain       : 			
*----------------------------------------------------
��ȡָ����ַ�İ���(16λ����) 	
faddr:����ַ 	
����ֵ:��Ӧ����.	
------------------------------------------------------------------------------*/
u32 InFLASH_ReadWord(u32 addr)
{
	return *(vu32*)addr; 
}
 

/**----------------------------------------------------------------------------  
* @FunctionName  : InFLASH_Write()     
* @Description   : None 
* @Data          : 2016/4/18
* @Explain       : 
*----------------------------------------------------
��ָ����ַ��ʼд��ָ�����ȵ�����   
�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����  
д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����  
д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������  
û����Ҫ����,��������������Ȳ�����,Ȼ����������д.   
�ú�����OTP����Ҳ��Ч!��������дOTP��!  
OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F  

Addr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!) 4*8 = 32Bit   
pBuffer:����ָ��
DataLenth:��(32λ)��(����Ҫд���32λ���ݵĸ���.) 
------------------------------------------------------------------------------*/
void InFLASH_Write(u32 Addr,u32 *pBuffer,u32 DataLenth)	
{ 
	FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
	if(Addr<STM32_FLASH_BASE||Addr%4)return;	//�Ƿ���ַ  	
	FLASH_Unlock();		//���� 		
	FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���  
 		
	addrx=Addr;	   //д�����ʼ��ַ
	endaddr=Addr+DataLenth*4;	//д��Ľ�����ַ 
	if(addrx<0X1FFF0000)			//ֻ�����洢��,����Ҫִ�в�������!! 
	{
		while(addrx<endaddr) //ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)  
		{	
			if(InFLASH_ReadWord(addrx)!=0xffffffff)//�з�0XFFFFFFFF�ĵط�,Ҫ�����������			
			{   
				status=FLASH_EraseSector(InFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V֮��!!		
				if(status!=FLASH_COMPLETE) break;	//����������  		
			}else addrx+=4;		
		} 					
	}						
	if(status==FLASH_COMPLETE) 				
	{				
		while(Addr<endaddr) //д����				
		{	
			if(FLASH_ProgramWord(Addr,*pBuffer)!=FLASH_COMPLETE)//д������ 			
			{ 		
				break;	//д���쳣						
			}						
			Addr+=4;				
			pBuffer++;			
		} 		
	}			
	FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���			
	FLASH_Lock();//����		
} 			
	


/**----------------------------------------------------------------------------
* @FunctionName  : InFLASH_Read()     
* @Description   : None 
* @Data          : 2016/4/18
* @Explain       : 
*----------------------------------------------------
��ָ����ַ��ʼ����ָ�����ȵ�����		
ReadAddr:��ʼ��ַ		
pBuffer:����ָ��		
DataLenth:��(4λ)��	
------------------------------------------------------------------------------*/
void InFLASH_Read(u32 Addr,u32 *pBuffer,u32 DataLenth)   	
{
	u32 i;
	for(i=0;i<DataLenth;i++)
	{
		pBuffer[i]=InFLASH_ReadWord(Addr);//��ȡ4���ֽ� = 32Bit		
		Addr+=4;//ƫ��4���ֽ�.	
	}
}
		
		
			
/**----------------------------------------------------------------------------
* @FunctionName  : FLASH_ReadWord()     
* @Description   : None 
* @Data          : 2016/4/18
* @Explain       : 
*----------------------------------------------------
��ȡĳ����ַ���ڵ�flash����
addr:flash��ַ
����ֵ:0~11,��addr���ڵ�����
------------------------------------------------------------------------------*/
u16 InFLASH_GetFlashSector(u32 addr)
{	
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;	
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;	
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;		
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;	
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;	
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;	
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;	
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;	
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;	
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;	
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10; 	
	return FLASH_Sector_11;	
																					
}		
		
		
		
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





