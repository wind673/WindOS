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
Type_Addr SystemHead= {0}; //定义系统程序运行的头帧 
Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  
Type_Addr *SystemTemp = &SystemHead;  



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
	if( _thread   != THREAD_FREE \
		&&_thread != THREAD_PRIMARY \
	    &&_thread != THREAD_SYSTEM  \
	   )return -1;
		
	
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //申请内存 		
	if(_p == NULL) return -2;
	
	if(_thread == THREAD_PRIMARY) //主线程
	{
		PrimaryTemp ->next = _p;    
		_p ->last = PrimaryTemp; 			
		PrimaryTemp = _p; 		 
	}
	else if(_thread == THREAD_FREE)  //空闲（后台）线程
	{ 
		FreeTemp ->next = _p;    
		_p ->last = FreeTemp; 			
		FreeTemp = _p; 	 
	} 
	else if(_thread == THREAD_SYSTEM)   //系统线程 
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
	unsigned long int _RAM = 0;
	static long int _cnt = 0;
    int *_RAM_Test = (int*)malloc(sizeof(int)); 
	
	_cnt++; 
	Temp_color = TextColor_Set(RED); 
    Show_String(0,50+FONT_3*3,(u8*)"OSTask_Show",FONT_3);  
	TextColor_Set(GREEN);	
	LCD_ShowNum(150,60+FONT_3*3,_cnt,7,FONT_2); 
	
	
	/* RAM 显示 ------------------------------------*/
	TextColor_Set(YELLOW);
	Show_String(0,FONT_1,(u8*)"RAM:",FONT_1); 
	_RAM = 0x20000 - ((unsigned long int)&_RAM_Test - 0x20000000);
	LCD_ShowDecim(FONT_1*5,FONT_1,(double)_RAM/0x20000,2,5,FONT_1);  
	Show_String(FONT_1*8,FONT_1,(u8*)"%",FONT_1); 
	
	Show_String(0,FONT_1*2,(u8*)"RAM_Used:",FONT_1); 
	_RAM = (unsigned long int)&_RAM_Test - 0x20000000;
	LCD_ShowNum(FONT_1*5,FONT_1*2,_RAM,6,FONT_1); 
	
	Show_String(0,FONT_1*3,(u8*)"RAM_All:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*3,(unsigned long int)0x20000,6,FONT_1); 
	
	Show_String(0,FONT_1*4,(u8*)"RAM_Start:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*4,(unsigned long int)0x20000000,9,FONT_1); 
	
	Show_String(0,FONT_1*5,(u8*)"RAM_Now:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*5,(unsigned long int)&_RAM_Test,9,FONT_1); 
	
	Show_String(150,0,FreeTemp ->name,FONT_1);                    
	Show_String(150,FONT_1*1,PrimaryTemp ->name,FONT_1);   
	Show_String(150,FONT_1*2,SystemTemp ->name,FONT_1);
	TextColor_Set(Temp_color); 
	
	free(_RAM_Test);
	return 0;
}






/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





