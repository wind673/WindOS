/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Button.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __OS_BUTTON_H
#define __OS_BUTTON_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
#define BUTTON_UP					1
#define BUTTON_DOWN 				2
#define BUTTON_DOWNED 				3 
#define BUTTON_DISABLED 			4
#define BUTTON_CLOSE				5
#define BUTTON_DEFAULT 				BUTTON_UP

#define BUTTON_VALID 				1
#define BUTTON_INVALID 				0


/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct __OS_Button
{
	u16 x1;			
	u16 y1;			
	u16 x2;			
	u16 y2;			
	u16 color;  
	u8 value; 	//�ð�ť��ֵ
	u8 state;	//��ť��״	
	u8 LastState; //�����Զ������״̬
	u8 *str;		
	u16 fontsize;	 
	struct __OS_Button *next;		
	
}Type_Button;
	
/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern Type_AppList OS_Button_Scan;


/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Button_Creat(Type_Button *pStruct,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color);
void OS_Button_Alter(Type_Button *ButtonStruct,u8 state,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color);
void OS_Button_Show(Type_Button *ButtonStruct,u8 state);      
void OS_Button_LastClear(Type_Button *ButtonStruct);
u8 OS_Button_State(Type_Button *ButtonStruct);    



#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/








