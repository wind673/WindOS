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
#include "OS_Run.h"
#include "OS_StartFile.h" 
																		
/* 私有宏定义 ----------------------------------------------------------------*/
											
/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/
extern Type_Addr AppHead;
Type_Addr *pAppRun = &AppHead;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Run()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Run(void)
{
	while(1)
	{
		if(pAppRun ->next == NULL) pAppRun = &AppHead;
		else 
		{
			pAppRun = pAppRun ->next;  
			if(pAppRun ->loading == 0) 
			{
				if(pAppRun ->state == STATE_ACTIVE) //判断是否激活
				{
					pAppRun ->loading = pAppRun ->reload; //重载
					pAppRun ->AppFun(); //运行程序 
				}
				else if(pAppRun ->state == STATE_ONE_OFF) //判断是一次性的程序
				{
					pAppRun ->AppFun(); //运行程序 
					OSTask_Remove(pAppRun ->AppFun);
				}
				                      
			}
			else
			{ 
				pAppRun ->loading --; 
			}
		}
		OSTask_Show();
	}
	
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





