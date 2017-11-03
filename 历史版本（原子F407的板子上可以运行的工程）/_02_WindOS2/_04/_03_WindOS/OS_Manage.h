/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_MANAGE_H  
#define __OS_MANAGE_H   
								
/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* 全局宏定义 ----------------------------------------------------------------*/

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 
/* App --------------------------------------------*/
extern Type_Addr AppHead; //定义空闲程序运行的头帧    
 
/* 全局函数声明 --------------------------------------------------------------*/   
unsigned char OSTask_Remove(CreatFun *_AppAddr);            
unsigned int OSCPU_Show(void);
unsigned int OSTask_Show(void);
unsigned char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T,unsigned char _state,unsigned char _thread);  
unsigned char OSTask_Alter(  CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T ,unsigned char _state ,unsigned char _thread) ;

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



