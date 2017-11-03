/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Touch.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_TOUCH_H
#define __DRIVE_TOUCH_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define TOUCH_BUFF_SIZE  		100
#define TOUCH_COLOR				DARKBLUE         
#define TOUCH_SCAN_SPEED 		20  //ɨ���ٶ�
#define TOUCH_SLIP_RESPONSE 	((OS_LCD_WHITH+OS_LCD_LENTH)/20) //������Ӧ����


#define TOUCH_SLIP_LEFT		(0x01<<0) //��	
#define TOUCH_SLIP_RIGHT	(0x01<<1) //�һ�	
#define TOUCH_SLIP_UP  		(0x01<<2) //�ϻ�	
#define TOUCH_SLIP_DOWN  	(0x01<<3) //�»�	
   
   
#define TOUCH_STATE_OFF 	0  	//��������	
#define TOUCH_STATE_ON 		1   //���ڴ���	
#define TOUCH_STATE_SLIP	2   //���ڴ���	



/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct _struct_Touch
{ 
	u16 _X; //��ǰx����
	u16 _Y; //��ǰy����
	u16 _LastX; //��һ��x����
	u16 _LastY; //��һ��y����
	
	u16 _XY[TOUCH_BUFF_SIZE][2]; //��ʷ���� 
	u8  _CNT; //��ʷ��¼��
	u8  _state; //����״̬
	u8 _slip_direction; //�����ķ���    
}Type_Touch;

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_Touch TouchPoint;
extern Type_AppList APP_TouchScan;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
int Drive_Touch_Init(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



