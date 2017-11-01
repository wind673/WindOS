/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_StartFile.h"
																		
/* ˽�к궨�� ----------------------------------------------------------------*/
											
/* ˽�У���̬���������� ------------------------------------------------------*/
										
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/	
			
/**----------------------------------------------------------------------------
* @FunctionName  : OSFree_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : �����߳�
------------------------------------------------------------------------------*/
void OSThread_Free(void)
{ 
 	  int flag;
	while(1)
	{  
	    if(FreeRun ->next != NULL)
	    if((FreeRun ->next) ->loading != 0 ) OSCPU_Monitor();
		
		if(FreeRun ->next == NULL) FreeRun = &FreeHead;
		else 
		{
			FreeRun = FreeRun ->next;  
			flag = 0;
			if(FreeRun ->loading != 0 )  FreeRun ->loading --;
			if(FreeRun ->loading == 0 ) 
			{
				flag = 0;
				if(FreeRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�   
				{ 
					FreeRun ->AppFun(); //���г���  
					FreeRun ->loading = FreeRun ->reload;		
				}
				else if(FreeRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���  
				{ 
					FreeRun ->AppFun(); //���г���   
					OSTask_Remove(FreeRun ->AppFun);   
				}
				else if(FreeRun ->state == OS_STATE_SUSPEND)  
				{	
					FreeRun ->state = OS_STATE_ACTIVE; //���¼���
					FreeRun ->loading = FreeRun ->reload;		 
				}  
			
			} 
			
		   flag = 0;
		}
		flag = 0;
		  
	} 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSPrimary_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : ���߳�
------------------------------------------------------------------------------*/
void OSThread_Primary(void)
{
	Type_Addr *temp = &PrimaryHead; 
	PrimaryHead.next;
	if(PrimaryRun ->next == NULL)PrimaryRun = &PrimaryHead;
	else
	{
		
		PrimaryRun = PrimaryRun ->next;  
		if(PrimaryRun ->loading == 0) 
	    {
			if(PrimaryRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				PrimaryRun ->AppFun(); //���г���    
				PrimaryRun ->loading = PrimaryRun->reload;
			}   
			else if(PrimaryRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���
			{
				PrimaryRun ->AppFun(); //���г��� 
				OSTask_Remove(PrimaryRun ->AppFun);   
				 
			}  
			else if(PrimaryRun ->state == OS_STATE_SUSPEND) //�ж���һ���Եĳ���
			{
				PrimaryRun ->state = OS_STATE_ACTIVE; 	   
			}
			 
		}
		 
	} 
	
		 
	
	while(1)
	{
		if(temp ->next == NULL) return;
		temp = temp ->next;
		if(temp ->loading != 0) temp ->loading --;   
		  
	}
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSPrimary_Thread()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : ϵͳ�߳�
------------------------------------------------------------------------------*/
void OSThread_System(void)
{
	Type_Addr *temp = &SystemHead;
	if(SystemRun ->next == NULL)SystemRun = &SystemHead;
	else
	{
		
		SystemRun = SystemRun ->next;  
		if(SystemRun ->loading == 0) 
	    {
			if(SystemRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				SystemRun ->AppFun(); //���г���    
				SystemRun ->loading = SystemRun->reload;
			}   
			else if(SystemRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���
			{
				SystemRun ->AppFun(); //���г��� 
				OSTask_Remove(SystemRun ->AppFun);   
				 
			}  
			else if(SystemRun ->state == OS_STATE_SUSPEND) //�ж���һ���Եĳ���
			{
				SystemRun ->state = OS_STATE_ACTIVE; 	   
			}
			                
		}
		 
	} 
	
	while(1)
	{
		if(temp ->next == NULL) return;
		temp = temp ->next;
		if(temp ->loading != 0) temp ->loading --;   
		  
	}
	
	
	
	
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





