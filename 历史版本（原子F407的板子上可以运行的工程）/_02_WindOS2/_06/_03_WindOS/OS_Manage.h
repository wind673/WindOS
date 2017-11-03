/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
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
extern Type_Addr AppHead; //������г������е�ͷ֡    
 
/* ȫ�ֺ������� --------------------------------------------------------------*/   
unsigned char OSTask_Remove(CreatFun *_AppAddr);            
unsigned int OSCPU_Show(void);
unsigned int OSTask_Show(void);
unsigned char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T,unsigned char _state,unsigned char _thread);  
unsigned char OSTask_Alter(  CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T ,unsigned char _state ,unsigned char _thread) ;

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



