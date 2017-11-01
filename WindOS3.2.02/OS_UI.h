/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_UI.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (TM4C1294NCPDT)
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
#define OS_LCD_LENTH  	480	 //�߶�	
#define OS_ICO_COLOUR_BACK  GREEN //ϵͳ���� ͼ�걳����ɫ
#define OS_ICO_COLOUR_TEXT  WHITE  //ϵͳ���� ͼ��������ɫ
		
#define FONT_1   12				
#define FONT_2   16			
#define FONT_3   24 
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


/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/   

/* ȫ�ֺ������� --------------------------------------------------------------*/ 
void OS_UI_Init(void);
void OS_Clear(void);
//void OS_String_Show(u16 x, u16 y, u8 *str);
void OS_Decim_Show(u16 x,u16 y,double num,u8 NumLenth,u8 DecimLenth); 
void OS_Num_Show(u16 x,u16 y,signed long int num,u8 NumLenth);
void OS_String_Show(u16 x, u16 y, char *str);

#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/














