/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Appdesktop.h
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APPDESKTOP_H
#define __APPDESKTOP_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
typedef unsigned int(CreatFun)(void); //App ������������� unsigned int XXX(void)  

/* �ṹ������ ----------------------------------------------------------------*/ 
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

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_Ico *AppRunning;
 
/* ȫ�ֺ������� --------------------------------------------------------------*/  
unsigned int App_Desktop(void);
unsigned int OS_Ico_Show(void); 
unsigned int App_In(void);
unsigned int App_Out(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



