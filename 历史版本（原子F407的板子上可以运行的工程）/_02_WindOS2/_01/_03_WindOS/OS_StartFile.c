/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_StartFile.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "My_Library.h" 
#include "OS_StartFile.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
/* App --------------------------------------------*/
Type_Addr AppHead = {0}; //定义任务堆头   



/* RAM --------------------------------------------*/
unsigned long int OS_RAM = 0; //RAM计数

/* RAM --------------------------------------------*/
unsigned long int OS_CPU = 0; //CPU计时
unsigned char OS_CPU_Flag = 0; //RAM计数

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
	Show_String(0,0,(u8*)"Drive_Init is OK!",FONT_1); //标识OK	
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSCPU_Monitor()     
* @Description   : WinOS CPU监测（开发者模式） 
* @Data          : 2016/3/16		
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int OSCPU_Monitor(void) 
{
	unsigned long int _CPU_Time = 0; 
    unsigned long int _CPU_Cnt = 0;
	
	//if(OS_CPU_Flag) return 1;
	
	if(TIM_GetCounter(TIM2) > 0xfff0ffff) TIM_SetCounter(TIM2,0);
	_CPU_Time = TIM_GetCounter(TIM2); 
	_CPU_Cnt = 0;
	while( TIM_GetCounter(TIM2)<_CPU_Time+1000 ) _CPU_Cnt++;   
	OS_CPU = 10000-_CPU_Cnt;
	
	//LCD_ShowDecim(0,FONT_2*5,_CPU_Cnt,2,12,FONT_2);  
	
	OS_CPU_Flag = 1;	 
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
	unsigned int Temp_color;  
	static long int _cnt = 0;
	unsigned char _line = 0;  

	Type_Addr *temp = &AppHead;   
	
	Temp_color = TextColor_Set(YELLOW);  
	LCD_ShowNum(0,FONT_3*6,_cnt,10,FONT_3); 
	
	/* CPU 显示 ------------------------------------*/  
	Show_String(0,FONT_2,(u8*)"CPU:",FONT_2); 
	Show_String(FONT_2*5,FONT_2,(u8*)"%",FONT_2);  
	LCD_ShowDecim(FONT_2*2,FONT_2,(double)OS_CPU/100.0f,2,5,FONT_2); 
	OS_CPU_Flag = 0;
	
	/* 任务显示 ------------------------------------*/ 
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		
		if(temp ->thread == OS_THREAD_FREE) TextColor_Set(GREEN);   
		else if(temp ->thread == OS_THREAD_FREE) TextColor_Set(YELLOW);
		else if(temp ->thread == OS_THREAD_FREE) TextColor_Set(RED); 
		else TextColor_Set(WHITE); 
		
		Show_String(120,FONT_1*_line++,temp ->name,FONT_1);   
	}
	
	TextColor_Set(Temp_color); 
	_cnt++; 
	return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()     
* @Description   : WinOSus延时函数 
* @Data          : 2016/3/19		
* @Explain       : 参数 ：_us = 延时时间   
------------------------------------------------------------------------------*/	
void OSdelay_us(unsigned long int _us)    
{   
	unsigned long int _TimeNow = TIM_GetCounter(TIM2);
  	if(_TimeNow > 0xfff0ffff) {TIM_SetCounter(TIM2,0);_TimeNow = 0; }
	
	while(TIM_GetCounter(TIM2) -_TimeNow < _us); 
		
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()     
* @Description   : WinOSus延时函数 
* @Data          : 2016/3/19		
* @Explain       : 参数 ：_ms = 延时时间   
------------------------------------------------------------------------------*/	
void OSdelay_ms(unsigned long int _ms)    
{   
	unsigned long int _TimeNow = TIM_GetCounter(TIM2);
	_ms*=1000;
  	if(_TimeNow > 0xfff0ffff) {TIM_SetCounter(TIM2,0);_TimeNow = 0; }
	
	while(TIM_GetCounter(TIM2) -_TimeNow < _ms); 
		
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_s()     
* @Description   : WinOSus延时函数 
* @Data          : 2016/3/19		
* @Explain       : 参数 ：_s = 延时时间   
------------------------------------------------------------------------------*/	
void OSdelay_s(unsigned long int _s)    
{   
	OSdelay_ms(_s*1000); 
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





