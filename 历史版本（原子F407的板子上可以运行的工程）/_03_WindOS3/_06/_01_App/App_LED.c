/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_LED.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_LED.h"  
 
/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
			

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LED_Flash()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LED_Main(void)		
{ 
	 
	 OS_BackColor_Set( OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 		
	 OS_TextColor_Set( ~OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 		
	 OS_String_Show(FONT_3*4,FONT_3*5,(u8*)"LED",FONT_3);		
			 
	 OS_Button_Creat(FONT_3*1,FONT_3*10,(u8*)" LED1 ",FONT_3,GREEN,0);
	 OS_Button_Creat(FONT_3*6,FONT_3*10,(u8*)" LED2 ",FONT_3,GREEN,1);
	 
	 LED_GREEN = ~LED_GREEN;  		
	 LEDRED_OFF(); 	     	
	 return 0;																	
}		
		
		
unsigned int LED_Back(void)		
{  
	 LED_GREEN = ~LED_GREEN;  
	 LEDRED_ON(); 	     
	 return 0;															
}
			
		
unsigned int LED_Start(void)		
{			
	 
	 
	return 0;
}		
			
	
unsigned int LED_End(void)		
{
	 
	LEDRED_OFF(); 
	LED_GREEN_OFF();
	return 0;	
}
							
			
Type_AppList App_LED = {LED_Main,LED_Back,LED_Start,LED_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"LED",300,USE_OS_DESKTOP};			
																
																				
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





