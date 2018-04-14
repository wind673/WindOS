/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : 系统运行
* @Date        : 2017/10/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
------------------------------------------------------------------------------- 
修订记录：	
 @Date		@Version			@Revise					@Author
2017/10/16 	V1.1.1				修正运行时间				Wind（谢玉伸）
2017/10/16 	V1.1.2				修复Free				Wind（谢玉伸）
2017/11/03 	V1.1.3				增加睡眠功能				Wind（谢玉伸）

最后修订：
1.增加睡眠功能。 
*=============================================================================*/     

/* 需要头文件 ----------------------------------------------------------------*/
#include "OS_Run.h"
#include "OS_StartFile.h"
#include "OS_Manage.h"
#include "OS_Tools.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/	
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_Handle()     
* @Description   : 线程切换函数  
* @Data          : 2017/11/03
* @Explain       : 放置对应的中断中
------------------------------------------------------------------------------*/
void OSThread_Handle(TypeEnum_OS_Thread Thread)
{  
 	TypeStruct_AppList *AppRun = &AppHead[Thread];  
	
	if(Thread == OS_THREAD_FREE)
	{
		static u32 time_us = 0;
		if(!OStimer_usTimeOver_Is(time_us,1000)) return;
		time_us = OStimer_us_Get(); //更新时间	 
	} 
	
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != Thread)  //转移非本线程的App
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
				case OS_STATE_ACTIVE_FINISH://激活状态	
					if(AppRun ->AppMain != NULL) AppRun ->AppMain();
					break;
				
				case OS_STATE_CLOSE_FINISH:	//关闭状态		 	
					break;
				
				case OS_STATE_ACTIVE://进入激活状态			
					if(AppRun ->AppStart != NULL) AppRun ->AppStart(); 
					AppRun ->state = OS_STATE_ACTIVE_FINISH; 	 
					break;//运行启动程序  	 
				
				case OS_STATE_CLOSE:	//进入关闭状态
					if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序
					AppRun ->state = OS_STATE_CLOSE_FINISH; 			
					break;
				
				case OS_STATE_CLOSE_SLEEP:	//睡眠状态
					if(AppRun ->sleep == 0)
					{	 
						if(AppRun ->AppMain != NULL) AppRun ->AppMain();
						AppRun ->state = OS_STATE_ACTIVE_FINISH; //唤醒	 
					}	
					else	
					{	
						if(AppRun ->AppSleep != NULL)  AppRun ->AppSleep(); 
					} 	
					break; 
				
				default: //出现不存在的状态
					AppRun ->state = OS_STATE_CLOSE_FINISH; 	
					break;
			} 
			
			
		}  
			   
	} 
	
}



 




/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





