/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Touch.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_TOUCH_H
#define __DRIVE_TOUCH_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
#define TOUCH_BUFF_SIZE  		100
#define TOUCH_COLOR				DARKBLUE         
#define TOUCH_SCAN_SPEED 		20  //扫描速度
#define TOUCH_SLIP_RESPONSE 	((OS_LCD_WHITH+OS_LCD_LENTH)/20) //滑动响应点数


#define TOUCH_SLIP_LEFT		(0x01<<0) //左滑	
#define TOUCH_SLIP_RIGHT	(0x01<<1) //右滑	
#define TOUCH_SLIP_UP  		(0x01<<2) //上滑	
#define TOUCH_SLIP_DOWN  	(0x01<<3) //下滑	
   
   
#define TOUCH_STATE_OFF 	0  	//触屏空闲	
#define TOUCH_STATE_ON 		1   //正在触屏	
#define TOUCH_STATE_SLIP	2   //正在触屏	



/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct _struct_Touch
{ 
	u16 _X; //当前x坐标
	u16 _Y; //当前y坐标
	u16 _LastX; //上一次x坐标
	u16 _LastY; //上一次y坐标
	
	u16 _XY[TOUCH_BUFF_SIZE][2]; //历史坐标 
	u8  _CNT; //历史记录数
	u8  _state; //触屏状态
	u8 _slip_direction; //滑动的方向    
}Type_Touch;

/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_Touch TouchPoint;
extern Type_AppList APP_TouchScan;

/* 全局函数声明 --------------------------------------------------------------*/  
int Drive_Touch_Init(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



