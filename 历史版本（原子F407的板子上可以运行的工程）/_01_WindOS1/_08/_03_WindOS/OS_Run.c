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
extern Type_Addr FreeHead;
extern Type_Addr PrimaryHead;
extern Type_Addr SystemHead;

Type_Addr *FreeRun = &FreeHead;
Type_Addr *PrimaryRun = &PrimaryHead;
Type_Addr *SystemRun = &SystemHead;


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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//8级抢占先级 2级响应优先级        
	delay_init(168);	    //初始化延时函数  						
	uart_init(115200);		//初始化串口波特率为115200					
	TFT_Init(); 																	
	RCC_Configuration();    //初始化时钟	 
	My_GPIO_Init();		
	TIM3_Config(); //主线程
	TIM4_Config(); //系统线程
	Show_String(0,0,"Drive_Init is OK!",FONT_1); //标识OK	
	
}	
			
/**----------------------------------------------------------------------------
* @FunctionName  : OSFree_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : 空闲线程
------------------------------------------------------------------------------*/
void OSThread_Free(void)
{
	 
	while(1)
	{  
		if(FreeRun ->next == NULL) FreeRun = &FreeHead;
		else 
		{
			FreeRun = FreeRun ->next; 
					
			if(FreeRun ->loading == 0 ) 
			{
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
					FreeRun ->state = OS_STATE_ACTIVE;//重新激活
					FreeRun ->loading = FreeRun ->reload;		 
				}  
			
			} 
		   			
		}
		
	FreeRun ->loading --;	
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





