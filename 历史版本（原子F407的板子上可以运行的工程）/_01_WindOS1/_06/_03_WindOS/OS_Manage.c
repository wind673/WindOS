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
#include "OS_StartFile.h" 

 

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/ 

/* 全局变量定义 --------------------------------------------------------------*/
unsigned long int OS_RAM = 0; //RAM计数
Type_Addr FreeHead = {0}; //定义空闲程序运行的头帧   
Type_Addr PrimaryHead = {0}; //定义主程序运行的头帧 

Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  



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
signed char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T,unsigned char _state,unsigned char _thread)
{   
	if(_thread == OS_FREE)  
	{
		Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //申请内存 		
		if(_p == NULL) return -1;
		
		FreeTemp ->next = _p;    
		_p ->last = FreeTemp; 			
		FreeTemp = _p; 		
		_p ->AppFun = _AppAddr;     
		_p ->next = NULL; //循环队列   	
		_p ->name = _Name;  
		_p ->reload = _T;  //设置重载值     
		_p ->loading = _p ->reload; //填装运行槽  
		_p ->state = _state;    //运行状态    
	}
	else if(_thread == THREAD_PRIMARY)   
	{
		Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //申请内存 		
		if(_p == NULL) return -1;		
		
		PrimaryTemp ->next = _p;    
		_p ->last = PrimaryTemp; 			
		PrimaryTemp = _p; 		
		_p ->AppFun = _AppAddr;     
		_p ->next = NULL; //循环队列   
		_p ->name = _Name;  
		_p ->reload = _T;  //设置重载值 
		_p ->loading = _p ->reload; //填装运行槽		
		_p ->state = _state;    //运行状态  
	 
	}
	  
	OS_RAM += sizeof(Type_Addr); //记录OS使用的内存数量    	 
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
	Type_Addr *pTemp = NULL;  	
	pTemp = &FreeHead;    
	unsigned char thread_cnt = 0;   
	unsigned int _cnt = TASK_MAX;   
	
	while(1)
	{ 
	   if(pTemp ->AppFun == _AppAddr) 
	   {	
		    (pTemp ->last) ->next = pTemp ->next;	
		    (pTemp ->next) ->last = pTemp ->last;	
		    pTemp ->AppFun = NULL;   	
		    free(pTemp); 		
		    pTemp =NULL;  		
		    OS_RAM -= sizeof(Type_Addr); //记录OS使用的内存数量	 	
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL)		
	   {		
		     if(thread_cnt == 0) pTemp = &PrimaryHead; 
		     if(thread_cnt >= 9) return -1;  
			 thread_cnt++;  	
	   }			
	   else			
	   {			
			pTemp = pTemp ->next;       	 
	   }			
	   
		_cnt--; 			
	   if(_cnt == 0) return -2;  			
	} 
	 			
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Show()     
* @Description   : WinOS任务显示（开发者模式） 
* @Data          : 2016/3/16		
* @Explain       : 参数 ：_AppAddr = 程序地址    	
*
*				   返回值 ：-1,-2 = 创建任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned int OSTask_Show(void) 
{
	unsigned int Temp_color;
	Temp_color = TextColor_Set(YELLOW);
	LCD_ShowNum(170,0,OS_RAM,10,FONT_1); 	
	Show_String(170,FONT_1*1,FreeTemp ->name,FONT_1); 		
	TextColor_Set(Temp_color);
	return 0;
}






/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





