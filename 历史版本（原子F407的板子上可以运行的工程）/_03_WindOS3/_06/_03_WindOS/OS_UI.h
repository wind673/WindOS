/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_UI.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __OS_UI_H
#define __OS_UI_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
//������ɫ
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

/*----------------������ɫ---------------------------------------*/
/* LCD color */
#define White          0xFFFF //��ɫ
#define Black          0x0000 //��ɫ
#define Grey           0xF7DE //��ɫ
#define Blue           0x001F //��ɫ
#define Blue2          0x051F //����ɫ
#define Red            0xF800 //��ɫ
#define Magenta        0xF81F //Ʒ��
#define Green          0x07E0 //��ɫ
#define Cyan           0x7FFF //����ɫ
#define Yellow         0xFFE0 //��ɫ
#define BROWN 			   0XBC40 //��ɫ
#define GRAY  			   0X8430 //��ɫ

/* �ߴ� --------------------------------------------------------*/
#define FONT_1   12				
#define FONT_2   16			
#define FONT_3   24 		
#define IOC_SIZE 64			

/* ������ǰ�Ĵ��� -----------------------------------------------*/
#define TextColor POINT_COLOR			
#define BackColor BACK_COLOR		

/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct __OS_Button
{
	u16 x1;			
	u16 y1;			
	u16 x2;			
	u16 y2;			
	u16 textcolor;	
	u16 backcolor;  
	u8 state;
	u8 *str;
	
	struct __OS_Button *next;
	
}Type_Button;
	
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_Button *Button_Temp;
extern Type_Button Button_Head;
/* ȫ�ֺ������� --------------------------------------------------------------*/  
unsigned int OS_TextColor_Set(u16 _color);
unsigned int OS_BackColor_Set(u16 _color);
void OS_Points_Draw(u16 x,u16 y,u16 color);
void OS_Lines_Draw(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void OS_Circle_Draw(u16 x,u16 y,u8 size,u8 mode,u16 color);
void OS_Rect_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u16 color);
void OS_Coord_Draw(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode);
void OS_Picture_Draw(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic,u8 mode);
void  OS_String_Show(u16 x,u16 y,u8*str,u8 size);
void OS_Decim_Show(u16 x,u16 y,double num,u8 digit,u8 len,u8 size);
void OS_Num_Show(u16 x,u16 y,u32 num,u8 len,u8 size);
u16 OS_Point_Read(u16 x,u16 y);
void OS_Button_Creat(u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color,u8 state);

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/






