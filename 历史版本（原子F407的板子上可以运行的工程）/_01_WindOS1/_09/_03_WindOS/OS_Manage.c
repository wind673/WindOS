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
signed char OSTask_Creat(  CreatFun *_AppAddr \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    )
						   
{  
	if( _thread   != OS_THREAD_FREE \
		&&_thread != OS_THREAD_PRIMARY \
	    &&_thread != OS_THREAD_SYSTEM  \
	   )return -1;
		
	
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //�����ڴ� 		
	if(_p == NULL) return -2;
	
	if(_thread == OS_THREAD_PRIMARY) //���߳�
	{
		PrimaryTemp ->next = _p;    
		_p ->last = PrimaryTemp; 			
		PrimaryTemp = _p; 		 
	}
	else if(_thread == OS_THREAD_FREE)  //���У���̨���߳�
	{ 
		FreeTemp ->next = _p;    
		_p ->last = FreeTemp; 			
		FreeTemp = _p; 	 
	} 
	else if(_thread == OS_THREAD_SYSTEM)   //ϵͳ�߳� 
	{
		SystemTemp ->next = _p;    
		_p ->last = SystemTemp; 			
		SystemTemp = _p; 		 
	}
	
	_p ->AppFun = _AppAddr;     
	_p ->next = NULL; //ѭ������   	
	_p ->name = _Name;  
	_p ->reload = _T;  //��������ֵ     
	_p ->loading = _p ->reload; //��װ���в�  
	_p ->state = _state;    //����״̬   
	
	  
	OS_RAM = (unsigned long int)_p; //��¼OSʹ�õ��ڴ�����    	 
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS����ɾ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    
*
*				   ����ֵ ��-1,-2,-3 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
signed char OSTask_Remove(CreatFun *_AppAddr)    
{   
	Type_Addr *pTemp = &FreeHead;  
	unsigned char thread_cnt = 0;   
	unsigned int _cnt = OS_TASK_MAX;   
	
	while(1)
	{ 
	 
	   if(pTemp ->AppFun == _AppAddr) 
	   {	
		    (pTemp ->last) ->next = pTemp ->next;	
		    (pTemp ->next) ->last = pTemp ->last;	
		    pTemp ->AppFun = NULL;   	
		    free(pTemp); 		
		    pTemp =NULL;  		
		    OS_RAM = (unsigned long int)pTemp; //��¼OSʹ�õ��ڴ�����	 	
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL)		
	   {		
		     if(thread_cnt == 0) pTemp = &PrimaryHead; 
		     if(thread_cnt == 1) pTemp = &FreeHead; 
		     if(thread_cnt == 2) pTemp = &SystemHead; 
		     if(thread_cnt >= 3) return -1;   
			 thread_cnt++;  	
	   }			
	   		
	   if(pTemp ->next != NULL) pTemp = pTemp ->next;       	 
	    		 
		_cnt--; 			
	   if(_cnt == 0) return -2;  			
	}  			
}









/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





