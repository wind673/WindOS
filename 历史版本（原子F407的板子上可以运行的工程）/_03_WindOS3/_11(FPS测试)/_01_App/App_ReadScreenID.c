/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_ReadScreenID.c
* @Description : None
* @Date        : 2016/3/31
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "App_ReadScreenID.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : Read_ScreenID()     
* @Description   : None 
* @Data          : 2016/3/31
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Read_ScreenID(void)  
{  
	 if(OS_Point_Read(OS_LCD_WHITH,OS_LCD_LENTH) != WHITE)OS_Clear_Y(FONT_1,0,WHITE);
	
	 OS_String_Show(50,100,(u8*)"��ȡ��Ļ��ID",FONT_3,0); 
	 OS_Num_Show(50,160,lcddev.id,8,FONT_3,1);		 
	 return 0;
}
 

unsigned int Read_ScreenID_Start(void)
{ 
	
	return 0;
}


unsigned int Read_ScreenID_End(void)
{ 
	
	return 0;
}
 
Type_AppList App_Read_ScreenID = {Read_ScreenID,NULL,Read_ScreenID_Start,Read_ScreenID_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"����ID",300,USE_OS_DESKTOP};			
	


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





