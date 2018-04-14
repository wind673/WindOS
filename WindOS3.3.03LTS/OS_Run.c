/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : ϵͳ����
* @Date        : 2017/10/16
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
------------------------------------------------------------------------------- 
�޶���¼��	
 @Date		@Version			@Revise					@Author
2017/10/16 	V1.1.1				��������ʱ��				Wind��л���죩
2017/10/16 	V1.1.2				�޸�Free				Wind��л���죩
2017/11/03 	V1.1.3				����˯�߹���				Wind��л���죩

����޶���
1.����˯�߹��ܡ� 
*=============================================================================*/     

/* ��Ҫͷ�ļ� ----------------------------------------------------------------*/
#include "OS_Run.h"
#include "OS_StartFile.h"
#include "OS_Manage.h"
#include "OS_Tools.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/
										
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/	
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_Handle()     
* @Description   : �߳��л�����  
* @Data          : 2017/11/03
* @Explain       : ���ö�Ӧ���ж���
------------------------------------------------------------------------------*/
void OSThread_Handle(TypeEnum_OS_Thread Thread)
{  
 	TypeStruct_AppList *AppRun = &AppHead[Thread];  
	
	if(Thread == OS_THREAD_FREE)
	{
		static u32 time_us = 0;
		if(!OStimer_usTimeOver_Is(time_us,1000)) return;
		time_us = OStimer_us_Get(); //����ʱ��	 
	} 
	
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != Thread)  //ת�ƷǱ��̵߳�App
		{
			OSTask_Remove(AppRun);	
			OSTask_Creat(AppRun);
			continue; 
		}
		
		if(AppRun ->sleep > 0 )  AppRun ->sleep --;	
		if(AppRun ->loading > 0 )  AppRun ->loading --;	
		if(AppRun ->loading == 0 ) 	
		{  	
			AppRun ->loading = AppRun ->reload;	
			switch((uint8_t)(AppRun ->state))
			{
				case OS_STATE_ACTIVE_FINISH://����״̬	
					if(AppRun ->AppMain != NULL) AppRun ->AppMain();
					break;
				
				case OS_STATE_CLOSE_FINISH:	//�ر�״̬		 	
					break;
				
				case OS_STATE_ACTIVE://���뼤��״̬			
					if(AppRun ->AppStart != NULL) AppRun ->AppStart(); 
					AppRun ->state = OS_STATE_ACTIVE_FINISH; 	 
					break;//������������  	 
				
				case OS_STATE_CLOSE:	//����ر�״̬
					if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//���н�������
					AppRun ->state = OS_STATE_CLOSE_FINISH; 			
					break;
				
				case OS_STATE_CLOSE_SLEEP:	//˯��״̬
					if(AppRun ->sleep == 0)
					{	 
						if(AppRun ->AppMain != NULL) AppRun ->AppMain();
						AppRun ->state = OS_STATE_ACTIVE_FINISH; //����	 
					}	
					else	
					{	
						if(AppRun ->AppSleep != NULL)  AppRun ->AppSleep(); 
					} 	
					break; 
				
				default: //���ֲ����ڵ�״̬
					AppRun ->state = OS_STATE_CLOSE_FINISH; 	
					break;
			} 
			
			
		}  
			   
	} 
	
}



 




/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





