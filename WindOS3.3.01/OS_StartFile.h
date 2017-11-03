/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_StartFile.h
* @Description : 系统启动文件
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/                 
#ifndef __OS_STARTFILE_H
#define __OS_STARTFILE_H

#include "User_Stdafx.h"  
  
/* 时间片定义 ----------------------------*/	
#define OS_TIME_SLICE 1000//1ms	 

/* WindOS宏定义 --------------------------------------------------------------*/		
/* 运行状态 -------------------------------*/			
typedef enum
{  
	OS_STATE_CLOSE_FINISH   =	0,   //关闭完毕 	
	OS_STATE_ACTIVE   		,	//激活  
	OS_STATE_CLOSE   		,   //关闭  
	OS_STATE_ACTIVE_FINISH  ,   //激活完毕   
	OS_STATE_CLOSE_SLEEP   	,   //睡眠状态	  
	OS_STATE_MAX   			,   //状态最大值，用来判断越界 
	
}Type_OS_State;   


/* 创建新线程必填 ========================================*/	
/* 自定义线程 ------------------------------*/	
typedef enum
{
	OS_THREAD_FREE = 0,//空闲线程		
	OS_THREAD_PRIMARY,//主线程  			
	OS_THREAD_SYSTEM,//系统线程	  		
	//在此处填写新的线程名 
	
	OS_THREAD_MAX//最大线程数
}Type_OS_Thread;    


/* 线程的优先级 ---------------------------*/
typedef enum
{
	OS_PRIOITY_FREE 	= 	0, 
	OS_PRIOITY_SYSTEM 	= 	5, 	
	OS_PRIOITY_PRIMARY 	= 	10,  
	//在此处填写新线程优先级

}Type_OS_Prioity; 
/* End =================================================*/	

typedef void(CreatFun)(void); //App 函数定义必须是 void XXX(void)   

typedef struct __AppList
{  		 
	CreatFun *AppMain;  //主程序的地址   		
	CreatFun *AppSleep; //睡眠程序的地址  	
	CreatFun *AppStart; //初始化程序的地址 	 	
	CreatFun *AppEnd;   //结束程序的地址  
	
	volatile Type_OS_State state;//运行状态	
	Type_OS_Thread thread;//线程 	 
	
	char *name;    		
    uint32_t reload;//程序重载值      
 	
	uint32_t loading;//运行槽   
	uint32_t sleep;//睡眠
	struct __AppList *next;   		
}Type_AppList; //任务队列		 



/* OS_MSG -------------------------------*/			
#define OS_BREAK 	     	     (0x01<<0)	  //立即中断所有程序的运行 	 
 
/* 其他 ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //缺省值
		
/* 头文件包含 ----------------------------------------------------------------*/ 		
#include "User_Library.h"  
#include "OS_Manage.h" 
#include "OS_Run.h"
#include "OS_Tools.h"
#include "OS_Hal.h"
//#include "OS_UI.h"
//#include "OS_UI_Hal.h"


/* 全局变量声明 --------------------------------------------------------------*/ 
/* 系统消息 --------------------------------*/ 
extern uint32_t OS_Msg;			 
extern uint16_t OS_TimeOver_Cnt; 

/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Init(void);  	  
 
#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





