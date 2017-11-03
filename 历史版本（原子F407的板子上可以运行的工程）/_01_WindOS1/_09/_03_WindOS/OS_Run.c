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
																		
/* 私有宏定义 ----------------------------------------------------------------*/
											
/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/

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
	TIM2_Config(); //系统时钟
	TIM3_Config(); //主线程
	TIM4_Config(); //系统线程
	tp_dev.init(); //触摸屏初始化
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
		TIM_GetCounter(TIM2);
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
	unsigned char _line = 0;
    int *_RAM_Test = (int*)malloc(sizeof(int)); 
	Type_Addr *temp =NULL;
	
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
	
	/* 任务显示 ------------------------------------*/
	temp = &FreeHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		Show_String(150,FONT_1*_line++,temp ->name,FONT_1);          
	}
	temp = &PrimaryHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		Show_String(150,FONT_1*_line++,temp ->name,FONT_1);          
	}
	temp = &SystemHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		Show_String(150,FONT_1*_line++,temp ->name,FONT_1);       
	}
	
	TextColor_Set(Temp_color); 
	
	free(_RAM_Test);
	return 0;
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





