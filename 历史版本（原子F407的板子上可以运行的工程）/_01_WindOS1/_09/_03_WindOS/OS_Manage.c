/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Manage.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Manage.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/ 

/* 全局变量定义 --------------------------------------------------------------*/



/* 全局函数编写 --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Creat()     
* @Description   : WinOS任务创建 
* @Data          : 2016/3/16
* @Explain       : 参数 ： _AppAddr = 程序地址       _Name = 程序名字 
*				  		   _T = 运行周期    	_state = 运行状态  
*						   _thread = 线程
*	
*				   返回值 ：-1 = 创建任务失败				0 = 成功
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
		
	
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //申请内存 		
	if(_p == NULL) return -2;
	
	if(_thread == OS_THREAD_PRIMARY) //主线程
	{
		PrimaryTemp ->next = _p;    
		_p ->last = PrimaryTemp; 			
		PrimaryTemp = _p; 		 
	}
	else if(_thread == OS_THREAD_FREE)  //空闲（后台）线程
	{ 
		FreeTemp ->next = _p;    
		_p ->last = FreeTemp; 			
		FreeTemp = _p; 	 
	} 
	else if(_thread == OS_THREAD_SYSTEM)   //系统线程 
	{
		SystemTemp ->next = _p;    
		_p ->last = SystemTemp; 			
		SystemTemp = _p; 		 
	}
	
	_p ->AppFun = _AppAddr;     
	_p ->next = NULL; //循环队列   	
	_p ->name = _Name;  
	_p ->reload = _T;  //设置重载值     
	_p ->loading = _p ->reload; //填装运行槽  
	_p ->state = _state;    //运行状态   
	
	  
	OS_RAM = (unsigned long int)_p; //记录OS使用的内存数量    	 
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS任务删除 
* @Data          : 2016/3/16		
* @Explain       : 参数 ：_AppAddr = 程序地址    
*
*				   返回值 ：-1,-2,-3 = 创建任务失败				0 = 成功
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
		    OS_RAM = (unsigned long int)pTemp; //记录OS使用的内存数量	 	
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









/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





