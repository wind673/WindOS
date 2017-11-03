/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : APP_Touch.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* 头文件包含 ----------------------------------------------------------------*/ 
#include "App_Touch.h" 
#include "touch.h"
 

Type_Touch TouchPoint = {0,0,{0},0,0};


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : TouchScan()     
* @Description   : None
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int TouchScan(void)  
{  
	 u16 tempX = 0xffff,tempY = 0xffff;
	 TP_Read_XY2(&tempX,&tempY);
	
	 TouchPoint._X = tempX*OS_LCD_WHITH/3600 - 20;//转换
	 TouchPoint._Y = tempY*OS_LCD_LENTH/3550 - 20;  
	 
	 if(TouchPoint._X <= OS_LCD_WHITH && TouchPoint._Y <= OS_LCD_LENTH)	
	 { 	
		TouchPoint._XY[TouchPoint._CNT][0] = TouchPoint._X;	
		TouchPoint._XY[TouchPoint._CNT][1] = TouchPoint._Y; 	
		TouchPoint._CNT = (TouchPoint._CNT + 1)%100;	
		TouchPoint._state = 1;	
		return 0;	
	 }	
	 else{ TouchPoint._X = 0xffff; TouchPoint._Y = 0Xffff; TouchPoint._state = 0;  return 1;}    
		
		
}  			
//程序注册表 
Type_AppList APP_TouchScan = {TouchScan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						NULL,TOUCH_SCAN_SPEED};  
	
	
/**----------------------------------------------------------------------------  
* @FunctionName  : APP_TouchDraw()     
* @Description   : 画板
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int TouchDraw_Main(void)  
{  
	 unsigned int i = 0;
	 
	
	 for(i=0;i<TouchPoint._CNT;i++) 
	{
		 OS_TextColor_Set(~OS_Point_Read(TouchPoint._XY[0][0],TouchPoint._XY[0][1]));   	
		 OS_Circle_Draw(TouchPoint._XY[i][0],TouchPoint._XY[i][1],5,1,TOUCH_COLOR);  	
	}		
	 TouchPoint._CNT = 0;		
																	
	 return 0;		
	 
}
 

unsigned int TouchDraw_End(void)  
{
	OSTask_Alter(&APP_TouchScan,NULL,TOUCH_SCAN_SPEED,NULL,NULL); 
	Taskbar_Draw(FONT_1); 
	return 0;
}


unsigned int TouchDraw_Start(void)  
{
	unsigned int i = 0; 
	Taskbar_Draw(FONT_1);
	OSTask_Alter(&APP_TouchScan,NULL,4,NULL,NULL);
	for(i=0;i<TouchPoint._CNT;i++)
	{
		TouchPoint._XY[i][0] = 0xffff;
		TouchPoint._XY[i][1] = 0xffff; 
	}
	 TouchPoint._CNT = 0;	
	
	 return 0;
}

Type_AppList APP_TouchDraw = {TouchDraw_Main,TouchDraw_Main,TouchDraw_Start,TouchDraw_End, \
							  OS_STATE_ACTIVE_ON,OS_THREAD_PRIMARY, \
							  (u8*)"画板",TOUCH_SCAN_SPEED,NULL,NULL};  

							  
						
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





