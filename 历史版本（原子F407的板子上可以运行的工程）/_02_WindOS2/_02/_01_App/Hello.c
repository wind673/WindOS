/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Hello.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* 头文件包含 ----------------------------------------------------------------*/          
#include "Hello.h"
#include "my_TFT.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : APP_Hello()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int APP_Hello(void)  
{ 
	 unsigned int Temp_color;       
	 Temp_color = TextColor_Set(GREEN/2);	  
	 Show_String(50,300,(u8*)"(C) COPYRIGHT 2016",FONT_1);
	 Show_String(165,300,(u8*)"Wind",FONT_1);	
	 TextColor_Set(Temp_color);
	 return 0;
}

 

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





