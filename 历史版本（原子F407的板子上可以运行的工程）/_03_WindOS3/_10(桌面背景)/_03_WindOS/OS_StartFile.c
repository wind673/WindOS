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
#include "User_Library.h" 
#include "OS_StartFile.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u32 OS_Msg = NULL;	


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
	OSTask_Creat(&APP_TouchScan); 	  			
	OSTask_Creat(&App_Taskbar);  				
	OSTask_Creat(&OS_Desktop); 			
	
	/* 硬件初始化 --------------------------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//8级抢占先级 2级响应优先级        
	delay_init(168);	    //初始化延时函数  						
	uart_init(115200);		//初始化串口波特率为115200	
	
	LCD_Init();//LCD初始化  
    if(font_init() != 0) //检查字库	
	{
		OS_String_Show(FONT_2,FONT_2*5,(u8*)"FontInit is error !!!",FONT_2); 
		while(font_init());
	} 
	
	OS_TextColor_Set(BLACK); 			
	OS_BackColor_Set(WHITE); 	
		 
	RCC_Configuration(); 
	My_GPIO_Init();	
	TIM2_Config(); 	 
	TIM3_Config(); 	
	TIM4_Config();  
	TIM5_Config();
	Drive_Touch_Init();  
 	 		 						
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





