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
#include "OS_StartFile.h" 

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
	 unsigned int Text_color,Back_color;       
	 Text_color = OS_TextColor_Set(~OS_Point_Read(49,300));
	 Back_color = OS_BackColor_Set(OS_Point_Read(49,300));
	
	 OS_String_Show(50,300,(u8*)"(C) COPYRIGHT 2016",FONT_1);
	 OS_String_Show(165,300,(u8*)"Wind",FONT_1);
	 
	 OS_String_Show(50,100,(u8*)"读取屏幕的ID",FONT_3);
	 OS_Num_Show(50,160,lcddev.id,8,FONT_3);					
			 
	 OS_BackColor_Set(Back_color);
	 OS_TextColor_Set(Text_color);
	 return 0;
}


unsigned int APP_Hello_Start(void)
{
	Taskbar_Draw(FONT_1);	 
	return 0;
}

unsigned int APP_Hello_End(void)
{
	Taskbar_Draw(FONT_1); 
	return 0;
}
 

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





