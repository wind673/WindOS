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
Type_Button *Button_LED1 = NULL,*Button_LED2 = NULL; 			

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LED_Flash()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LED_Main(void)		
{   
	 OS_String_Show(FONT_3*4,FONT_3*5,(u8*)"LED",FONT_3);		
	 
	 
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
	
	if(Button_LED1 == NULL) //������ť
	{
		Button_LED1 = OS_Button_Creat(FONT_3*1,FONT_3*10,(u8*)" LED1 ",FONT_3,GREEN);
		Button_LED2 = OS_Button_Creat(FONT_3*6,FONT_3*10,(u8*)" LED2 ",FONT_3,GREEN);
	} 
	
	Button_LED1 ->state = Button_Up;	 
	Button_LED2 ->state = Button_Up;
	OS_BackColor_Set( OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 		
	OS_TextColor_Set( ~OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 
	
	return 0;
}		
			
	
unsigned int LED_End(void)		
{
	Button_LED1 ->state = Button_Close;	 
	Button_LED2 ->state = Button_Close;	  
	
	LEDRED_OFF(); 
	LED_GREEN_OFF();
	return 0;	
}
							
			
Type_AppList App_LED = {LED_Main,LED_Back,LED_Start,LED_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"LED",300,USE_OS_DESKTOP};			
																
																				
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





