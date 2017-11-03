/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : LED.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "LED.h" 
#include "My_GPIO.h"
#include "OS_StartFile.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LED_Flash()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LED_Flash(void)
{ 
	 OS_BackColor_Set( OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 
	 OS_TextColor_Set( ~OS_Point_Read(FONT_3*2-1,FONT_3*5-1)); 
	 OS_String_Show(FONT_3*2,FONT_3*5,(u8*)"LED_Flash.wos",FONT_3);
	  
	 LED_GREEN = ~LED_GREEN;  
	 LEDRED_OFF(); 	     
	 return 0;															
}

unsigned int LED_Flash_Start(void)
{
	Taskbar_Draw(FONT_1);	 
	return 0;
}

unsigned int LED_Flash_End(void)
{
	Taskbar_Draw(FONT_1); 
	return 0;
}

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





