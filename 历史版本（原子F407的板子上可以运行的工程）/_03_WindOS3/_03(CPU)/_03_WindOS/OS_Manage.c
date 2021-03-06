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
/* App --------------------------------------------*/
Type_AppList AppHead = {NULL}; //定义任务堆头    
 
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
unsigned char OSTask_Creat(Type_AppList *_AppList) 				   
{  
	static Type_AppList *AppTemp = &AppHead;	
	
	AppTemp ->next = _AppList;     					
	AppTemp = _AppList; 	 
	AppTemp ->next = NULL; //堆尾   

#if USE_OS_DESKTOP == 1	//使用系统桌面
	if(_AppList ->name != NULL)
	OS_IcoCreat(_AppList,OS_ICO_COLOUR_TEXT,OS_ICO_COLOUR_BACK);	 
#endif
	
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS任务删除 
* @Data          : 2016/3/16		
* @Explain       : 参数 ：_AppAddr = 程序地址    
*
*				   返回值 ：1,2,3 = 删除任务失败				0 = 成功
------------------------------------------------------------------------------*/	
unsigned char OSTask_Remove(Type_AppList *_AppList)    
{   
	Type_AppList *pPre = NULL; //上一个节点    
	Type_AppList *pList = &AppHead; 
	unsigned int _cnt = OS_TASK_MAX; //在最大任务内查询
	unsigned char _exist = 0;	
	
	/* 判断任务是否存在 ----------------------------*/
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	
		
		pPre = 	pList; //记录上一个节点
		if(pList->next != NULL) pList = pList->next;		
		else break;  
		
		_cnt--; 				
		if(_cnt == 0) return 2;  		
		
	}
	if(_exist == 0) return 1;  
	
	/* 删除任务 -----------------------------------*/
	pPre ->next = pList ->next;
	pList ->AppMain = NULL;   
	pList ->AppBack = NULL;   
	pList ->AppStart = NULL;   
	pList ->AppEnd = NULL;   
	    
	free(pList); 		
	pList =NULL;  		 
	   	  
	return 0;		
}  			


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Alter()     
* @Description   : WinOS任务修改
* @Data          : 2016/3/22		
* @Explain       : 参数 ：_AppAddr = 程序地址    
*
*				   返回值 ：1,2,3 = 修改任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned char OSTask_Alter(  Type_AppList *_AppList \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    )  
{     
	Type_AppList *pList = &AppHead;    	
	unsigned int _cnt = OS_TASK_MAX;   			
	unsigned char _exist = 0;				
																
	/* 判断任务是否存在 ----------------------------*/				
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	 
		if(pList->next != NULL) pList = pList->next;		
		else break;   									
	}		 
	if(_exist == 0) return 1;	
				
	/* 修改数据 -----------------------------------*/		
	if(_Name != OS_DEFAULT)	_AppList ->name = _Name;		
	if(_T != OS_DEFAULT)  	_AppList ->reload = _T;		
	if(_state != OS_DEFAULT) 	_AppList ->state = _state;		
	if(_thread != OS_DEFAULT)	_AppList ->thread= _thread;		
																
	_cnt--; 															
    if(_cnt == 0) return 2;  	
	
	return 0;				
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSRunning_Break()     
* @Description   : WinOS打断运行
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
* @Description   : WinOS继续运行
* @Data          : 2016/3/23		
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int OSRunning_Continue(void) 
{
	
	OS_Msg &=  ~OS_BREAK; 
	return 0; 
}

 

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





