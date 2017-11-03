/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_StartFile.h
* @Description : None
* @Date        : 2016/3/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             
#ifndef __OS_STARTFILE_H
#define __OS_STARTFILE_H

/* 头文件包含 ----------------------------------------------------------------*/  
/* WindOS系统自身头文件 ---------------------*/
#include "OS_Run.h"
#include "OS_UI.h"
#include "OS_Manage.h"

/* 平台驱动 --------------------------------*/  
#include "my_sys.h" 
#include "my_TFT.h"  
#include "My_GPIO.h"
#include "My_Interrupt.h"
#include "My_Timer.h"


/* 应用程序 --------------------------------*/  
#include "Hello.h"  
#include "LED.h" 



/* User宏定义 ---------------------------------------------------------------*/
/* 时间片定义 ----------------------------*/
#define TIME_SLICE 10000//10ms

/* 晶振定义 ------------------------------*/
#define FOSC 168000000   //168M

/* 显示屏定义 ----------------------------*/
#define LCD_WHITH  	240	 //宽度
#define LCD_LENTH  	400	 //高度

/* 最大任务数 ----------------------------*/
#define TASK_MAX  1000

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  


/* WindOS宏定义 --------------------------------------------------------------*/
/* _state -------------------------------*/
#define STATE_CLOSE   		 0    //关闭
#define STATE_ACTIVE   		 1	  //激活
#define STATE_BACKSTAGE  	 2	  //后台运行
#define STATE_ONE_OFF  	     3	  //只运行一次
#define STATE_SUSPEND  	     4	  //暂停一次

/* prioity ------------------------------*/
#define OS_FREE  	     254  //空闲线程
#define THREAD_OS  	     0	  //线程0 系统线程
#define THREAD_PRIMARY 	 7	  //线程7 主线程  
#define THREAD_6  	     6	  //线程6
#define THREAD_5  	     5	  //线程6
#define THREAD_4  	     4	  //线程6
#define THREAD_3  	     3	  //线程6
#define THREAD_2  	     2	  //线程6
#define THREAD_1  	     1	  //线程6 

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





