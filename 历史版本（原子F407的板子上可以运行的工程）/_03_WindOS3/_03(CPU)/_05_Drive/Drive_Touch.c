/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Touch.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Touch.h"
#include "User_Library.h" 
#include "touch.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Touch TouchPoint = {0,0,{0},0,0};

/* ȫ�ֺ�����д --------------------------------------------------------------*/
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
	
	 TouchPoint._X = tempX*OS_LCD_WHITH/3600 - 20;//ת��
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
//����ע��� 
Type_AppList APP_TouchScan = {TouchScan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						NULL,TOUCH_SCAN_SPEED};  
	


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





