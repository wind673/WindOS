/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Run.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_RUN_H
#define __OS_RUN_H 

/* 头文件包含 ----------------------------------------------------------------*/  

/* 全局宏定义 ----------------------------------------------------------------*/

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Init(void); 	
void OSFree_Thread(void); 
void OSPrimary_Thread(void);			




#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



