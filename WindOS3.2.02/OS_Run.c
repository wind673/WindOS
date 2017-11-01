/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : ϵͳ����
* @Date        : 2017/10/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
-------------------------------------------------------------------------------
�汾�ţ�		WindOS3.2.01
�޶���¼��	
 @Date		@Version			@Revise					@Author
2017/10/16 	WindOS3.2.01		��������ʱ��				Wind��л���죩
2017/10/16 	WindOS3.2.02		�޸�Free				Wind��л���죩

����޶���
�޸�Free��ֻ����һ��App��BUG�� 
*=============================================================================*/     

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Run.h"
#include "OS_StartFile.h"
#include "OS_Manage.h"
#include "OS_Tools.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
											
/* ˽�У���̬���������� ------------------------------------------------------*/
										
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/	
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_Free()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : �����߳�
------------------------------------------------------------------------------*/
inline void OSThread_Free(void)
{ 
	static u32 time_us = 0;
 	Type_AppList *AppRun = &AppHead;    
	
	if(!OStimer_usTimeOver_Is(time_us,1000)) return;
	time_us = OStimer_us_Get(); //����ʱ��
	
	if(OS_Msg & OS_BREAK) return;   
	
	while(1)
	{   
		
		if(AppRun ->next == NULL) return;  
		
		AppRun = AppRun ->next;   	 
		if(AppRun ->thread != OS_THREAD_FREE) continue; 
		if(AppRun ->loading != 0 )  AppRun ->loading --;
		if(AppRun ->loading == 0 ) 
		{ 
		 
			if(AppRun ->state == OS_STATE_SUSPEND) //����
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd();  
				AppRun ->state = OS_STATE_SUSPEND_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_SUSPEND_FINISH)//�����Ѿ�����ĺ�̨����
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//���к�̨����
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE) //����   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //������������  
				AppRun ->state = OS_STATE_ACTIVE_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}					
			else if(AppRun ->state == OS_STATE_ONE_OFF) //һ���Եĳ���  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //����һ��������  
				AppRun ->state = OS_STATE_CLOSE_FINISH;  
				AppRun ->loading = AppRun ->reload;	 
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//���н�������
				AppRun ->state = OS_STATE_CLOSE_FINISH;
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_ACTIVE_FINISH)//�����Ѿ������������
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 
				AppRun ->loading = AppRun ->reload;	
			}	
			 
		}  
		
	} 
}

 
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_5()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : �߳�5
------------------------------------------------------------------------------*/
inline void OSThread_5(void)
{
	Type_AppList *AppRun = &AppHead;   
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_5) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;   
		if(AppRun ->loading == 0 )  
		{  	
			if(AppRun ->state == OS_STATE_ACTIVE_FINISH)//�����Ѿ������������		
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 	
				AppRun ->loading = AppRun ->reload;					
			} 
			else if(AppRun ->state == OS_STATE_SUSPEND_FINISH)//�����Ѿ�����ĺ�̨����
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//���к�̨����
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_SUSPEND) //����
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ACTIVE) //����   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //������������  
				AppRun ->state = OS_STATE_ACTIVE_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}		 
			else if(AppRun ->state == OS_STATE_ONE_OFF) //һ���Եĳ���  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //����һ�����������   	
				AppRun ->state = OS_STATE_ONE_OFF_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ONE_OFF_FINISH) //һ���Եĳ���  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //����һ�����������   	
				AppRun ->state = OS_STATE_CLOSE_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)	
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//���н�������	
				AppRun ->state = OS_STATE_CLOSE_FINISH;	
				AppRun ->loading = AppRun ->reload;	
			}	 
			 							
		}
			   
	} 
	
}








/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_8()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : �߳�8
------------------------------------------------------------------------------*/
inline void OSThread_8(void)
{   
	Type_AppList *AppRun = &AppHead;   
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_8) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;   
		if(AppRun ->loading == 0 )  
		{  	
			if(AppRun ->state == OS_STATE_ACTIVE_FINISH)//�����Ѿ������������		
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 	
				AppRun ->loading = AppRun ->reload;					
			} 
			else if(AppRun ->state == OS_STATE_SUSPEND_FINISH)//�����Ѿ�����ĺ�̨����
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//���к�̨����
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_SUSPEND) //����
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ACTIVE) //����   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //������������  
				AppRun ->state = OS_STATE_ACTIVE_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}		 
			else if(AppRun ->state == OS_STATE_ONE_OFF) //һ���Եĳ���  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //����һ�����������   	
				AppRun ->state = OS_STATE_ONE_OFF_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ONE_OFF_FINISH) //һ���Եĳ���  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //����һ�����������   	
				AppRun ->state = OS_STATE_CLOSE_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)	
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//���н�������	
				AppRun ->state = OS_STATE_CLOSE_FINISH;	
				AppRun ->loading = AppRun ->reload;	
			}	 
			 							
		}
			   
	} 
	
} 






/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/






