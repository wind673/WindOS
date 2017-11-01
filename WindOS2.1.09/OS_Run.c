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
 	Type_Addr *AppRun = &AppHead; 
	unsigned int BackColor,TestColor; 
	 
	while(1)
	{   
		if(OS_Msg & OS_BREAK) continue;
		if(AppRun ->next == NULL) AppRun = &AppHead;  
		else 
		{
			AppRun = AppRun ->next;  
			if(AppRun ->thread != OS_THREAD_FREE) continue; 	
			if(AppRun ->loading != 0 )  AppRun ->loading --;	
			if(AppRun ->loading == 0 ) 
			{ 
				TestColor = OS_TextColor_Set(BLACK);//��¼��������ɫ 
				BackColor = OS_BackColor_Set(WHITE);	
				if(AppRun ->state == OS_STATE_ACTIVE) //�ж� �Ƿ񼤻�   
				{ 
					AppRun ->AppFun(); //���г���  
					AppRun ->loading = AppRun ->reload;		
				}
				else if(AppRun ->state == OS_STATE_ONE_OFF) //�ж� һ���Եĳ���  
				{ 
					AppRun ->AppFun(); //���г���   	
					OSTask_Remove(AppRun ->AppFun);   
				} 
				 OS_TextColor_Set(TestColor);//��ԭԭ������ɫ	
				 OS_BackColor_Set(BackColor);	
			} 
			 
		} 
		  
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
	Type_Addr *AppRun = &AppHead;  
	unsigned int BackColor,TestColor; 
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_PRIMARY) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;   
		
		if(AppRun ->loading == 0) 
		{
			TestColor = OS_TextColor_Set(BLACK);//��¼��������ɫ 
			BackColor = OS_BackColor_Set(WHITE);
			
			if(AppRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				AppRun ->AppFun(); //���г���    
				AppRun ->loading = AppRun->reload;
			}   
			else if(AppRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���				
			{
				AppRun ->AppFun(); //���г��� 
				OSTask_Remove(AppRun ->AppFun);   
					 
			}  
			 OS_TextColor_Set(TestColor); //��ԭԭ������ɫ
			 OS_BackColor_Set(BackColor);									
		}
			   
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
	Type_Addr *AppRun = &AppHead;  
	unsigned int BackColor,TestColor;  
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_SYSTEM) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;    
		
		if(AppRun ->loading == 0) 
		{
			TestColor = OS_TextColor_Set(BLACK);//��¼��������ɫ 
			BackColor = OS_BackColor_Set(WHITE);
			
			if(AppRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				AppRun ->AppFun(); //���г���    
				AppRun ->loading = AppRun->reload;
			}   
			else if(AppRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���				
			{
				AppRun ->AppFun(); //���г��� 
				OSTask_Remove(AppRun ->AppFun);   
					 
			}  
			OS_TextColor_Set(TestColor); //��ԭԭ������ɫ
			OS_BackColor_Set(BackColor);					
		}
			   
	} 
	
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/




