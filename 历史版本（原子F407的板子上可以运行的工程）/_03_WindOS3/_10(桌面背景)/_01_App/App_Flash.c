/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Flash.c
* @Description : None
* @Date        : 2016/4/18
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/          

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "App_Flash.h" 	
 
/* ˽�к궨�� ----------------------------------------------------------------*/
#define BASIC_ADDR   ADDR_FLASH_SECTOR_9
 
 
/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
u8 SendBuff[] = "Hellow WindOS3.6";					
u8 ReceiveBuff[20] = {0};			
#define BUFFSIZE (strlen((const char*)SendBuff)/4+1)  

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : Flash()     
* @Description   : None 
* @Data          : 2016/4/18	
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Flash_Main(void)  	
{ 		
	OS_String_Show(FONT_3*3,FONT_3*2,(u8*)"Flash",FONT_3);							
	
	OS_String_Show(FONT_1,FONT_3*4,(u8*)"FlashSend:",FONT_2);	
	OS_String_Show(FONT_1,FONT_3*5,SendBuff,FONT_2);		
//	OS_Num_Show(FONT_1,FONT_3*5,SendBuff[0],3,FONT_2);	
											
	OS_String_Show(FONT_1,FONT_3*7,(u8*)"FlashReceive:",FONT_2);	
	OS_String_Show(FONT_1,FONT_3*8,ReceiveBuff,FONT_2);		
//	OS_Num_Show(FONT_1,FONT_3*8,ReceiveBuff[0],3,FONT_2);			
	return 0; 		
}	
	
	
unsigned int Flash_Start(void)	
{	 
	InFLASH_Write(BASIC_ADDR,(u32*)SendBuff,BUFFSIZE);							
	InFLASH_Read(BASIC_ADDR,(u32*)ReceiveBuff,BUFFSIZE);		 
	
	return 0;		
}
	
	
unsigned int Flash_End(void)	
{			
				
										
	return 0;		
}


Type_AppList APP_Flash = {Flash_Main,NULL,Flash_Start,Flash_End, \
							OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
							(u8*)"Flash",200,USE_OS_DESKTOP};			
		

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





