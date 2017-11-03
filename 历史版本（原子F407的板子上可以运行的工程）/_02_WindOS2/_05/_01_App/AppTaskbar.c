/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : AppTaskbar.c
* @Description : None
* @Date        : 2016/3/22
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "AppTaskbar.h" 
#include "OS_StartFile.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/
static u16 Taskbar_Draw(u16 Bar_Y);

/* ȫ�ֱ������� --------------------------------------------------------------*/
TypeTaskbar Taskbar = {BAR_UP,0,BAR_FREE,BAR_FIRST};

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------  
* @FunctionName  : AppTaskbar()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int AppTaskbar(void)  
{ 
	 unsigned int Temp_color;  
	 
	 Temp_color = OS_TextColor_Set(WHITE);	  
	 if(Taskbar.run_state == BAR_FIRST){ LCD_Fill(0,0,OS_LCD_WHITH,FONT_1,BLACK); Taskbar.run_state = BAR_CLOSE;}
	 
	 if(TouchPoint._state != 0)  //�ж��Ƿ�����Ļ
	 {
		if(Taskbar.activate_point == BAR_UP) //�жϼ����λ��
		if(TouchPoint._Y < FONT_3) Taskbar.activate_state = BAR_ACTIVATE;
		
		if(Taskbar.activate_point == BAR_DOWN) 
		{
			if(TouchPoint._Y > OS_LCD_LENTH - FONT_3*3) Taskbar.activate_state = BAR_ACTIVATE;	  
		}		
	 } 
	 else Taskbar.activate_state = BAR_CLOSE;  
	 
	  	  
	 if(Taskbar.activate_state == BAR_ACTIVATE) //�ж��û��Ƿ��¼���� 	
	 {
		Taskbar.dynamic_Y = Taskbar_Draw(TouchPoint._Y);   
		Taskbar.run_state = BAR_RUNNING;	
	 }	           
	 else  
	 {
		if(Taskbar.run_state == BAR_RUNNING)  
		{
			if(Taskbar.dynamic_Y > OS_LCD_LENTH/2)
			{			
				Taskbar.activate_point = BAR_DOWN; 
				Taskbar_Draw(OS_LCD_LENTH); 
			}
			else 
			{
				Taskbar.activate_point = BAR_UP;     
				Taskbar_Draw(FONT_1);
			}
			Taskbar.run_state = BAR_CLOSE; //���ֺ� �����жϣ�������Ӧ�Ĵ���
			 
		}
	 }
		
	  
	 OS_TextColor_Set(Temp_color);		
	 return 0;
}

/**----------------------------------------------------------------------------  
* @FunctionName  : TaskbarY()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : None
------------------------------------------------------------------------------*/
static u16 Taskbar_Draw(u16 Bar_Y)  
{
	LCD_Fill(0,0,OS_LCD_WHITH,Bar_Y+1,BLACK); 
	LCD_Fill(0,Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,WHITE); 
	
	return Bar_Y;
}
	

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





