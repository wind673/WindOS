/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Touch.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Touch.h"
#include "User_Library.h" 
#include "touch.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Touch TouchPoint = {0,0,0,0,{0},0,0,0};

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Drive_GPIO_Init()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
int Drive_Touch_Init(void)
{
	 tp_dev.init(); 
	return 0;
}

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
		TouchPoint._state = TOUCH_STATE_ON;	
		TouchPoint._LastX = TouchPoint._X;
		TouchPoint._LastY = TouchPoint._Y; 
		 
		/* 记录滑动方向 ------------------------------------------------*/
		if(  TouchPoint._LastX - TouchPoint._XY[0][0] >= TOUCH_SLIP_RESPONSE \
		  || TouchPoint._LastY - TouchPoint._XY[0][1] >= TOUCH_SLIP_RESPONSE \
		  || TouchPoint._XY[0][0] - TouchPoint._LastX  >= TOUCH_SLIP_RESPONSE \
		  || TouchPoint._XY[0][1] - TouchPoint._LastY  >= TOUCH_SLIP_RESPONSE ) 
		{
			TouchPoint._slip_direction = 0x00;
			TouchPoint._state = TOUCH_STATE_SLIP;	
			if(TouchPoint._LastX - TouchPoint._XY[0][0] < 0)  TouchPoint._slip_direction |= TOUCH_SLIP_LEFT; 
			if(TouchPoint._LastX - TouchPoint._XY[0][0] > 0)  TouchPoint._slip_direction |= TOUCH_SLIP_RIGHT; 
			if(TouchPoint._LastY - TouchPoint._XY[0][1] < 0)  TouchPoint._slip_direction |= TOUCH_SLIP_UP; 
			if(TouchPoint._LastY - TouchPoint._XY[0][1] > 0)  TouchPoint._slip_direction |= TOUCH_SLIP_DOWN; 
		}		
					
		return 0;	
	 }	
	 else	
	{ 
		
		TouchPoint._X = 0xffff; 
		TouchPoint._Y = 0Xffff; 
		TouchPoint._slip_direction = 0x00;
		TouchPoint._state = TOUCH_STATE_OFF;  
		return 1;
	}    
		
		
}  			
//程序注册表 
Type_AppList APP_TouchScan = {TouchScan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"TouchScan",TOUCH_SCAN_SPEED};  
		
	

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/

						
						
						




