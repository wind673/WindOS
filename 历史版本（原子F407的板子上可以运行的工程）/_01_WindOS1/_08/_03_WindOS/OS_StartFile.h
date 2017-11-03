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
/* WindOSϵͳ����ͷ�ļ� ---------------------*/
#include "OS_Run.h"
#include "OS_UI.h"
#include "OS_Manage.h"

/* ƽ̨���� --------------------------------*/  
#include "my_sys.h" 
#include "my_TFT.h"  
#include "My_GPIO.h"
#include "My_Interrupt.h"
#include "My_Timer.h"


/* Ӧ�ó��� --------------------------------*/  
#include "Hello.h"  
#include "LED.h" 



/* User�궨�� ---------------------------------------------------------------*/
/* ʱ��Ƭ���� ----------------------------*/
#define OS_TIME_SLICE 1000//1ms

/* ������ ------------------------------*/
#define OS_FOSC 168000000   //168M

/* ��ʾ������ ----------------------------*/
#define OS_LCD_WHITH  	240	 //���
#define OS_LCD_LENTH  	400	 //�߶�

/* ��������� ----------------------------*/
#define OS_TASK_MAX  10000

/* RAM��ַ ----------------------------*/
#define OS_RAM_START 0x20000000  
#define OS_RAM_SIZE  0x20000

/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/  


/* WindOS�궨�� --------------------------------------------------------------*/
/* _state -------------------------------*/
#define OS_STATE_CLOSE   		 0    //�ر�
#define OS_STATE_ACTIVE   		 1	  //����
#define OS_STATE_BACKSTAGE  	 2	  //��̨����
#define OS_STATE_ONE_OFF  	     3	  //ֻ����һ��
#define OS_STATE_SUSPEND  	     4	  //��ͣһ��

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


#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





