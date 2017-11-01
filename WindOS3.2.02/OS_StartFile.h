/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_StartFile.h
* @Description : ϵͳ�����ļ�
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/                 
#ifndef __OS_STARTFILE_H
#define __OS_STARTFILE_H

/* �ṹ������ ---------------------------------------------------------------*/ 
typedef void(CreatFun)(void); //App ������������� void XXX(void)   

 
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
 	
	unsigned long int loading;//���в�   
	struct __AppList *next;   		
}Type_AppList; //�������		
				
				
					 
/* User�궨�� ---------------------------------------------------------------*/		
/* ʱ��Ƭ���� ----------------------------*/	
#define OS_TIME_SLICE 1000//1ms	

/* ������ ------------------------------*/	
#define OS_FOSC 48000000   //ϵͳʱ��

/* ��ʾ������ ----------------------------*/		
//#define USE_OS_DESKTOP  	1	 //ʹ��ϵͳ����
 
/* ��������� ----------------------------*/	
#define OS_TASK_MAX  100	

/* �Զ����߳� ------------------------------*/	
#define OS_THREAD_FREE  	     0xfe  			  //�����߳�		
#define OS_THREAD_PRIMARY 	 	 OS_THREAD_8	  //���߳�  
#define OS_THREAD_SYSTEM  	     OS_THREAD_5	  //ϵͳ�߳�	

/* RAM��ַ -------------------------------*/ 	
#define OS_RAM_SIZE  0x8000	
	 
/* WindOS�궨�� --------------------------------------------------------------*/		
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 		1    //���𣨺�̨��
#define OS_STATE_ACTIVE   		 		2	 //���� 
#define OS_STATE_ONE_OFF  	     		3	 //ֻ����һ�� 
#define OS_STATE_CLOSE   		 		4    //�ر�  
#define OS_STATE_ACTIVE_FINISH   	 	5    //�������  
#define OS_STATE_CLOSE_FINISH   		6    //�ر���� 	
#define OS_STATE_SUSPEND_FINISH   	 	7    //���𣨺�̨��	 
#define OS_STATE_ONE_OFF_FINISH  	    8	 //ֻ����һ����� 	 		
																	
/* prioity -----------------------------*/
#define OS_THREAD_0  	     	 0x00	 
#define OS_THREAD_1  	     	 0x01		
#define OS_THREAD_2  	     	 0x02
#define OS_THREAD_3 	     	 0x03   
#define OS_THREAD_4 	     	 0x04	
#define OS_THREAD_5  	     	 0x05	//�ѿ���	 OS_THREAD_SYSTEM
#define OS_THREAD_6  	     	 0x06	
#define OS_THREAD_7  	     	 0x07	 
#define OS_THREAD_8  	     	 0x08	//�ѿ��� OS_THREAD_PRIMARY
#define OS_THREAD_9	     	 	 0x09
#define OS_THREAD_10  	     	 0x0A
#define OS_THREAD_11  	     	 0x0B
#define OS_THREAD_12  	     	 0x0C
#define OS_THREAD_13  	     	 0x0D
#define OS_THREAD_14  	     	 0x0E
#define OS_THREAD_15  	     	 0x0F


/* OS_MSG -------------------------------*/			
#define OS_BREAK 	     	     (0x01<<0)	  //�����ж����г�������� 	
 
/* OS_ERROR -----------------------------*/			
#define OS_ERROR_MALLOC	         (0x01<<0)	 //�ڴ��������	
 
/* ���� ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //ȱʡֵ
		
/* ͷ�ļ����� ----------------------------------------------------------------*/ 		
#include "User_Library.h"  
#include "OS_Manage.h" 
#include "OS_Run.h"
#include "OS_Tools.h"

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
/* ϵͳ��Ϣ --------------------------------*/ 
extern uint32_t OS_Msg;			
extern uint32_t OS_Error;
extern uint16_t OS_TimeOver_Cnt;
extern uint32_t os_fosc;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Init(void);  	  
 
#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





