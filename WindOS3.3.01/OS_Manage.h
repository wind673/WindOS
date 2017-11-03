/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : 系统管理
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
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
extern Type_AppList AppHead[OS_THREAD_MAX];  
 
/* 全局函数声明 --------------------------------------------------------------*/    
uint8_t OSTask_Creat(Type_AppList *_AppList);
uint8_t OSTask_Remove(Type_AppList *_AppList);  
uint8_t OSTask_State(Type_AppList *_AppList,Type_OS_State _State);
uint8_t OSTask_Close(Type_AppList *_AppList);  
uint8_t OSTask_Active(Type_AppList *_AppList);   
uint8_t OSTask_Sleep(Type_AppList *_AppList,uint32_t Sleep);

uint8_t OSRunning_Break(void);
uint8_t OSRunning_Continue(void); 
  				
#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/



