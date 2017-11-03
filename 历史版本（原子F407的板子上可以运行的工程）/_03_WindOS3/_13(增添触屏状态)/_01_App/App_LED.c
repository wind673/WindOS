/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_LED.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_LED.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Button Button_LED1 = {NULL},Button_LED2 = {NULL}; 
u8 Led1 = 0,Led2 = 0;

/* 全局变量声明 --------------------------------------------------------------*/
extern u16 DeskSourceColor[4];


/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LED_Flash()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LED_Main(void)		
{   
	 OS_String_Show(FONT_3*4,FONT_3*5,(u8*)"LED",FONT_3,0);	
	
	 /* 刷新背景 ----------------------------------------*/
	 if(DeskSourceColor[0] != OS_Point_Read(1,FONT_1+3)) 
	 if(DeskSourceColor[1] != OS_Point_Read(OS_LCD_WHITH - 1,FONT_1+3))
	 if(DeskSourceColor[2] != OS_Point_Read(1,OS_LCD_LENTH - 1))	
	 if(DeskSourceColor[3] != OS_Point_Read(OS_LCD_WHITH - 1,OS_LCD_LENTH - 1))			
	 OS_Clear_Y(FONT_1,1,NULL);
	 
	 /* 响应按钮 ----------------------------------------*/
	 if(Button_LED1.LastState == Button_Down) 
	 {		 
		 Button_LED1.value = 0; 
		 Led1 = (Led1+1)%2;		 
	 }	
		
	 if(Button_LED2.LastState == Button_Down) 
	 {
		 Button_LED2.value = 0; 
		 Led2 = (Led2+1)%2;	 
	 }
	 
	while(Button_LED1.state == Button_Down);//等待按钮抬起  	
	while(Button_LED2.state == Button_Down);//等待按钮抬起  	 
	OS_Button_LastClear(&Button_LED1);
	OS_Button_LastClear(&Button_LED2); 
	 
	/* 处理按钮消息 ------------------------------------*/
	if(Led1) 		
	{	
		LEDRED_ON(); 
		OS_Button_Show(&Button_LED1,Button_Up);
	}	 
	else 
	{
		LEDRED_OFF();
		OS_Button_Show(&Button_LED1,Button_Disabled);
	} 
	 
	
	if(Led2)
	{ 
		LEDGREEN_ON();	
		OS_Button_Show(&Button_LED2,Button_Up);
	}	
	 else
	{
		LEDGREEN_OFF(); 
		OS_Button_Show(&Button_LED2,Button_Disabled);
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
	static u8 first = 0; 
	if(first == 0)	
	{
		OS_Button_Creat(&Button_LED1,FONT_3*1,FONT_3*10,(u8*)" LED1 ",FONT_3,GREEN);
		OS_Button_Creat(&Button_LED2,FONT_3*6,FONT_3*10,(u8*)" LED2 ",FONT_3,GREEN);
		first = 1;
	}  
	
	/* 开启按钮响应 ----------------------------*/
	OS_Button_Alter(&Button_LED1,Button_Up,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT);
	OS_Button_Alter(&Button_LED2,Button_Up,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT);
	
	OS_BackColor_Set( OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 		
	OS_TextColor_Set( ~OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 
	
	return 0;
}		
			
	
unsigned int LED_End(void)		
{ 
	
	LEDRED_OFF(); 	
	LEDGREEN_OFF();	
	
	/* 关闭按钮响应 ----------------------------*/
	OS_Button_Alter(&Button_LED1,Button_Close,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT);
	OS_Button_Alter(&Button_LED2,Button_Close,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT,OS_DEFAULT);
	
	return 0;	
}
	 			
Type_AppList App_LED = {LED_Main,LED_Back,LED_Start,LED_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"LED",300,USE_OS_DESKTOP};			
																
																				
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





