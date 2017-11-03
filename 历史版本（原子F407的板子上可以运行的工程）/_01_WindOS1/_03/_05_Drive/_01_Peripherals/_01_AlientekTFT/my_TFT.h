//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//
#ifndef __MY_TFT_H
#define __MY_TFT_H

//��Ļ�ķֱ������� 
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
#define POINT_COLOR      TextColor
#define BACK_COLOR       BackColor

/*----------------������ɫ-------------------------------------------------------------------*/
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
//===================================================================================================





void TFT_Init(void);


//����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoints(u16 x,u16 y);

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoints(u16 x,u16 y);

//����
//x,y:����
//POINT_COLOR:���ߵ���ɫ
void LCD_DrawLines(u16 x1, u16 y1, u16 x2, u16 y2);

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
//void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);


////��ʾASCII�ַ���
////x y ��ʼ����
////*p:�ַ�����ʼ��ַ	
//void LCD_ShowString(u16 x,u16 y,u8 *p);

////��ʾ��������
////x,y:�������
////digit:����λ��
////size:�����С  12/16/24/90(Ԥ��λ����ʱ����ʵ��)
//void LCD_ShowNum(u16 x,u16 y,double num,u8 digit,u8 size);


//��ʵ��Բ��
//(x,y):���ĵ�
//size:Բ��ĵĴ�С
void LCD_Big_Point(u16 x,u16 y,u16 size,u16 color);
	

//��ʵ�ľ���
//x,y,xi,yi �����ĸ���
void LCD_Big_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

//�����ľ���
//x,y,xi,yi �����ĸ���
void Draw_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

//��������
//mode �Ƿ�д���� 1д   0��д
//density �����ܶ�
void Creat_Coord(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode);


//RGB565  16λ�����ʾ
//���ɷ���
//��ͷ����
void Show_Picture0(u16 x1,u16 y1,const u8 *pic);

//RGB565  16λ�����ʾ
//�ɷ���
//��ͷ����
void Show_Picture1(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic);


//��ʾ�ַ���
//x y ��ʼ����
//*p:�ַ�����ʼ��ַ	
//size:�ֳߴ� 16 24 32��ѡ
void  Show_String(uint16_t x,uint16_t y,u8*str,u8 size);






void LCD_Fonts_Init(void);

#endif

//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//

