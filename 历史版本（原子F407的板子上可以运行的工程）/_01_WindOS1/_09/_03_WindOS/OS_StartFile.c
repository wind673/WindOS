/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : My_Library.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "My_Library.h" 
#include "OS_StartFile.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 unsigned long int OS_RAM = 0; //RAM计数
Type_Addr FreeHead = {0}; //定义空闲程序运行的头帧   
Type_Addr PrimaryHead = {0}; //定义主程序运行的头帧 
Type_Addr SystemHead= {0}; //定义系统程序运行的头帧 
Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  
Type_Addr *SystemTemp = &SystemHead;  
Type_Addr *FreeRun = &FreeHead;
Type_Addr *PrimaryRun = &PrimaryHead;
Type_Addr *SystemRun = &SystemHead;

/* 全局函数编写 --------------------------------------------------------------*/



/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





