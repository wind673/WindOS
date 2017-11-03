/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_DMA.h
* @Description : DMA传输测试
* @Date        : 2016/05/22 
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_DMA_H
#define __DRIVE_DMA_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/ 


/* 结构体声明 ----------------------------------------------------------------*/ 
																	
/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_AppList APP_DMA;

/* 全局函数声明 --------------------------------------------------------------*/    
void APP_DMA_Init(void); 
void APP_DMA_ReStart(u8 Speed);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



