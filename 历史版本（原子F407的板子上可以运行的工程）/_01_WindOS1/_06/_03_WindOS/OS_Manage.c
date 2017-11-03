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
#include "OS_StartFile.h" 

 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/
unsigned long int OS_RAM = 0; //RAM����
Type_Addr FreeHead = {0}; //������г������е�ͷ֡   
Type_Addr PrimaryHead = {0}; //�������������е�ͷ֡ 

Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  



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
signed char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T,unsigned char _state,unsigned char _thread)
{   
	if(_thread == OS_FREE)  
	{
		Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //�����ڴ� 		
		if(_p == NULL) return -1;
		
		FreeTemp ->next = _p;    
		_p ->last = FreeTemp; 			
		FreeTemp = _p; 		
		_p ->AppFun = _AppAddr;     
		_p ->next = NULL; //ѭ������   	
		_p ->name = _Name;  
		_p ->reload = _T;  //��������ֵ     
		_p ->loading = _p ->reload; //��װ���в�  
		_p ->state = _state;    //����״̬    
	}
	else if(_thread == THREAD_PRIMARY)   
	{
		Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //�����ڴ� 		
		if(_p == NULL) return -1;		
		
		PrimaryTemp ->next = _p;    
		_p ->last = PrimaryTemp; 			
		PrimaryTemp = _p; 		
		_p ->AppFun = _AppAddr;     
		_p ->next = NULL; //ѭ������   
		_p ->name = _Name;  
		_p ->reload = _T;  //��������ֵ 
		_p ->loading = _p ->reload; //��װ���в�		
		_p ->state = _state;    //����״̬  
	 
	}
	  
	OS_RAM += sizeof(Type_Addr); //��¼OSʹ�õ��ڴ�����    	 
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
	Type_Addr *pTemp = NULL;  	
	pTemp = &FreeHead;    
	unsigned char thread_cnt = 0;   
	unsigned int _cnt = TASK_MAX;   
	
	while(1)
	{ 
	   if(pTemp ->AppFun == _AppAddr) 
	   {	
		    (pTemp ->last) ->next = pTemp ->next;	
		    (pTemp ->next) ->last = pTemp ->last;	
		    pTemp ->AppFun = NULL;   	
		    free(pTemp); 		
		    pTemp =NULL;  		
		    OS_RAM -= sizeof(Type_Addr); //��¼OSʹ�õ��ڴ�����	 	
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL)		
	   {		
		     if(thread_cnt == 0) pTemp = &PrimaryHead; 
		     if(thread_cnt >= 9) return -1;  
			 thread_cnt++;  	
	   }			
	   else			
	   {			
			pTemp = pTemp ->next;       	 
	   }			
	   
		_cnt--; 			
	   if(_cnt == 0) return -2;  			
	} 
	 			
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Show()     
* @Description   : WinOS������ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    	
*
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned int OSTask_Show(void) 
{
	unsigned int Temp_color;
	Temp_color = TextColor_Set(YELLOW);
	LCD_ShowNum(170,0,OS_RAM,10,FONT_1); 	
	Show_String(170,FONT_1*1,FreeTemp ->name,FONT_1); 		
	TextColor_Set(Temp_color);
	return 0;
}






/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





