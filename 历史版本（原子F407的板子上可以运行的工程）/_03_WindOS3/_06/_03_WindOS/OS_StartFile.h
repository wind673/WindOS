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
 
/* �ṹ������ ---------------------------------------------------------------*/ 
typedef unsigned int(CreatFun)(void); //App ������������� unsigned int XXX(void)  

 
typedef struct __AppList
{  		 
	CreatFun *AppMain;  //������ĵ�ַ   		
	CreatFun *AppBack;  //��̨����ĵ�ַ  	
	CreatFun *AppStart; //��ʼ������ĵ�ַ 	 	
	CreatFun *AppEnd;   //��������ĵ�ַ  
	
	volatile unsigned char state;//����״̬	
	unsigned char thread;//�߳� 	
	
	unsigned char *name;    		
    unsigned long int reload;//��������ֵ   
	unsigned char ico_used;   
	 	
	unsigned long int loading;//���в�   
	struct __AppList *next;   		
}Type_AppList; //�������		
				
				
					 
/* User�궨�� ---------------------------------------------------------------*/		
/* ʱ��Ƭ���� ----------------------------*/	
#define OS_TIME_SLICE 1000//1ms	

/* ������ ------------------------------*/	
#define OS_FOSC 168000000   //168M

/* ��ʾ������ ----------------------------*/		
#define OS_LCD_WHITH  	240	 //���	
#define OS_LCD_LENTH  	320	 //�߶�	
#define USE_OS_DESKTOP  1	 //ʹ��ϵͳ����
#define OS_ICO_COLOUR_BACK  GREEN //ϵͳ���� ͼ�걳����ɫ
#define OS_ICO_COLOUR_TEXT  BLUE  //ϵͳ���� ͼ��������ɫ

/* ��������� ----------------------------*/	
#define OS_TASK_MAX  10000	

/* �����߳� ------------------------------*/	
#define OS_THREAD_FREE  	     0xf0  			  //�����߳�		
#define OS_THREAD_PRIMARY 	 	 OS_THREAD_6	  //�߳�6 ���߳�  
#define OS_THREAD_SYSTEM  	     OS_THREAD_4	  //�߳�4 ϵͳ�߳�	

/* RAM��ַ -------------------------------*/ 	
#define OS_RAM_SIZE  0x8000	
	
/* ��ɫ ----------------------------------*/
#define OS_COLOR_FREE  	    (GREEN)           
#define OS_COLOR_PRIMARY 	(DARKBLUE)           
#define OS_COLOR_SYSTEM  	(RED)           
#define OS_COLOR_OTHER   	(BLACK)           
#define OS_COLOR_CPU   		(WHITE)           
#define OS_COLOR_STATUSBAR  (BLACK)     
 
 
/* WindOS�궨�� --------------------------------------------------------------*/		
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 1    //���𣨺�̨��
#define OS_STATE_ACTIVE   		 2	  //���� 
#define OS_STATE_ONE_OFF  	     3	  //ֻ����һ�� 
#define OS_STATE_CLOSE   		 4    //�ر�  
#define OS_STATE_ACTIVE_ON   	 5    //�������  
#define OS_STATE_CLOSE_ON   	 6    //�ر���� 	
#define OS_STATE_SUSPEND_ON   	 7    //���𣨺�̨��	
		
																	
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
 
/* ���� ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //ȱʡֵ
		
		
			
/* ͷ�ļ����� ----------------------------------------------------------------*/
/* ƽ̨���� -------------------------------*/  
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

/* Ӳ������ -------------------------------*/  
#include "Drive_GPIO.h"	
#include "Drive_Interrupt.h"	
#include "Drive_Timer.h"	
#include "Drive_Touch.h" 	
#include "Drive_Flash.h"		

/* WindOSϵͳ����ͷ�ļ� --------------------*/  
#include "OS_Run.h"			
#include "OS_UI.h"			
#include "OS_Manage.h"					
#include "OS_Desktop.h" 	 

/* Ӧ�ó��� --------------------------------*/   
#include "App_LED.h" 				
#include "App_Draw.h" 	
#include "App_ReadScreenID.h" 		
#include "App_Flash.h" 		
#include "App_CPUMonitor.h" 	
#include "App_Flash.h" 			
	

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
/* ϵͳ��Ϣ -------------------------------*/ 
extern u32 OS_Msg;			
	 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Init(void);  		
	
void OSdelay_us(unsigned long int _us);			
void OSdelay_ms(unsigned long int _ms);   		
void OSdelay_s(unsigned long int _s);			
	
	
	
	
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





