/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Desktop.h
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
  
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_DESKTOP_H	
#define __OS_DESKTOP_H 	

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
#define USE_DESKBACK   1
#define DESK_IMAGE       gImage_Smile

typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  
enum __TASKBAR_STATE
{
	 BAR_PRESS = 0x10,
	 BAR_FREE,  
	 BAR_ACTIVATE,  
	 BAR_CLOSE,
	 BAR_FIRST,
	 BAR_RUNNING,
};		

enum __TASKBAR_ACTIVE
{ 
	 BAR_UP = 0x20,
	 BAR_DOWN,

};


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
	Type_AppList *App;		
	struct __ICO *next;		
	u16 Nox;//图标序号	
	u16 Page;
}Type_Ico;

typedef struct __Taskbar
{
	u8 activate_point;		//状态栏激活点
	u16 dynamic_Y;    //激活状态下的 触摸位置
	u8 activate_state;  //是否为激活状态
	u8  run_state; 		//状态栏运行状态
}TypeTaskbar;

typedef struct __Desk
{
	signed char CurrentPage;
	signed char FirstPage;
	signed char EndPage;   
}TypeDesk;


/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_Ico *AppRunning;	
extern Type_AppList App_Taskbar;		
extern TypeDesk DeskPage;
extern unsigned DESK_IMAGE[153608];
	
	
/* 程序注册表 ------------------------------*/		
extern Type_AppList OS_Desktop;	 
extern Type_AppList OS_AppIn;
extern Type_AppList OS_AppOut;
extern Type_AppList OS_IcoShow; 
	
	
	
/* 全局函数声明 --------------------------------------------------------------*/  
unsigned char OS_IcoCreat(Type_AppList *_App,u16 _TextColor,u16 _BackColor);


//u16 Taskbar_Draw(u16 Bar_Y);


 
#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/

 


