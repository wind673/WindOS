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
/* 平台驱动 --------------------------------*/  
#include "My_Library.h" 
#include "my_sys.h"  
#include "My_GPIO.h"
#include "My_Interrupt.h"
#include "My_Timer.h"
#include "touch.h"
#include <malloc.h>
#include "sys.h"
#include "usart.h"	
#include "malloc.h" 
#include "w25qxx.h"    
#include "exfuns.h"   
#include "sdio_sdcard.h"    
#include "malloc.h" 
#include "fontupd.h"
#include "ff.h"  
#include "text.h"	
#include "delay.h"
#include "usart.h"
#include "lcd.h"


/* 应用程序 --------------------------------*/  
#include "Hello.h"  
#include "LED.h" 
#include "AppTouch.h"
#include "AppTaskbar.h" 
#include "AppDesktop.h" 
#include "App_Read_ScreenID.h" 

	 
/* User宏定义 ---------------------------------------------------------------*/
/* 时间片定义 ----------------------------*/
#define OS_TIME_SLICE 1000//1ms

/* 晶振定义 ------------------------------*/
#define OS_FOSC 168000000   //168M

/* 显示屏定义 ----------------------------*/
#define OS_LCD_WHITH  	240	 //宽度
#define OS_LCD_LENTH  	320	 //高度

/* 最大任务数 ----------------------------*/
#define OS_TASK_MAX  10000

/* RAM地址 -------------------------------*/ 
#define OS_RAM_SIZE  0x8000

/* 颜色 ----------------------------------*/
#define OS_COLOR_FREE  	    (0x02E0)           
#define OS_COLOR_PRIMARY 	(DARKBLUE)           
#define OS_COLOR_SYSTEM  	(RED)           
#define OS_COLOR_OTHER   	(BLACK)           
#define OS_COLOR_CPU   		(WHITE)           
#define OS_COLOR_STATUSBAR  (BLACK)     
 
 
/* WindOS宏定义 --------------------------------------------------------------*/
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 1    //挂起
#define OS_STATE_ACTIVE   		 2	  //激活
#define OS_STATE_BACKSTAGE  	 3	  //后台运行
#define OS_STATE_ONE_OFF  	     4	  //只运行一次 

/* prioity ------------------------------*/
#define OS_THREAD_FREE  	     0xf0  	  //空闲线程
#define OS_THREAD_PRIMARY 	 	 0x07	  //线程7 主线程  
#define OS_THREAD_SYSTEM  	     0x04	  //线程4 系统线程
#define OS_THREAD_6  	      	 0x06	  //线程6
#define OS_THREAD_5  	    	 0x05	  //线程5 
#define OS_THREAD_3  	    	 0x03	  //线程3
#define OS_THREAD_2  	     	 0x02	  //线程2
#define OS_THREAD_1  	     	 0x01	  //线程1 
#define OS_THREAD_0  	     	 0x08	  //线程0 
/* OS_MSG ---------------------------------*/
#define OS_BREAK 	     	     (0x01<<0)	  //缺省值
 

/* 其他 ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //缺省值

/* AppFun ------------------------------*/
typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  

/* 结构体声明 ---------------------------------------------------------------*/ 
typedef struct __AppMember
{  																					
	unsigned char *name;   
	unsigned char thread;//线程  							
    unsigned long int  reload;//程序重载值   	
	unsigned long int  loading;//运行槽   
	volatile unsigned char state;//运行状态   
																			
	CreatFun *AppFun;  //程序的地址  
					 
	struct __AppMember *next;  
	struct __AppMember *last;  
}Type_Addr; //环形队列成员 
	
/* 全局变量声明 --------------------------------------------------------------*/ 
/* 系统消息 ----------------------------------*/ 
extern u32 OS_Msg;			
	
	
	
/* WindOS系统自身头文件 ------------------------------------------------------*/  
#include "OS_Run.h"			
#include "OS_UI.h"			
#include "OS_Manage.h"					

/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Init(void);  		
	
void OSdelay_us(unsigned long int _us);			
void OSdelay_ms(unsigned long int _ms);   		
void OSdelay_s(unsigned long int _s);			

	
#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





