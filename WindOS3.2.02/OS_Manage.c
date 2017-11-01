/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.c
* @Description : ϵͳ����
* @Date        : 2017/10/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     :  
-------------------------------------------------------------------------------
�汾�ţ�		WindOS3.2.01
�޶���¼��	
 @Date		@Version			@Revise					@Author
2017/10/16	WindOS3.2.01		�����ú���				Wind��л���죩

����޶���
��������OSTask_Active��OSTask_Close���������ú�����

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
* @Explain       : 
-------------------------------------------------------------------------------
���� �� _AppList = �����ַ    
����ֵ �� 1 = �����ظ�����������ʧ��		 0 = �ɹ�
------------------------------------------------------------------------------*/	
unsigned char OSTask_Creat(Type_AppList *_AppList) 				   
{  
	Type_AppList *Temp = &AppHead;		 
	while(Temp ->next != NULL)
	{
		Temp = Temp ->next;	
		if(Temp == _AppList) return 1; 	
	}	
	 
	Temp ->next = _AppList;       	 
	_AppList ->next = NULL; //��β   		
		 				
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS����ɾ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    
*
*				   ����ֵ ��1 = ɾ������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
unsigned char OSTask_Remove(Type_AppList *_AppList)    
{   
	Type_AppList *Temp = &AppHead;	 
	while(Temp ->next != NULL)	
	{
		Temp = Temp ->next;	 
		if(Temp ->next == _AppList) break; //�ҵ� pStruct ��һ����ť�ĵ�ַ
	} 	 
	Temp ->next = _AppList ->next;  	
	free(_AppList);   	 
	_AppList = NULL;
	
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
* @FunctionName  : OSTask_State()     
* @Description   : WinOS����״̬�޸�
* @Data          : 2016/3/22		
* @Explain       : 
-------------------------------------------------------------------------------
_AppAddr = �����ַ    
_State	 = ����״̬	
	OS_STATE_SUSPEND   		 	1    //���𣨺�̨��
	OS_STATE_ACTIVE   		 	2	  //���� 
	OS_STATE_ONE_OFF  	     	3	  //ֻ����һ�� 
	OS_STATE_CLOSE   			4    //�ر�  
	OS_STATE_ACTIVE_FINISH   	5    //�������  
	OS_STATE_CLOSE_FINISH   	6    //�ر���� 	
	OS_STATE_SUSPEND_FINISH   	7    //���𣨺�̨��	

����ֵ ��1,2,3 = �޸�����ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned char OSTask_State(Type_AppList *_AppList,unsigned char _State)  
{     
	Type_AppList *pList = &AppHead;       			
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
	_AppList ->state= _State;		
			 
	return 0;				
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_State()     
* @Description   : WinOS����״̬�޸�
* @Data          : 2016/3/22		
* @Explain       : 
-------------------------------------------------------------------------------
_AppAddr = �����ַ     
����ֵ ��1,2,3 = �޸�����ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned char OSTask_Close(Type_AppList *_AppList)  
{     
	Type_AppList *pList = &AppHead;       			
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
	_AppList ->state = OS_STATE_CLOSE;		
			 
	return 0;				
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_State()     
* @Description   : WinOS����״̬�޸�
* @Data          : 2016/3/22		
* @Explain       : 
-------------------------------------------------------------------------------
_AppAddr = �����ַ     
����ֵ ��1,2,3 = �޸�����ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned char OSTask_Active(Type_AppList *_AppList)  
{     
	Type_AppList *pList = &AppHead;       			
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
	_AppList ->state = OS_STATE_ACTIVE;		
			 
	return 0;				
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSRunning_Break()     	
* @Description   : WinOS�������	
* @Data          : 2016/3/23		
* @Explain       : None 		
------------------------------------------------------------------------------*/
inline unsigned int OSRunning_Break(void) 
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
inline unsigned int OSRunning_Continue(void) 
{ 
	OS_Msg &=  ~OS_BREAK; 
	return 0; 
}

 

/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





