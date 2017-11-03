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
Type_Addr AppHead = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //定义程序运行的头帧
Type_Addr *pTemp = &AppHead;  
	
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Init()     
* @Description   : WinOS初始化 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Init(void)
{		
	 
	/* WindOS初始化 ------------------------------------*/  
	
	/* 硬件初始化 --------------------------------------*/
	Drive_Init(); 
	
}			

 
	
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Creat()     
* @Description   : WinOS任务创建 
* @Data          : 2016/3/16
* @Explain       : 参数 ： _AppAddr = 程序地址       _Name = 程序名字 
*				  		   _period = 运行周期    	_state = 运行状态  
*						   _thread = 线程
*				   返回值 ：-1 = 创建任务失败				0 = 成功
------------------------------------------------------------------------------*/	
signed char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _period,unsigned char _state,unsigned char _thread)
{  
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //申请内存 		
	if(_p == NULL) return -1;
	
	pTemp ->next = _p;    
	_p ->last = pTemp; 			
	pTemp = _p; 		
	_p ->AppFun = _AppAddr;     
	_p ->next = AppHead.next; //循环队列
	_p ->name = _Name; 
	_p ->reload = _period;  //设置重载值
	_p ->loading = _p ->reload; //重新装载重载值
	_p ->state = _state;    //运行状态
	
	OS_RAM += sizeof(Type_Addr); //记录OS使用的内存数量	 
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS任务删除 
* @Data          : 2016/3/16		
* @Explain       : 参数 ：_AppAddr = 程序地址    		
*				   返回值 ：-1,-2 = 创建任务失败				0 = 成功
------------------------------------------------------------------------------*/	
signed char OSTask_Remove(CreatFun *_AppAddr) 
{  
	Type_Addr *pTemp = &AppHead;
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
			 return -1;   
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
*				   返回值 ：-1,-2 = 创建任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned int OSTask_Show(void) 
{
	TextColor_Set(YELLOW);
	LCD_ShowNum(120,0,OS_RAM,10,FONT_1); 	
	Show_String(120,FONT_1*1,pTemp ->name,FONT_1); 
	LCD_ShowNum(120,FONT_1*2,pTemp ->loading,10,FONT_1); 		
	
	return 0;
}






/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





