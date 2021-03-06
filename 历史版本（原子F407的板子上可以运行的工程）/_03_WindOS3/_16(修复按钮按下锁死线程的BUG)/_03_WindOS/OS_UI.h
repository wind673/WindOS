/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_UI.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_UI_H
#define __OS_UI_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0

/*----------------兼容颜色---------------------------------------*/
/* LCD color */
#define White          0xFFFF //白色
#define Black          0x0000 //黑色
#define Grey           0xF7DE //灰色
#define Blue           0x001F //蓝色
#define Blue2          0x051F //深蓝色
#define Red            0xF800 //红色
#define Magenta        0xF81F //品红
#define Green          0x07E0 //绿色
#define Cyan           0x7FFF //蓝绿色
#define Yellow         0xFFE0 //黄色
#define BROWN 		   0XBC40 //棕色
#define GRAY  		   0X8430 //灰色

/* 尺寸 --------------------------------------------------------*/
#define OS_LCD_WHITH  	240	 //宽度	
#define OS_LCD_LENTH  	320	 //高度	
#define OS_ICO_COLOUR_BACK  GREEN //系统桌面 图标背景颜色
#define OS_ICO_COLOUR_TEXT  WHITE  //系统桌面 图标文字颜色
		
#define FONT_1   12				
#define FONT_2   16			
#define FONT_3   24 
#define FONT1   FONT_1				
#define FONT2   FONT_2			
#define FONT3   FONT_3 

#define IOC_SIZE 64			



#ifndef OS_DEFAULT
#define OS_DEFAULT 	     	     NULL	  //缺省值
#endif


/* 兼容以前的代码 -----------------------------------------------*/
#define TextColor POINT_COLOR			
#define BackColor BACK_COLOR		
 	
/* 程序需要 ----------------------------------------------------*/
#define OS_CLEAR_PURE				(0x01 << 0)	
#define OS_CLEAR_IMAGE				 0x00	
#define OS_CLEAR_WEAKNESS			(0x01 << 1)		
#define OS_CLEAR_CONSTRAINT			 0x00 

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
u16  OS_Point_Read(u16 x,u16 y);
unsigned int OS_TextColor_Set(u16 _color);
unsigned int OS_BackColor_Set(u16 _color);
void OS_Points_Draw(u16 x,u16 y,u16 color);
void OS_Lines_Draw(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void OS_Circle_Draw(u16 x,u16 y,u8 size,u8 mode,u16 color);
void OS_Rect_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u16 color);
void OS_Coord_Draw(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode);
void OS_Picture_Draw(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic,u8 mode);
void OS_String_Show(u16 x,u16 y,u8*str,u8 size,u8 mode);
void OS_Decim_Show(u16 x,u16 y,double num,u8 digit,u8 len,u8 size,u8 mode);
void OS_Num_Show(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode); 
void OS_Button_Creat(Type_Button *pStruct,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color);
void OS_Button_Alter(Type_Button *ButtonStruct,u8 state,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color);
void OS_Button_Show(Type_Button *ButtonStruct,u8 state);      
void OS_Button_LastClear(Type_Button *ButtonStruct);
u8 Button_State(Type_Button *ButtonStruct);    
u16 OS_Clear_Y(u16 _Bar_Y,u8 _mode,u16 _color);


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/






