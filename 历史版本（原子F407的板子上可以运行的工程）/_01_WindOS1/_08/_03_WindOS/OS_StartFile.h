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
#define OS_TIME_SLICE 1000//1ms

/* 晶振定义 ------------------------------*/
#define OS_FOSC 168000000   //168M

/* 显示屏定义 ----------------------------*/
#define OS_LCD_WHITH  	240	 //宽度
#define OS_LCD_LENTH  	400	 //高度

/* 最大任务数 ----------------------------*/
#define OS_TASK_MAX  10000

/* RAM地址 ----------------------------*/
#define OS_RAM_START 0x20000000  
#define OS_RAM_SIZE  0x20000

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  


/* WindOS宏定义 --------------------------------------------------------------*/
/* _state -------------------------------*/
#define OS_STATE_CLOSE   		 0    //关闭
#define OS_STATE_ACTIVE   		 1	  //激活
#define OS_STATE_BACKSTAGE  	 2	  //后台运行
#define OS_STATE_ONE_OFF  	     3	  //只运行一次
#define OS_STATE_SUSPEND  	     4	  //暂停一次

/* prioity ------------------------------*/
#define OS_THREAD_FREE  	     254  //空闲线程
#define OS_THREAD_SYSTEM  	     4	  //线程4 系统线程
#define OS_THREAD_PRIMARY 	 	 7	  //线程7 主线程  
#define OS_THREAD_6  	      	 6	  //线程6
#define OS_THREAD_5  	    	 5	  //线程5 
#define OS_THREAD_3  	    	 3	  //线程3
#define OS_THREAD_2  	     	 2	  //线程2
#define OS_THREAD_1  	     	 1	  //线程1 
#define OS_THREAD_0  	     	 0	  //线程0 


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





