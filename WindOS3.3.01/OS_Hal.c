/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Hal.c
* @Description : 系统抽象层
* @Date        : 2017/11/03
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : 移植系统前必须完成以下内容。
------------------------------------------------------------------------------- 
修订记录：	
 @Date		@Version			@Revise					@Author
2017/10/16 	V1.1.1				第一次更新				Wind（谢玉伸）

最后修订：
第一次更新
*=============================================================================*/     

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Hal.h"
#include "OS_StartFile.h"
#include "OS_Manage.h"
#include "OS_Tools.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : 用于时钟 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM2_Init(void)
{ 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = 0xffff - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : 用于主线程
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM4_Init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_PRIOITY_PRIMARY;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM4, ENABLE);  //使能TIMx	
}	


/**----------------------------------------------------------------------------
* @FunctionName  : TIM6_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : 用于系统线程 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能
	
	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_PRIOITY_SYSTEM;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM6, ENABLE);  //使能TIMx	 
} 



/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_IRQHandler()
* @Description   : 定时器服务函数
* @Data          : 2016/8/8
* @Explain       : 用于时钟
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM2_IRQHandler(void)
{ 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除TIMx更新中断标志
    OS_TimeOver_Cnt ++; 
}



/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_IRQHandler()
* @Description   : 定时器服务函数
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM4_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除TIMx更新中断标志
    OSThread_Handle(OS_THREAD_PRIMARY);
	
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_IRQHandler()
* @Description   : 定时器服务函数
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM6_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除TIMx更新中断标志
    OSThread_Handle(OS_THREAD_SYSTEM);
	
}



//main Demo
/* 
int main()					
{		  
	// WindOS初始化 -------------------------------
	OS_Init();      
	Bsp_Init();		
	
	// 程序注册 ----------------------------------- 		
	//OSTask_Creat(&App_Test);   	 	
	OSTask_Creat(&App_LED);   		//LED控制	
	OSTask_Creat(&App_Key); 		//按键		 
	
	// WindOS空闲程序 -----------------------------
	while(1) OSThread_Handle(OS_THREAD_FREE); 		
	
}	

*/




/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





