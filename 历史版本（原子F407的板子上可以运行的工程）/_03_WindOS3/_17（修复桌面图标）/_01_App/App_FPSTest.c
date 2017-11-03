/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_FPSTest.c
* @Description : 读取图片App
* @Date        : 2016/4/25
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_FPSTest.h"   
 
/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : FPSTest()    	 
* @Description   : None 	
* @Data          : 2016/4/25	
* @Explain       : None	
------------------------------------------------------------------------------*/
unsigned int FPSTest(void)
{
	volatile u32 _cntPure,_cntImage,_NowTime,_InTime;
	u16 _color = 0;
	OS_BackColor_Set(GRAY);		
	
	/* 刷纯色图 -------------------------------------*/
	_InTime = TIM_GetCounter(TIM2); _cntPure = 0; 
	if(_NowTime > 0xfff0ffff) {TIM_SetCounter(TIM2,0); _NowTime = 0;}
	while(1)
	{
		LCD_Fill(0,0,OS_LCD_WHITH,OS_LCD_LENTH,_color++);  
		_cntPure ++;
		_NowTime = TIM_GetCounter(TIM2);
		if( _NowTime - _InTime > 1000000) break;
	}
	 
	
	/* 刷图片 ---------------------------------------*/
	_InTime = TIM_GetCounter(TIM2); _cntImage = 0;
	if(_NowTime > 0xfff0ffff) {TIM_SetCounter(TIM2,0);_NowTime = 0;}
	while(1) 
	{
		OS_Picture_Draw(0,FONT_1,OS_LCD_WHITH,OS_LCD_LENTH,(const u8*)DESK_IMAGE,0);
		_cntImage ++;
		_NowTime = TIM_GetCounter(TIM2);
		if( _NowTime - _InTime > 1000000) break;
	}
	
	OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_CONSTRAINT,NULL);
	
	OS_String_Show(FONT_3*1,FONT_3*2,(u8*)" Pure FPS:    ",FONT_2,1);
	OS_Num_Show(FONT_3*4,FONT_3*2,_cntPure,4,FONT_2,0);       
	OS_String_Show(FONT_3*1,FONT_3*3,(u8*)" Image FPS:   ",FONT_2,1);
	OS_Num_Show(FONT_3*4,FONT_3*3,_cntImage,4,FONT_2,0);
	
	return 0; 
}
							
	 			
Type_AppList App_FPSTest = {NULL,NULL,FPSTest,NULL, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"FPS",300,USE_OS_ICO};			
		


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





