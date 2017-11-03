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
Type_Addr AppHead = {0}; //定义任务堆头    
 
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
unsigned char OSTask_Creat(  CreatFun *_AppAddr \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    ) 
						   
{  
	static Type_Addr *AppTemp = &AppHead;
		
	if( _thread   != OS_THREAD_FREE \
		&&_thread != OS_THREAD_PRIMARY \
	    &&_thread != OS_THREAD_SYSTEM  \
	   )return 1;
		
	Type_Addr *_p = NULL;
	 _p = (Type_Addr*)malloc(sizeof(Type_Addr)); //申请内存 	
		
	if(_p == NULL) return 2;
	
	AppTemp ->next = _p;    
	_p ->last = AppTemp; 			
	AppTemp = _p; 	 
	_p ->thread = _thread;
	_p ->AppFun =_AppAddr;     
	_p ->next = NULL; //堆尾   	
	_p ->name = _Name;  
	_p ->reload = _T;  //设置重载值     
	_p ->loading = _p ->reload; //填装运行槽  
	_p ->state = _state;    //运行状态   
	 
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
unsigned char OSTask_Remove(CreatFun *_AppAddr)    
{   
	Type_Addr *pTemp = &AppHead;    
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
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL) return 1;  			
	   		
	   if(pTemp ->next != NULL) pTemp = pTemp ->next;       	 
	    		 
		_cnt--; 		
	   if(_cnt == 0) return 2;  			
	}  			
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Alter()     
* @Description   : WinOS任务修改
* @Data          : 2016/3/22		
* @Explain       : 参数 ：_AppAddr = 程序地址    
*
*				   返回值 ：1,2,3 = 修改任务失败				0 = 成功
------------------------------------------------------------------------------*/	
unsigned char OSTask_Alter(  CreatFun *_AppAddr \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    )  
{   
	Type_Addr *pTemp = &AppHead;    
	unsigned int _cnt = OS_TASK_MAX;   
	
	while(1)
	{ 
	 
	   if(pTemp ->AppFun == _AppAddr) 
	   {	
		    if(_Name != OS_DEFAULT)	    pTemp ->name = _Name;
		    if(_T != OS_DEFAULT)  		pTemp ->reload = _T;
		    if(_state != OS_DEFAULT) 	pTemp ->state = _state;
		    if(_thread != OS_DEFAULT)	pTemp ->thread= _thread;
		   
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL) return 1;  			
	   		
	   if(pTemp ->next != NULL) pTemp = pTemp ->next;       	 
	    		 
		_cnt--; 		
	   if(_cnt == 0) return 2;  			
	}  			
}


 
/**----------------------------------------------------------------------------
* @FunctionName  : OSSystemShow()     
* @Description   : WinOS系统显示（开发者模式） 
* @Data          : 2016/3/16		
* @Explain       : 参数 ：_AppAddr = 程序地址    	
*
*				   返回值 ：-1,-2 = 创建任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned int OSCPU_Show(void) 
{
	unsigned int tBackColor,tTextColor;      
	static unsigned char flag = 0;
	unsigned long int _CPU_Time = 0,_CPU_Cnt = 0,OS_CPU = 0;    
	
	tTextColor = OS_TextColor_Set(OS_COLOR_CPU);
	tBackColor = OS_BackColor_Set(OS_COLOR_STATUSBAR);	
	if(flag == 0){ LCD_Fill(0,0,OS_LCD_WHITH,FONT_1-1,BLACK);flag = 1;}
	 
	/* CPU 检测 ------------------------------------*/  
	if(TIM_GetCounter(TIM2) > 0xfff0ffff) TIM_SetCounter(TIM2,0);
	_CPU_Time = TIM_GetCounter(TIM2); 
	_CPU_Cnt = 0;
	while( TIM_GetCounter(TIM2)<_CPU_Time + 100000 ) _CPU_Cnt++; //检测100ms所运行的减法数 
	OS_CPU = (1.0f - ((double)_CPU_Cnt/884000.0f))*10000;   
	
	/* CPU 显示 ------------------------------------*/  
	OS_String(0,0,(u8*)"CPU:",FONT_1); 
	OS_String(FONT_1*5,0,(u8*)"%",FONT_1);  
	LCD_ShowDecim(FONT_1*2,0,OS_CPU/100.0f,2,5,FONT_1);  
		
	
	OS_BackColor_Set(tBackColor);	
	OS_TextColor_Set(tTextColor); 
	//OSTask_Show();
	return 0;
	
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
	unsigned int Temp_Color;   
	unsigned char _line = 1;  
	Type_Addr *temp = &AppHead;   
	
	Temp_Color = OS_TextColor_Set(YELLOW);  
	
	/* 任务显示 ------------------------------------*/ 
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		
		if(temp ->thread == OS_THREAD_FREE) OS_TextColor_Set(OS_COLOR_FREE);   
		else if(temp ->thread == OS_THREAD_PRIMARY) OS_TextColor_Set(OS_COLOR_PRIMARY);
		else if(temp ->thread == OS_THREAD_SYSTEM) OS_TextColor_Set(OS_COLOR_SYSTEM); 
		else OS_TextColor_Set(OS_COLOR_OTHER); 
		
		OS_String(120,FONT_1*_line++,temp ->name,FONT_1);   
	}
	
	OS_TextColor_Set(Temp_Color); 	
	return 0;	
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





