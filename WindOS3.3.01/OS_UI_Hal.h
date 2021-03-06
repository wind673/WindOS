/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_UI_Hal.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_UI_HAL_H
#define __OS_UI_HAL_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/

/* 兼容以前的代码 ------------------------------------------------------------*/ 
 	
/* 程序需要 ------------------------------------------------------------------*/  	

/* 结构体声明 ----------------------------------------------------------------*/  

/* 全局变量声明 --------------------------------------------------------------*/   

/* 全局函数声明 --------------------------------------------------------------*/  
int OS_LCD_Init(void);  
int OS_LCD_Clear(u16 color);
unsigned int OS_Point_Read(u16 x,u16 y);
unsigned int OS_TextColor_Set(u16 _color);
unsigned int OS_BackColor_Set(u16 _color);
int OS_Point_Draw(u16 x,u16 y,u16 color);

void OS_Char_Show(u16 x, u16 y, u8 num, u8 size, u8 mode);


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/













