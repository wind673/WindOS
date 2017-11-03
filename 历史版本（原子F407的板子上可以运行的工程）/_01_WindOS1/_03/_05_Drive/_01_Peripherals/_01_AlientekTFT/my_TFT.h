//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//
#ifndef __MY_TFT_H
#define __MY_TFT_H

//屏幕的分辨率设置 
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



extern __IO uint16_t TextColor,BackColor;

//===================================================================================================

extern void LCD_WriteRAM(uint16_t RGB_Code);
extern void LCD_WriteRAM_Prepare(void);
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
#define POINT_COLOR      TextColor
#define BACK_COLOR       BackColor

/*----------------兼容颜色-------------------------------------------------------------------*/
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
#define BROWN 			   0XBC40 //棕色
#define GRAY  			   0X8430 //灰色
//===================================================================================================





void TFT_Init(void);


//定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void LCD_DrawPoints(u16 x,u16 y);

//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void LCD_DrawPoints(u16 x,u16 y);

//画线
//x,y:坐标
//POINT_COLOR:此线的颜色
void LCD_DrawLines(u16 x1, u16 y1, u16 x2, u16 y2);

//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
//void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);


////显示ASCII字符串
////x y 起始坐标
////*p:字符串起始地址	
//void LCD_ShowString(u16 x,u16 y,u8 *p);

////显示任意数字
////x,y:起点坐标
////digit:保留位数
////size:字体大小  12/16/24/90(预留位，暂时不能实现)
//void LCD_ShowNum(u16 x,u16 y,double num,u8 digit,u8 size);


//画实心圆点
//(x,y):中心点
//size:圆点的的大小
void LCD_Big_Point(u16 x,u16 y,u16 size,u16 color);
	

//画实心矩形
//x,y,xi,yi 矩形四个角
void LCD_Big_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

//画空心矩形
//x,y,xi,yi 矩形四个角
void Draw_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

//创建坐标
//mode 是否写背景 1写   0不写
//density 网格密度
void Creat_Coord(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode);


//RGB565  16位真彩显示
//不可放缩
//带头数据
void Show_Picture0(u16 x1,u16 y1,const u8 *pic);

//RGB565  16位真彩显示
//可放缩
//带头数据
void Show_Picture1(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic);


//显示字符串
//x y 起始坐标
//*p:字符串起始地址	
//size:字尺寸 16 24 32可选
void  Show_String(uint16_t x,uint16_t y,u8*str,u8 size);






void LCD_Fonts_Init(void);

#endif

//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//

