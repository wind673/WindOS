/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_LED.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __LED_FLASH_H
#define __LED_FLASH_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
#define LEDRED_ON() 	LED_RED = 0			
#define LEDRED_OFF() 	LED_RED = 1		
													
#define LEDGREEN_ON() 	LED_GREEN = 0	
#define LED_GREEN_OFF() LED_GREEN = 1	
																
									
/* 结构体声明 ----------------------------------------------------------------*/ 
																	
/* 全局变量声明 --------------------------------------------------------------*/ 
 																														
/* 全局函数声明 --------------------------------------------------------------*/  
extern Type_AppList App_LED;



#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



