/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Button.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_BUTTON_H
#define __OS_BUTTON_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/ 
#define BUTTON_UP					1
#define BUTTON_DOWN 				2
#define BUTTON_DOWNED 				3 
#define BUTTON_DISABLED 			4
#define BUTTON_CLOSE				5
#define BUTTON_DEFAULT 				BUTTON_UP

#define BUTTON_VALID 				1
#define BUTTON_INVALID 				0


/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct __OS_Button
{
	u16 x1;			
	u16 y1;			
	u16 x2;			
	u16 y2;			
	u16 color;  
	u8 value; 	//该按钮的值
	u8 state;	//按钮现状	
	u8 LastState; //不会自动清除的状态
	u8 *str;		
	u16 fontsize;	 
	struct __OS_Button *next;		
	
}Type_Button;
	
/* 全局变量声明 --------------------------------------------------------------*/  
extern Type_AppList OS_Button_Scan;


/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Button_Creat(Type_Button *pStruct,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color);
void OS_Button_Alter(Type_Button *ButtonStruct,u8 state,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color);
void OS_Button_Show(Type_Button *ButtonStruct,u8 state);      
void OS_Button_LastClear(Type_Button *ButtonStruct);
u8 OS_Button_State(Type_Button *ButtonStruct);    



#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/








