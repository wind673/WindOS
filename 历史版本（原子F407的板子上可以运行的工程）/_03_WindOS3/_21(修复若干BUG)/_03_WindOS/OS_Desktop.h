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
#define USE_DESKBACK  		 1   //ʹ�����汳��
#define DESK_IMAGE      	 gImage_Smile

#define USE_OS_ICO	 		 1	 //ʹ��ͼ��
#define NO_USE_OS_ICO	  	 0	 //��ʹ��ͼ��

#define ICO_UP				 1	 //ͼ��û����
#define ICO_DOWN	  		 2	 //ͼ�걻����

/* ����ˢ�¼��� ----------------------------------------*/
#define DESK_REFRESH_1	  	 1,FONT_1+3	  					
#define DESK_REFRESH_2	  	 OS_LCD_WHITH - 1,FONT_1+3	 
#define DESK_REFRESH_3	  	 1,OS_LCD_LENTH - 1	 
#define DESK_REFRESH_4	  	 OS_LCD_WHITH - 1,OS_LCD_LENTH - 1	 


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
	const unsigned char *Ico;	
	const unsigned char *IcoDown;
	u8 state;
	u8 value;
	u8 LastState;
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
extern TypeDesk DeskPage;
extern unsigned DESK_IMAGE[153608];
	
	
/* ����ע��� ------------------------------*/		
extern Type_AppList OS_DesktopInit;	 
extern Type_AppList OS_AppIn;
extern Type_AppList OS_AppOut;
extern Type_AppList OS_DesktopShow;
extern Type_AppList OS_Ico_Scan;	
extern Type_AppList OS_Taskbar_Show;	
extern u16 DeskSourceColor[4]; 	

/* ȫ�ֺ������� --------------------------------------------------------------*/  
unsigned char OS_IcoCreat(Type_AppList *_App,u16 _TextColor,const unsigned char *Ico,const unsigned char *IcoDown);
u8 Ico_State(Type_Ico *IcoStruct);
void Ico_LastClear(Type_Ico *IcoStruct);



//u16 Taskbar_Draw(u16 Bar_Y);


 
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/

 


