/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Draw.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* 头文件包含 ----------------------------------------------------------------*/ 
#include "App_Draw.h"  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 

/* 全局函数编写 --------------------------------------------------------------*/

	
/**----------------------------------------------------------------------------  
* @FunctionName  : APP_TouchDraw()     
* @Description   : 画板
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int TouchDraw_Main(void)  
{  
	unsigned int i = 0;
	 
	/* 画出点的缓冲 ----------------------------*/
	for(i=0;i<TouchPoint._CNT;i++) 
	{
		if(TouchPoint._BuffX[i] != 0xffff && TouchPoint._BuffY[i] != 0xffff)
		{			 
			OS_TextColor_Set(~OS_Point_Read(TouchPoint._BuffX[0],TouchPoint._BuffY[0]));  
			OS_Circle_Draw(TouchPoint._BuffX[i],TouchPoint._BuffY[i],5,1,TOUCH_COLOR);  
		}			 
	}		 
	 
	return 0;		
	 
}
 

unsigned int TouchDraw_Start(void)  
{ 
	OS_Clear_Y(FONT_1,0,WHITE);	
	
	/* 屏幕扫描时间调整 ------------------------*/
	OSTask_Alter(&APP_TouchScan,NULL,2,NULL,NULL);
	 
	return 0;
}


unsigned int TouchDraw_End(void)  
{
	/* 屏幕扫描时间调整 ------------------------*/
	if(APP_TouchDraw.state == OS_STATE_CLOSE) OSTask_Alter(&APP_TouchScan,NULL,TOUCH_SCAN_SPEED,NULL,NULL); 
	 
	return 0;
}



	
Type_AppList APP_TouchDraw = {TouchDraw_Main,TouchDraw_Main,TouchDraw_Start,TouchDraw_End, \
							  OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
							  (u8*)"画板",TOUCH_SCAN_SPEED,USE_OS_ICO};  

							  
						
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





