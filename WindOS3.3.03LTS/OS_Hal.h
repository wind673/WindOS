/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Hal.h
* @Description : 系统抽象层
* @Date        : 2017/11/03
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : 移植系统前必须完成以下内容。
*=============================================================================*/     

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_HAL_H
#define __OS_HAL_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
#if defined (STM32L1XX_MD)
#define ADDR_CHIPID_0		0x1FF80050
#define ADDR_CHIPID_1		0x1FF80054
#define ADDR_CHIPID_2		0x1FF80064
#elif defined (STM32F40_41xxx)
#define ADDR_CHIPID_0		0x1FFF7A10
#define ADDR_CHIPID_1		0x1FFF7A14
#define ADDR_CHIPID_2		0x1FFF7A18
#endif

#define OS_TIMER_CNT_MAX	(0xffff)
#define OS_Clock_us			(TIM_GetCounter(TIM2))




/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/    	
void TIM2_Init(void);
void TIM6_Init(void);
void TIM4_Init(void);


#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/












