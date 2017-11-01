/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : ϵͳ����
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/     

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __OS_MANAGE_H  
#define __OS_MANAGE_H   
								
/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 


/* ȫ�ֺ궨�� ----------------------------------------------------------------*/

/* �ṹ������ ----------------------------------------------------------------*/ 
 
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
/* App --------------------------------------------*/
extern Type_AppList AppHead; //������г������е�ͷ֡    
 
/* ȫ�ֺ������� --------------------------------------------------------------*/    
unsigned char OSTask_Creat(Type_AppList *_AppList);
unsigned char OSTask_Remove(Type_AppList *_AppList);  
unsigned char OSTask_State(Type_AppList *_AppList,unsigned char _State);
unsigned char OSTask_Close(Type_AppList *_AppList);  
unsigned char OSTask_Active(Type_AppList *_AppList);  
unsigned char OSTask_Alter(  Type_AppList *_AppList \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    ); 
						   
unsigned int OSRunning_Break(void);
unsigned int OSRunning_Continue(void); 
  				
#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



