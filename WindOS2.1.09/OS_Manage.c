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
Type_Addr AppHead = {0}; //���������ͷ    
 
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
unsigned char OSTask_Creat(  CreatFun *_AppAddr \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    ) 
						   
{  
	static Type_Addr *AppTemp = &AppHead;
		
	if( _thread   != OS_THREAD_FREE \
		&&_thread != OS_THREAD_PRIMARY \
	    &&_thread != OS_THREAD_SYSTEM  \
	   )return 1;
		
	Type_Addr *_p = NULL;
	 _p = (Type_Addr*)malloc(sizeof(Type_Addr)); //�����ڴ� 	
		
	if(_p == NULL) return 2;
	
	_p ->last = AppTemp;
	AppTemp ->next = _p;     			
	AppTemp = _p; 	 
	
	_p ->thread = _thread; 
	_p ->AppFun =_AppAddr;     
	_p ->next = NULL; //��β   	
	_p ->name = _Name;  
	_p ->reload = _T;  //��������ֵ     
	_p ->loading = _p ->reload; //��װ���в�  
	_p ->state = _state;    //����״̬   
	 
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
unsigned char OSTask_Remove(CreatFun *_AppAddr)    
{   
	Type_Addr *pTemp = &AppHead;    
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
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL) return 1;  			
	   		
	   if(pTemp ->next != NULL) pTemp = pTemp ->next;       	 
	    		 
		_cnt--; 		
	   if(_cnt == 0) return 2;  			
	}  			
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Alter()     
* @Description   : WinOS�����޸�
* @Data          : 2016/3/22		
* @Explain       : ���� ��_AppAddr = �����ַ    
*
*				   ����ֵ ��1,2,3 = �޸�����ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
unsigned char OSTask_Alter(  CreatFun *_AppAddr \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    )  
{   
	Type_Addr *pTemp = &AppHead;    
	unsigned int _cnt = OS_TASK_MAX;   
	
	while(1)
	{ 
	 
	   if(pTemp ->AppFun == _AppAddr) 
	   {	
		    if(_Name != OS_DEFAULT)	    pTemp ->name = _Name;
		    if(_T != OS_DEFAULT)  		pTemp ->reload = _T;
		    if(_state != OS_DEFAULT) 	pTemp ->state = _state;
		    if(_thread != OS_DEFAULT)	pTemp ->thread= _thread;
		   
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL) return 1;  			
	   		
	   if(pTemp ->next != NULL) pTemp = pTemp ->next;       	 
	    		 
		_cnt--; 		
	   if(_cnt == 0) return 2;  			
	}  			
}


 
/**----------------------------------------------------------------------------
* @FunctionName  : OSSystemShow()     
* @Description   : WinOSϵͳ��ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    	
*
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned int OSCPU_Show(void) 
{ 
	u16 Color = OS_Point_Read(OS_LCD_WHITH/2,FONT_1/2); 
	unsigned long int _CPU_Time = 0,_CPU_Cnt = 0,OS_CPU = 0;   
	OS_TextColor_Set(~Color);
	OS_BackColor_Set(Color);	
	 
	/* CPU ��� ------------------------------------*/  
	if(TIM_GetCounter(TIM2) > 0xfff0ffff) TIM_SetCounter(TIM2,0);
	_CPU_Time = TIM_GetCounter(TIM2); 
	_CPU_Cnt = 0;
	while( TIM_GetCounter(TIM2)<_CPU_Time + 100000 ) _CPU_Cnt++; //���100ms�����еļ����� 
	OS_CPU = (1.0f - ((double)_CPU_Cnt/884000.0f))*10000;   
	
	/* CPU ��ʾ ------------------------------------*/  
	OS_String_Show(0,0,(u8*)"CPU:",FONT_1); 
	OS_String_Show(FONT_1*5,0,(u8*)"%",FONT_1);  
	OS_Decim_Show(FONT_1*2,0,OS_CPU/100.0f,2,5,FONT_1);   
	//OSTask_Show();
	return 0; 
}  

unsigned int OSCPU_Show_Start(void)
{
	Taskbar_Draw(FONT_1);	 
	return 0;
}

unsigned int OSCPU_Show_End(void)
{
	Taskbar_Draw(FONT_1); 
	return 0;
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
	unsigned int Temp_Color;   
	unsigned char _line = 1;  
	Type_Addr *temp = &AppHead;   
	
	Temp_Color = OS_TextColor_Set(YELLOW);  
	
	/* ������ʾ ------------------------------------*/ 
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		
		if(temp ->thread == OS_THREAD_FREE) OS_TextColor_Set(OS_COLOR_FREE);   
		else if(temp ->thread == OS_THREAD_PRIMARY) OS_TextColor_Set(OS_COLOR_PRIMARY);
		else if(temp ->thread == OS_THREAD_SYSTEM) OS_TextColor_Set(OS_COLOR_SYSTEM); 
		else OS_TextColor_Set(OS_COLOR_OTHER); 
		
		OS_String_Show(120,FONT_1*_line++,temp ->name,FONT_1);   
	}
	
	OS_TextColor_Set(Temp_Color); 	
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




