/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : My_Timer.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "My_Timer.h"
#include "My_Library.h" 

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_Config()     
* @Description   : None 
* @Data          : 2016/3/18
* @Explain       : 1ms时间片
------------------------------------------------------------------------------*/
void TIM3_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//配置时钟及初始化预装值
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period =1000-1;//重装载值
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//允许定时器9更新中断							//@
	
/*---------------------------------------------------------------------------------------------*/
	RCC_HCLKConfig(RCC_SYSCLK_Div1);  

//配置中断层
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM3_IRQn; //定时器 x 中断							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 7 ; //抢占优先级 7
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC
 	TIM_Cmd(TIM3,ENABLE); //使能定时器 x												//@
/*---------------------------------------------------------------------------------------------*/
}
	




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





