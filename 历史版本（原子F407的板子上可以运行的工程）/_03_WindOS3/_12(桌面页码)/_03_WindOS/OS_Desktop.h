/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Desktop.h
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
  
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __OS_DESKTOP_H	
#define __OS_DESKTOP_H 	

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define USE_DESKBACK   1
#define DESK_IMAGE       gImage_Smile

typedef unsigned int(CreatFun)(void); //App ������������� unsigned int XXX(void)  
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
	Type_AppList *App;		
	struct __ICO *next;		
	u16 Nox;//ͼ�����	
	u16 Page;
}Type_Ico;

typedef struct __Taskbar
{
	u8 activate_point;		//״̬�������
	u16 dynamic_Y;    //����״̬�µ� ����λ��
	u8 activate_state;  //�Ƿ�Ϊ����״̬
	u8  run_state; 		//״̬������״̬
}TypeTaskbar;

typedef struct __Desk
{
	signed char CurrentPage;
	signed char FirstPage;
	signed char EndPage;   
}TypeDesk;


/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_Ico *AppRunning;	
extern Type_AppList App_Taskbar;		
extern TypeDesk DeskPage;
extern unsigned DESK_IMAGE[153608];
	
	
/* ����ע��� ------------------------------*/		
extern Type_AppList OS_Desktop;	 
extern Type_AppList OS_AppIn;
extern Type_AppList OS_AppOut;
extern Type_AppList OS_IcoShow; 
	
	
	
/* ȫ�ֺ������� --------------------------------------------------------------*/  
unsigned char OS_IcoCreat(Type_AppList *_App,u16 _TextColor,u16 _BackColor);


//u16 Taskbar_Draw(u16 Bar_Y);


 
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/

 


