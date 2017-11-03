/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_StartFile.h
* @Description : ϵͳ�����ļ�
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/                 
#ifndef __OS_STARTFILE_H
#define __OS_STARTFILE_H

#include "User_Stdafx.h"  
  
/* ʱ��Ƭ���� ----------------------------*/	
#define OS_TIME_SLICE 1000//1ms	 

/* WindOS�궨�� --------------------------------------------------------------*/		
/* ����״̬ -------------------------------*/			
typedef enum
{  
	OS_STATE_CLOSE_FINISH   =	0,   //�ر���� 	
	OS_STATE_ACTIVE   		,	//����  
	OS_STATE_CLOSE   		,   //�ر�  
	OS_STATE_ACTIVE_FINISH  ,   //�������   
	OS_STATE_CLOSE_SLEEP   	,   //˯��״̬	  
	OS_STATE_MAX   			,   //״̬���ֵ�������ж�Խ�� 
	
}Type_OS_State;   


/* �������̱߳��� ========================================*/	
/* �Զ����߳� ------------------------------*/	
typedef enum
{
	OS_THREAD_FREE = 0,//�����߳�		
	OS_THREAD_PRIMARY,//���߳�  			
	OS_THREAD_SYSTEM,//ϵͳ�߳�	  		
	//�ڴ˴���д�µ��߳��� 
	
	OS_THREAD_MAX//����߳���
}Type_OS_Thread;    


/* �̵߳����ȼ� ---------------------------*/
typedef enum
{
	OS_PRIOITY_FREE 	= 	0, 
	OS_PRIOITY_SYSTEM 	= 	5, 	
	OS_PRIOITY_PRIMARY 	= 	10,  
	//�ڴ˴���д���߳����ȼ�

}Type_OS_Prioity; 
/* End =================================================*/	

typedef void(CreatFun)(void); //App ������������� void XXX(void)   

typedef struct __AppList
{  		 
	CreatFun *AppMain;  //������ĵ�ַ   		
	CreatFun *AppSleep; //˯�߳���ĵ�ַ  	
	CreatFun *AppStart; //��ʼ������ĵ�ַ 	 	
	CreatFun *AppEnd;   //��������ĵ�ַ  
	
	volatile Type_OS_State state;//����״̬	
	Type_OS_Thread thread;//�߳� 	 
	
	char *name;    		
    uint32_t reload;//��������ֵ      
 	
	uint32_t loading;//���в�   
	uint32_t sleep;//˯��
	struct __AppList *next;   		
}Type_AppList; //�������		 



/* OS_MSG -------------------------------*/			
#define OS_BREAK 	     	     (0x01<<0)	  //�����ж����г�������� 	 
 
/* ���� ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //ȱʡֵ
		
/* ͷ�ļ����� ----------------------------------------------------------------*/ 		
#include "User_Library.h"  
#include "OS_Manage.h" 
#include "OS_Run.h"
#include "OS_Tools.h"
#include "OS_Hal.h"
//#include "OS_UI.h"
//#include "OS_UI_Hal.h"


/* ȫ�ֱ������� --------------------------------------------------------------*/ 
/* ϵͳ��Ϣ --------------------------------*/ 
extern uint32_t OS_Msg;			 
extern uint16_t OS_TimeOver_Cnt; 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Init(void);  	  
 
#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





