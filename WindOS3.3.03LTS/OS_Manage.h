/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : ϵͳ����
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
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
extern TypeStruct_AppList AppHead[OS_THREAD_MAX];  
 
/* ȫ�ֺ������� --------------------------------------------------------------*/    
uint8_t OSTask_Creat(TypeStruct_AppList *_AppList);
uint8_t OSTask_Remove(TypeStruct_AppList *_AppList);  
uint8_t OSTask_State(TypeStruct_AppList *_AppList,TypeEnum_OS_State _State);
uint8_t OSTask_Close(TypeStruct_AppList *_AppList);  
uint8_t OSTask_Active(TypeStruct_AppList *_AppList);   
uint8_t OSTask_Sleep(TypeStruct_AppList *_AppList,uint32_t Sleep);

uint8_t OSRunning_Break(void);
uint8_t OSRunning_Continue(void); 
  				
#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



