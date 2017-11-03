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
#define BROWN 		   0XBC40 //��ɫ
#define GRAY  		   0X8430 //��ɫ

/* �ߴ� --------------------------------------------------------*/
#define OS_LCD_WHITH  	800	 //���	
#define OS_LCD_HEIGHT  	480	 //�߶�	
#define OS_ICO_COLOUR_BACK  GREEN //ϵͳ���� ͼ�걳����ɫ
#define OS_ICO_COLOUR_TEXT  WHITE  //ϵͳ���� ͼ��������ɫ
		
#define FONT_1   16				
#define FONT_2   24			
#define FONT_3   32 
#define FONT1   FONT_1				
#define FONT2   FONT_2			
#define FONT3   FONT_3 

#define IOC_SIZE 64			



#ifndef OS_DEFAULT
#define OS_DEFAULT 	     	     NULL	  //ȱʡֵ
#endif


/* ������ǰ�Ĵ��� -----------------------------------------------*/ 
 	
/* ������Ҫ ----------------------------------------------------*/
#define OS_CLEAR_PURE				(0x01 << 0)	
#define OS_CLEAR_IMAGE				 0x00	
#define OS_CLEAR_WEAKNESS			(0x01 << 1)		
#define OS_CLEAR_CONSTRAINT			 0x00 

#define OSC_FORMAT_U8				0x01
#define OSC_FORMAT_U16				0x02
#define OSC_FORMAT_FLOAT			0x03
#define OSC_FORMAT_DOUBLE			0x04

#define OSC_MODE_WINDOWS_SHOW		0x01 			 
#define OSC_MODE_LINE_SHOW			0x02	 	

#define OSC_MODE_ERROR				0x00	
#define OSC_MODE_NORMAL				0x01 			 
#define OSC_MODE_FFT				0x02	 	

/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct __TYPE_OSC
{ 
	u16 x,y;//OSC���ڵ�λ�� 
	float ZoomWindows;//��ʾ����������  1.0�Ǳ�׼��
	int ShiftX; //����ƫ����	0�Ǳ�׼��
	int ShiftY; //����ƫ����	0�Ǳ�׼��
	float ZoomX;  //����������	1.0�Ǳ�׼��
	float ZoomY;  //����������   1.0�Ǳ�׼��
	u16 LineColor;//������ɫ
	u16 BackColor;//������ɫ
	u16 WindowsColor;//������ɫ
	u8 LineSize;//������ϸ�ĳߴ�
	u8 Mode;//0:����ʾ���	1����ʾ�����FFTģʽ��
	
	u16 BuffLenth;//���� 
	u8 BuffFormat;//Buff�ĸ�ʽ
	u16 *Buff_u16;
	u8 *Buff_u8;
	float *Buff_float;
	double *Buff_double;
	
	//�������ݲ���Ҫ�û�ȥ����
	u16 LastBuff[2][OS_LCD_WHITH];	
	u16 LastZeroLine;
	u8 LastBuff_Cnt;
	u8 LastMode;
	u8 LastLineSize; 
	
}Type_OSC;
  

/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern Type_OSC Struct_OSC;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
int OS_LCD_Init(void);  
int OS_LCD_Clear(u16 color);
unsigned int OS_Point_Read(u16 x,u16 y);
unsigned int OS_TextColor_Set(u16 _color);
unsigned int OS_BackColor_Set(u16 _color);
int OS_Point_Draw(u16 x,u16 y,u16 color);
int OS_Line_Draw(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);  
int OS_Circle_Draw(u16 x, u16 y, u8 r, u8 size, u16 color);
int OS_Rect_Draw(u16 x1, u16 y1, u16 x2, u16 y2, u8 size, u16 color); 
int OS_Picture_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,const u8 *pic);  
 
int OS_String_Show(u16 x, u16 y, u8 size, u8 mode, char *str);
int OS_Num_Show(u16 x,u16 y,u8 size,u8 mode,double num,char* format);
int OS_Wave_Draw(Type_OSC *Struct_OSC,u8 mode);
int OS_Wave_Unite(Type_OSC *Struct_OSC_Source, Type_OSC *Struct_New);


#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/













