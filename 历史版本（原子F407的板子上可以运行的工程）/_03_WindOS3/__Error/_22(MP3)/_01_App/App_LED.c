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
Type_Button *Button_LED1,*Button_LED2; 
u8 Led1 = 0,Led2 = 0;

/* ȫ�ֱ������� --------------------------------------------------------------*/
extern u16 DeskSourceColor[4];


/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LED_Flash()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LED_Main(void)		
{   
	 OS_String_Show(FONT_3*4,FONT_3*5,(u8*)"LED",FONT_3,0);	
	
	 /* ˢ�±��� ----------------------------------------*/ 
	 OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_WEAKNESS,NULL);
	 
	 /* ��Ӧ��ť ----------------------------------------*/ 
	 if(OS_Button_State(Button_LED1) == BUTTON_VALID)			 
		Led1 = (Led1+1)%2; 
	
		
	 if(OS_Button_State(Button_LED2) == BUTTON_VALID)				
		Led2 = (Led2+1)%2;	 
		 
	OS_Button_LastClear(Button_LED1);
	OS_Button_LastClear(Button_LED2);	
	 
	/* ����ť��Ϣ ------------------------------------*/
	if(Led1) 		
	{	
		LEDRED_ON(); 
		OS_Button_Show(Button_LED1,BUTTON_UP);
	}	 
	else 
	{
		LEDRED_OFF();
		OS_Button_Show(Button_LED1,BUTTON_DISABLED); 
	} 
		
		
	if(Led2)
	{ 
		LEDGREEN_ON();	
		OS_Button_Show(Button_LED2,BUTTON_UP);
	}	
	 else
	{
		LEDGREEN_OFF(); 
		OS_Button_Show(Button_LED2,BUTTON_DISABLED);
	}	
      	
	 return 0;																	
}		
		
		
unsigned int LED_Back(void)		
{    
	 if(Led2) LED_GREEN = ~LED_GREEN; 
	 else LEDGREEN_OFF();	
	
	 if(Led1)LEDRED_ON(); 
	 else LEDRED_OFF();	
	 return 0;															
}
			
		
unsigned int LED_Start(void)		
{	  
	OSTask_Alter(&App_LED,NULL,100,NULL,OS_THREAD_PRIMARY);
	/* ������ť --------------------------------*/
	Button_LED1 = OS_Button_Creat(FONT_3*1,FONT_3*10,(u8*)" LED1 ",FONT_3,GREEN);
	Button_LED2 = OS_Button_Creat(FONT_3*6,FONT_3*10,(u8*)" LED2 ",FONT_3,GREEN);  
	
	/* ���ó����������ɫ ----------------------*/
	OS_BackColor_Set( OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 		
	OS_TextColor_Set( ~OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 
	
	return 0;
}		
			
			
unsigned int LED_End(void)		
{   
	OSTask_Alter(&App_LED,NULL,300,NULL,OS_THREAD_5);
	LEDRED_OFF(); 	 
	LEDGREEN_OFF();	 
	
	/* ɾ����ť���ͷ��ڴ� ---------------------*/
	OS_Button_Remove(Button_LED1);  
	OS_Button_Remove(Button_LED2);  

	return 0;	
}
	 			
Type_AppList App_LED = {LED_Main,LED_Back,LED_Start,LED_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"LED",300,USE_OS_ICO,gImage_IcoLED};			
																
																				
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





