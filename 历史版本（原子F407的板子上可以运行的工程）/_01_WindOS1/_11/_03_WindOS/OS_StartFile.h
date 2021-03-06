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
#include "my_sys.h" 
#include "my_TFT.h"  
#include "My_GPIO.h"
#include "My_Interrupt.h"
#include "My_Timer.h"
#include "touch.h"
#include <malloc.h>


/* 应用程序 --------------------------------*/  
#include "Hello.h"  
#include "LED.h" 
#include "AppTouch.h"

	 
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

/* RAM地址 ----------------------------*/
#define OS_RAM_START 0x20000000  
#define OS_RAM_SIZE  0x20000

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

/* AppFun ------------------------------*/
typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  

/* 结构体声明 ----------------------------------------------------------------*/ 
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
/* App --------------------------------------------*/
extern Type_Addr FreeHead; //定义空闲程序运行的头帧   
extern Type_Addr PrimaryHead; //定义主程序运行的头帧 
extern Type_Addr SystemHead; //定义系统程序运行的头帧 
extern Type_Addr *FreeTemp;  
extern Type_Addr *PrimaryTemp;  
extern Type_Addr *SystemTemp;  
extern Type_Addr *FreeRun;
extern Type_Addr *PrimaryRun;
extern Type_Addr *SystemRun;

/* RAM --------------------------------------------*/
extern unsigned long int OS_RAM; //RAM计数
/* RAM --------------------------------------------*/
extern unsigned long int OS_CPU; //CPU计时

/* WindOS系统自身头文件 -------------------------------------------------------*/  
#include "OS_Run.h"
#include "OS_UI.h"
#include "OS_Manage.h"

/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Init(void); 
unsigned int OSTask_Show(void);
unsigned int OSCPU_Monitor(void);


void OSdelay_us(unsigned long int _us);
void OSdelay_ms(unsigned long int _ms);   
void OSdelay_s(unsigned long int _s);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





