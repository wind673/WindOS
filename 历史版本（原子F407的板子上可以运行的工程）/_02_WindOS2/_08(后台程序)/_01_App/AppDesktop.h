/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Appdesktop.h
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __APPDESKTOP_H
#define __APPDESKTOP_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  

/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct __ICO
{
	u16 x1;			
	u16 y1;		
	u16 x2;			
	u16 y2;			
	u16 textcolor;	
	u16 backcolor;
	u8 state;
	u8 *str;
	CreatFun *_AppStart;
	CreatFun *_AppAddr;
	CreatFun *_AppEnd; 
	struct __ICO *next;
	
}Type_Ico;

/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_Ico *AppRunning;
 
/* 全局函数声明 --------------------------------------------------------------*/  
unsigned int App_Desktop(void);
unsigned int OS_Ico_Show(void); 
unsigned int App_In(void);
unsigned int App_Out(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



