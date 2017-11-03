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
 
/* 结构体声明 ---------------------------------------------------------------*/ 
typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  

 
typedef struct __AppList
{  		 
	CreatFun *AppMain;  //主程序的地址   		
	CreatFun *AppBack;  //后台程序的地址  	
	CreatFun *AppStart; //初始化程序的地址 	 	
	CreatFun *AppEnd;   //结束程序的地址  
	
	volatile unsigned char state;//运行状态	
	unsigned char thread;//线程 	
	
	unsigned char *name;    		
    unsigned long int reload;//程序重载值   
	unsigned char ico_used;   
	 	
	unsigned long int loading;//运行槽   
	struct __AppList *next;   		
}Type_AppList; //任务队列		
				
				
					 
/* User宏定义 ---------------------------------------------------------------*/		
/* 时间片定义 ----------------------------*/	
#define OS_TIME_SLICE 1000//1ms	

/* 晶振定义 ------------------------------*/	
#define OS_FOSC 168000000   //168M

/* 显示屏定义 ----------------------------*/		
#define OS_LCD_WHITH  	240	 //宽度	
#define OS_LCD_LENTH  	320	 //高度	
#define USE_OS_DESKTOP  1	 //使用系统桌面
#define OS_ICO_COLOUR_BACK  GREEN //系统桌面 图标背景颜色
#define OS_ICO_COLOUR_TEXT  BLUE  //系统桌面 图标文字颜色

/* 最大任务数 ----------------------------*/	
#define OS_TASK_MAX  10000	

/* 定义线程 ------------------------------*/	
#define OS_THREAD_FREE  	     0xf0  			  //空闲线程		
#define OS_THREAD_PRIMARY 	 	 OS_THREAD_6	  //线程6 主线程  
#define OS_THREAD_SYSTEM  	     OS_THREAD_4	  //线程4 系统线程	

/* RAM地址 -------------------------------*/ 	
#define OS_RAM_SIZE  0x8000	
	
/* 颜色 ----------------------------------*/
#define OS_COLOR_FREE  	    (GREEN)           
#define OS_COLOR_PRIMARY 	(DARKBLUE)           
#define OS_COLOR_SYSTEM  	(RED)           
#define OS_COLOR_OTHER   	(BLACK)           
#define OS_COLOR_CPU   		(WHITE)           
#define OS_COLOR_STATUSBAR  (BLACK)     
 
 
/* WindOS宏定义 --------------------------------------------------------------*/		
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 1    //挂起（后台）
#define OS_STATE_ACTIVE   		 2	  //激活 
#define OS_STATE_ONE_OFF  	     3	  //只运行一次 
#define OS_STATE_CLOSE   		 4    //关闭  
#define OS_STATE_ACTIVE_ON   	 5    //激活完毕  
#define OS_STATE_CLOSE_ON   	 6    //关闭完毕 	
#define OS_STATE_SUSPEND_ON   	 7    //挂起（后台）	
		
																	
/* prioity ------------------------------*/
#define OS_THREAD_0  	     	 0x00	 
#define OS_THREAD_1  	     	 0x01		
#define OS_THREAD_2  	     	 0x02
#define OS_THREAD_3 	     	 0x03
#define OS_THREAD_4 	     	 0x04
#define OS_THREAD_5  	     	 0x05
#define OS_THREAD_6  	     	 0x06
#define OS_THREAD_7  	     	 0x07


/* OS_MSG -------------------------------*/			
#define OS_BREAK 	     	     (0x01<<0)	  // 	
 
/* 其他 ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //缺省值
		
		
			
/* 头文件包含 ----------------------------------------------------------------*/
/* 平台驱动 -------------------------------*/  
#include "User_Library.h" 
#include "my_sys.h"  
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

/* 硬件驱动 -------------------------------*/  
#include "Drive_GPIO.h"	
#include "Drive_Interrupt.h"	
#include "Drive_Timer.h"	
#include "Drive_Touch.h" 	
#include "Drive_Flash.h"		

/* WindOS系统自身头文件 --------------------*/  
#include "OS_Run.h"			
#include "OS_UI.h"			
#include "OS_Manage.h"					
#include "OS_Desktop.h" 	 

/* 应用程序 --------------------------------*/   
#include "App_LED.h" 				
#include "App_Draw.h" 	
#include "App_ReadScreenID.h" 		
#include "App_Flash.h" 		
#include "App_CPUMonitor.h" 	
#include "App_Flash.h" 			
	

/* 全局变量声明 --------------------------------------------------------------*/ 
/* 系统消息 -------------------------------*/ 
extern u32 OS_Msg;			
	 

/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Init(void);  		
	
void OSdelay_us(unsigned long int _us);			
void OSdelay_ms(unsigned long int _ms);   		
void OSdelay_s(unsigned long int _s);			
	
	
	
	
#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





