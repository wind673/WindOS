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
#include "AppTouch.h" 
#include "touch.h"
#include "OS_StartFile.h"  

Type_Touch TouchPoint = {0,0,{0},0,0};

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : APP_TouchScan()     
* @Description   :  
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int APP_TouchScan(void)  
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

/**----------------------------------------------------------------------------  
* @FunctionName  : APP_TouchDraw()     
* @Description   : 画板
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int APP_TouchDraw(void)  
{  
	 unsigned int i = 0;
	 unsigned int Temp_Color; 
	 
	 Temp_Color = OS_TextColor_Set(YELLOW);  
	
	 for(i=0;i<TouchPoint._CNT;i++)  OS_Circle_Draw(TouchPoint._XY[i][0],TouchPoint._XY[i][1],5,1,TOUCH_COLOR); 
	  
	 TouchPoint._CNT = 0;	
	 
	 OS_TextColor_Set(Temp_Color); 
	 return 0;
	 
}


unsigned int APP_TouchDraw_End(void)  
{
	OSTask_Alter(APP_TouchScan,NULL,20,OS_STATE_ACTIVE,NULL);
	Taskbar_Draw(FONT_1); 
	return 0;
}


unsigned int APP_TouchDraw_Start(void)  
{
	unsigned int i = 0; 
	Taskbar_Draw(FONT_1);
	OSTask_Alter(APP_TouchScan,NULL,4,OS_STATE_ACTIVE,NULL);
	for(i=0;i<TouchPoint._CNT;i++)
	{
		TouchPoint._XY[i][0] = 0xffff;
		TouchPoint._XY[i][1] = 0xffff; 
	}
	 TouchPoint._CNT = 0;	
	
	 return 0;
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





