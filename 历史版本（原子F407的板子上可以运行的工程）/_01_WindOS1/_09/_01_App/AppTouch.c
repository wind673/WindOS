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
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int APP_Touch(void)  
{ 
	 unsigned int Temp_color;  
   
	 TP_Read_XY2(&TouchX,&TouchY);
	 TouchX = TouchX*OS_LCD_WHITH/3600 - 20;
	 TouchY = TouchY*OS_LCD_LENTH/3550 - 20;  
	 if(TouchX <= OS_LCD_WHITH && TouchY <= OS_LCD_LENTH)
	 {
		LCD_Big_Point(TouchX,TouchY,5,GREEN);
	 }
	 else{ TouchX = 0xffff; TouchY = 0Xffff;}  
	 TextColor_Set(Temp_color);
	 return 0;
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





