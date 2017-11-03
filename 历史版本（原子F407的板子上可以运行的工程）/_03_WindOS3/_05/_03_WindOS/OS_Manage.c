/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Manage.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/
/* App --------------------------------------------*/
Type_AppList AppHead = {NULL}; //���������ͷ    
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Creat()     
* @Description   : WinOS���񴴽� 
* @Data          : 2016/3/16
* @Explain       : ���� �� _AppAddr = �����ַ       _Name = �������� 
*				  		   _T = ��������    	_state = ����״̬  
*						   _thread = �߳�
*	
*				   ����ֵ ��-1 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
unsigned char OSTask_Creat(Type_AppList *_AppList) 				   
{  
	static Type_AppList *AppTemp = &AppHead;		
														
	AppTemp ->next = _AppList;     						
	AppTemp = _AppList; 	 
	AppTemp ->next = NULL; //��β   		
	
#if USE_OS_DESKTOP == 1	//ʹ��ϵͳ����															
	if(_AppList ->ico_used == USE_OS_DESKTOP)												
	OS_IcoCreat(_AppList,OS_ICO_COLOUR_TEXT,OS_ICO_COLOUR_BACK);	 							
#endif															
								
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS����ɾ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    
*
*				   ����ֵ ��1,2,3 = ɾ������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
unsigned char OSTask_Remove(Type_AppList *_AppList)    
{   
	Type_AppList *pPre = NULL; //��һ���ڵ�    
	Type_AppList *pList = &AppHead; 
	unsigned int _cnt = OS_TASK_MAX; //����������ڲ�ѯ
	unsigned char _exist = 0;	
	
	/* �ж������Ƿ���� ----------------------------*/
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	
		
		pPre = 	pList; //��¼��һ���ڵ�
		if(pList->next != NULL) pList = pList->next;		
		else break;  
		
		_cnt--; 				
		if(_cnt == 0) return 2;  		
		
	}
	if(_exist == 0) return 1;  
	
	/* ɾ������ -----------------------------------*/
	pPre ->next = pList ->next;
	pList ->AppMain = NULL;   
	pList ->AppBack = NULL;   
	pList ->AppStart = NULL;   
	pList ->AppEnd = NULL;   
	    
	free(pList); 		
	pList =NULL;  		 
	   	  
	return 0;		
}  			


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Alter()     
* @Description   : WinOS�����޸�
* @Data          : 2016/3/22		
* @Explain       : ���� ��_AppAddr = �����ַ    
*
*				   ����ֵ ��1,2,3 = �޸�����ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned char OSTask_Alter(  Type_AppList *_AppList \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    )  
{     
	Type_AppList *pList = &AppHead;    	
	unsigned int _cnt = OS_TASK_MAX;   			
	unsigned char _exist = 0;				
																
	/* �ж������Ƿ���� ----------------------------*/				
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	 
		if(pList->next != NULL) pList = pList->next;		
		else break;   									
	}		 
	if(_exist == 0) return 1;	
				
	/* �޸����� -----------------------------------*/		
	if(_Name != OS_DEFAULT)	_AppList ->name = _Name;		
	if(_T != OS_DEFAULT)  	_AppList ->reload = _T;		
	if(_state != OS_DEFAULT) 	_AppList ->state = _state;		
	if(_thread != OS_DEFAULT)	_AppList ->thread= _thread;		
																
	_cnt--; 															
    if(_cnt == 0) return 2;  	
	
	return 0;				
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSRunning_Break()     
* @Description   : WinOS�������
* @Data          : 2016/3/23	
* @Explain       : None 	
------------------------------------------------------------------------------*/
unsigned int OSRunning_Break(void) 
{
	OS_Msg |=  OS_BREAK; 
	return 0;
}
												
											
/**----------------------------------------------------------------------------
* @FunctionName  : OSRunning_GoOn()     
* @Description   : WinOS��������
* @Data          : 2016/3/23		
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int OSRunning_Continue(void) 
{
	
	OS_Msg &=  ~OS_BREAK; 
	return 0; 
}

 

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





