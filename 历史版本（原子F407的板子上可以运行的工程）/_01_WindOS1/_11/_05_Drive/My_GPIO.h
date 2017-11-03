/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : My_GPIO.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __MY_GPIO_H
#define __MY_GPIO_H 

/* 头文件包含 ----------------------------------------------------------------*/  

/* 全局宏定义 ----------------------------------------------------------------*/
#define PF9			PFout(9)
#define PF10		PFout(10)

#define LED_RED		PF9
#define LED_GREEN  	PF10

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  
int My_GPIO_Init(void);


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



