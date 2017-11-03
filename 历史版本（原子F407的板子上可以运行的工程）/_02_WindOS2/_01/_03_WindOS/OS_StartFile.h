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
#include "my_sys.h" 
#include "my_TFT.h"  
#include "My_GPIO.h"
#include "My_Interrupt.h"
#include "My_Timer.h"
#include "touch.h"
#include <malloc.h>


/* Ӧ�ó��� --------------------------------*/  
#include "Hello.h"  
#include "LED.h" 
#include "AppTouch.h"

	 
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

/* RAM��ַ ----------------------------*/
#define OS_RAM_START 0x20000000  
#define OS_RAM_SIZE  0x20000

/* WindOS�궨�� --------------------------------------------------------------*/
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 0    //����
#define OS_STATE_ACTIVE   		 1	  //����
#define OS_STATE_BACKSTAGE  	 2	  //��̨����
#define OS_STATE_ONE_OFF  	     3	  //ֻ����һ�� 

/* prioity ------------------------------*/
#define OS_THREAD_FREE  	     254  //�����߳�
#define OS_THREAD_SYSTEM  	     4	  //�߳�4 ϵͳ�߳�
#define OS_THREAD_PRIMARY 	 	 7	  //�߳�7 ���߳�  
#define OS_THREAD_6  	      	 6	  //�߳�6
#define OS_THREAD_5  	    	 5	  //�߳�5 
#define OS_THREAD_3  	    	 3	  //�߳�3
#define OS_THREAD_2  	     	 2	  //�߳�2
#define OS_THREAD_1  	     	 1	  //�߳�1 
#define OS_THREAD_0  	     	 0	  //�߳�0 

/* AppFun ------------------------------*/
typedef unsigned int(CreatFun)(void); //App ������������� unsigned int XXX(void)  

/* �ṹ������ ----------------------------------------------------------------*/ 
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
/* App --------------------------------------------*/
extern Type_Addr AppHead; //������г������е�ͷ֡    
 
/* RAM --------------------------------------------*/
extern unsigned long int OS_RAM; //RAM����
/* RAM --------------------------------------------*/
extern unsigned long int OS_CPU; //CPU��ʱ

/* WindOSϵͳ����ͷ�ļ� -------------------------------------------------------*/  
#include "OS_Run.h"
#include "OS_UI.h"
#include "OS_Manage.h"

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Init(void); 
unsigned int OSTask_Show(void);
unsigned int OSCPU_Monitor(void);


void OSdelay_us(unsigned long int _us);
void OSdelay_ms(unsigned long int _ms);   
void OSdelay_s(unsigned long int _s);

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





