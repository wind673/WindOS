/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : APP_Touch.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "AppTouch.h"
#include "my_TFT.h"
#include "touch.h"
#include "OS_StartFile.h" 
 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
u16 TouchX = 0xffff,TouchY = 0xffff;

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : APP_Touch()     
* @Description   :  
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int APP_TouchScan(void)  
{  
	 TP_Read_XY2(&TouchX,&TouchY);
	 TouchX = TouchX*OS_LCD_WHITH/3600 - 20;
	 TouchY = TouchY*OS_LCD_LENTH/3550 - 20;  
	 if(TouchX <= OS_LCD_WHITH && TouchY <= OS_LCD_LENTH)  return 0;
	 else{ TouchX = 0xffff; TouchY = 0Xffff; return 1;}    
}

/**----------------------------------------------------------------------------  
* @FunctionName  : APP_TouchDraw()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int APP_TouchDraw(void)  
{  
	  
	 if(TouchX <= OS_LCD_WHITH && TouchY <= OS_LCD_LENTH) 
	 {
		 LCD_Big_Point(TouchX,TouchY,5,GREEN); 
		 return 0;
	 }
	 return 1;
	 
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





