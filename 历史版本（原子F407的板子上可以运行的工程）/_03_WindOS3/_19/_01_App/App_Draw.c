/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Draw.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
#include "App_Draw.h"  

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ�����д --------------------------------------------------------------*/

	
/**----------------------------------------------------------------------------  
* @FunctionName  : APP_TouchDraw()     
* @Description   : ����
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int TouchDraw_Main(void)  
{  
	unsigned int i = 0;
	 
	/* ������Ļ��� ----------------------------*/
	for(i=0;i<TouchPoint._LastCNT;i++)  
	{
		if(TouchPoint._LastBuffX[i] != 0xffff && TouchPoint._LastBuffY[i] != 0xffff)
		{			 
			OS_TextColor_Set(~OS_Point_Read(TouchPoint._LastBuffX[0],TouchPoint._LastBuffY[0]));  
			OS_Circle_Draw(TouchPoint._LastBuffX[i],TouchPoint._LastBuffY[i],5,1,TOUCH_COLOR);  
		}			 
	}
	
	/* ����������� ----------------------------*/
	TouchPoint._LastBuffX[TouchPoint._LastCNT] = 0xffff;
	TouchPoint._LastBuffY[TouchPoint._LastCNT] = 0xffff;
	while(TouchPoint._LastCNT) 
	{
		TouchPoint._LastCNT --;
		TouchPoint._LastBuffX[TouchPoint._LastCNT] = 0xffff;
		TouchPoint._LastBuffY[TouchPoint._LastCNT] = 0xffff;
	}	 
	
	return 0;	 
}
 

unsigned int TouchDraw_Start(void)  
{ 
	OS_Clear_Y(FONT_1,OS_CLEAR_PURE|OS_CLEAR_CONSTRAINT,WHITE);	
	
	/* ��Ļɨ��ʱ����� ------------------------*/
	OSTask_Alter(&Drive_TouchScan,NULL,2,NULL,NULL);
	
	/* ����������� ----------------------------*/
	TouchPoint._LastBuffX[TouchPoint._LastCNT] = 0xffff;
	TouchPoint._LastBuffY[TouchPoint._LastCNT] = 0xffff;
	while(TouchPoint._LastCNT) 
	{
		TouchPoint._LastCNT --;
		TouchPoint._LastBuffX[TouchPoint._LastCNT] = 0xffff;
		TouchPoint._LastBuffY[TouchPoint._LastCNT] = 0xffff;
	}
		
	return 0;
}


unsigned int TouchDraw_End(void)  
{
	/* ��Ļɨ��ʱ����� ------------------------*/
	if(APP_TouchDraw.state == OS_STATE_CLOSE) OSTask_Alter(&Drive_TouchScan,NULL,TOUCH_SCAN_SPEED,NULL,NULL); 
	 
	return 0;
}



	
Type_AppList APP_TouchDraw = {TouchDraw_Main,TouchDraw_Main,TouchDraw_Start,TouchDraw_End, \
							  OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
							  (u8*)"����",TOUCH_SCAN_SPEED,USE_OS_ICO};  

							  
						
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





