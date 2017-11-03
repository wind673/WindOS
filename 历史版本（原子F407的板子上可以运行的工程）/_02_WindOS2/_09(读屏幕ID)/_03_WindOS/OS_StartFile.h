/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_StartFile.h
* @Description : None
* @Date        : 2016/3/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             
#ifndef __OS_STARTFILE_H
#define __OS_STARTFILE_H

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
/* ƽ̨���� --------------------------------*/  
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


/* Ӧ�ó��� --------------------------------*/  
#include "Hello.h"  
#include "LED.h" 
#include "AppTouch.h"
#include "AppTaskbar.h" 
#include "AppDesktop.h" 
#include "App_Read_ScreenID.h" 

	 
/* User�궨�� ---------------------------------------------------------------*/
/* ʱ��Ƭ���� ----------------------------*/
#define OS_TIME_SLICE 1000//1ms

/* ������ ------------------------------*/
#define OS_FOSC 168000000   //168M

/* ��ʾ������ ----------------------------*/
#define OS_LCD_WHITH  	240	 //���
#define OS_LCD_LENTH  	320	 //�߶�

/* ��������� ----------------------------*/
#define OS_TASK_MAX  10000

/* RAM��ַ -------------------------------*/ 
#define OS_RAM_SIZE  0x8000

/* ��ɫ ----------------------------------*/
#define OS_COLOR_FREE  	    (0x02E0)           
#define OS_COLOR_PRIMARY 	(DARKBLUE)           
#define OS_COLOR_SYSTEM  	(RED)           
#define OS_COLOR_OTHER   	(BLACK)           
#define OS_COLOR_CPU   		(WHITE)           
#define OS_COLOR_STATUSBAR  (BLACK)     
 
 
/* WindOS�궨�� --------------------------------------------------------------*/
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 1    //����
#define OS_STATE_ACTIVE   		 2	  //����
#define OS_STATE_BACKSTAGE  	 3	  //��̨����
#define OS_STATE_ONE_OFF  	     4	  //ֻ����һ�� 

/* prioity ------------------------------*/
#define OS_THREAD_FREE  	     0xf0  	  //�����߳�
#define OS_THREAD_PRIMARY 	 	 0x07	  //�߳�7 ���߳�  
#define OS_THREAD_SYSTEM  	     0x04	  //�߳�4 ϵͳ�߳�
#define OS_THREAD_6  	      	 0x06	  //�߳�6
#define OS_THREAD_5  	    	 0x05	  //�߳�5 
#define OS_THREAD_3  	    	 0x03	  //�߳�3
#define OS_THREAD_2  	     	 0x02	  //�߳�2
#define OS_THREAD_1  	     	 0x01	  //�߳�1 
#define OS_THREAD_0  	     	 0x08	  //�߳�0 
/* OS_MSG ---------------------------------*/
#define OS_BREAK 	     	     (0x01<<0)	  //ȱʡֵ
 

/* ���� ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //ȱʡֵ

/* AppFun ------------------------------*/
typedef unsigned int(CreatFun)(void); //App ������������� unsigned int XXX(void)  

/* �ṹ������ ---------------------------------------------------------------*/ 
typedef struct __AppMember
{  																					
	unsigned char *name;   
	unsigned char thread;//�߳�  							
    unsigned long int  reload;//��������ֵ   	
	unsigned long int  loading;//���в�   
	volatile unsigned char state;//����״̬   
																			
	CreatFun *AppFun;  //����ĵ�ַ  
					 
	struct __AppMember *next;  
	struct __AppMember *last;  
}Type_Addr; //���ζ��г�Ա 
	
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
/* ϵͳ��Ϣ ----------------------------------*/ 
extern u32 OS_Msg;			
	
	
	
/* WindOSϵͳ����ͷ�ļ� ------------------------------------------------------*/  
#include "OS_Run.h"			
#include "OS_UI.h"			
#include "OS_Manage.h"					

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Init(void);  		
	
void OSdelay_us(unsigned long int _us);			
void OSdelay_ms(unsigned long int _ms);   		
void OSdelay_s(unsigned long int _s);			

	
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





