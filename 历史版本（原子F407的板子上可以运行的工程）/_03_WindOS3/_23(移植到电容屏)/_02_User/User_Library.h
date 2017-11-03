/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : My_Library.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __MY_LIBRARY_H
#define __MY_LIBRARY_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "arm_math.h"
#include "stm32f4xx.h" 
#include "stm32f4xx_exti.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_usart.h"	
#include "stm32f4xx_dma.h"	
#include "stm32f4xx_adc.h"	 
#include "sys.h"


/* 平台驱动 -------------------------------*/  
#include "my_sys.h"  
#include "touch.h"
#include <malloc.h>
#include "sys.h"
#include "usart.h"	
#include "malloc.h" 
#include "w25qxx.h"    
#include "exfuns.h"   
#include "sdio_sdcard.h"    
#include "malloc.h" 
#include "fontupd.h"
#include "ff.h"  
#include "text.h"	
#include "delay.h"
#include "usart.h"
#include "lcd.h"


/* 硬件驱动 -------------------------------*/  
#include "Drive_GPIO.h"	
#include "Drive_Interrupt.h"	
#include "Drive_Timer.h"	
#include "Drive_Touch.h" 	
#include "Drive_Flash.h"		
#include "Drive_DMA.h"  
#include "Drive_FFT.h"


/* WindOS系统自身头文件 --------------------*/  
#include "OS_Run.h"			
#include "OS_UI.h"	
#include "OS_Button.h" 
#include "OS_Manage.h"					
#include "OS_Desktop.h" 	 
#include "Material.h"   


/* 应用程序 --------------------------------*/   
#include "App_LED.h" 				
#include "App_Draw.h" 	
#include "App_ReadScreenID.h" 		
#include "App_Flash.h" 		
#include "App_CPUMonitor.h" 	
#include "App_Flash.h" 			
#include "App_FPSTest.h"   	
#include "App_OSC.h"  
#include "App_Test.h"  


/* 全局宏定义 ----------------------------------------------------------------*/ 

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  



#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



