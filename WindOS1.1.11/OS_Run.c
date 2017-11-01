/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_StartFile.h"
																		
/* 私有宏定义 ----------------------------------------------------------------*/
											
/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/	
			
/**----------------------------------------------------------------------------
* @FunctionName  : OSFree_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : 空闲线程
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
				if(FreeRun ->state == OS_STATE_ACTIVE) //判断是否激活   
				{ 
					FreeRun ->AppFun(); //运行程序  
					FreeRun ->loading = FreeRun ->reload;		
				}
				else if(FreeRun ->state == OS_STATE_ONE_OFF) //判断是一次性的程序  
				{ 
					FreeRun ->AppFun(); //运行程序   
					OSTask_Remove(FreeRun ->AppFun);   
				}
				else if(FreeRun ->state == OS_STATE_SUSPEND)  
				{	
					FreeRun ->state = OS_STATE_ACTIVE; //重新激活
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
* @Explain       : 主线程
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
			if(PrimaryRun ->state == OS_STATE_ACTIVE) //判断是否激活
			{ 
				PrimaryRun ->AppFun(); //运行程序    
				PrimaryRun ->loading = PrimaryRun->reload;
			}   
			else if(PrimaryRun ->state == OS_STATE_ONE_OFF) //判断是一次性的程序
			{
				PrimaryRun ->AppFun(); //运行程序 
				OSTask_Remove(PrimaryRun ->AppFun);   
				 
			}  
			else if(PrimaryRun ->state == OS_STATE_SUSPEND) //判断是一次性的程序
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
* @Explain       : 系统线程
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
			if(SystemRun ->state == OS_STATE_ACTIVE) //判断是否激活
			{ 
				SystemRun ->AppFun(); //运行程序    
				SystemRun ->loading = SystemRun->reload;
			}   
			else if(SystemRun ->state == OS_STATE_ONE_OFF) //判断是一次性的程序
			{
				SystemRun ->AppFun(); //运行程序 
				OSTask_Remove(SystemRun ->AppFun);   
				 
			}  
			else if(SystemRun ->state == OS_STATE_SUSPEND) //判断是一次性的程序
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




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





