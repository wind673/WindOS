/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_CPUMonitor.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "App_CPUMonitor.h" 


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/
static unsigned int Task_Show(void);

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ������� --------------------------------------------------------------*/
extern u16 DeskSourceColor[4];

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : CPU_Show_Main()     
* @Description   : WinOSϵͳ��ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    	
*
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned int CPU_Show_Main(void) 
{  
	unsigned long int _CPU_Time = 0,_CPU_Cnt = 0,OS_CPU = 0;  
	
	/* ˢ�±��� ------------------------------------*/ 		
	OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_WEAKNESS,NULL);
	
	/* CPU ��� ------------------------------------*/  
	if(TIM_GetCounter(TIM2) > 0xfff0ffff) TIM_SetCounter(TIM2,0);	
	_CPU_Time = TIM_GetCounter(TIM2); 	
	_CPU_Cnt = 0;		
	while( TIM_GetCounter(TIM2)<_CPU_Time + 100000 ) _CPU_Cnt++;  //���100ms�����еļ����� 
	OS_CPU = (1.0f - ((double)_CPU_Cnt/884000.0f))*10000;   	
	
	/* ���� ��ʾ -----------------------------------*/  
	if(OS_Point_Read(FONT_3*6,FONT_3*12) != GRAY) 
	{
		OS_Rect_Draw(FONT_1/2+1,FONT_3+1,FONT_3*6+1,FONT_3*12+1,0,BLACK);
		OS_Rect_Draw(FONT_1/2+2,FONT_3+2,FONT_3*6+2,FONT_3*12+2,0,BLACK);	
		OS_Rect_Draw(FONT_1/2,FONT_3,FONT_3*6,FONT_3*12,1,GRAY); 
		OS_String_Show(FONT_3,FONT_3+3,(u8*)"�����б�",FONT_3,0);  
		
	}		
	
	OS_BackColor_Set(GRAY);															
	/* CPU ��ʾ ------------------------------------*/  
	OS_String_Show(FONT_1*4,FONT_3*11,(u8*)"CPU:",FONT_1,1); 	
	OS_String_Show(FONT_1*9,FONT_3*11,(u8*)"%",FONT_1,1);  
	OS_Decim_Show(FONT_1*6,FONT_3*11,OS_CPU/100.0f,2,5,FONT_1,1);   
	Task_Show();					
					
	return 0; 		
}  																	
											
														
														
unsigned int CPU_Show_Back(void) 		
{ 
	u16 Color = OS_Point_Read(OS_LCD_WHITH/2,FONT_1/2); 
	unsigned long int _CPU_Time = 0,_CPU_Cnt = 0,OS_CPU = 0;   
	OS_TextColor_Set(~Color);	
	OS_BackColor_Set(Color);	
	 
	/* CPU ��� ------------------------------------*/  						
	if(TIM_GetCounter(TIM2) > 0xfff0ffff) TIM_SetCounter(TIM2,0);						
	_CPU_Time = TIM_GetCounter(TIM2); 								
	_CPU_Cnt = 0;					
	while( TIM_GetCounter(TIM2)<_CPU_Time + 100000 ) _CPU_Cnt++; //���100ms�����еļ����� 
	OS_CPU = (1.0f - ((double)_CPU_Cnt/884000.0f))*10000;   
												
	/* CPU ״̬����ʾ ------------------------------------*/  
	OS_String_Show(0,0,(u8*)"CPU:",FONT_1,1); 	
	OS_String_Show(FONT_1*5,0,(u8*)"%",FONT_1,1);  
	OS_Decim_Show(FONT_1*2,0,OS_CPU/100.0f,2,5,FONT_1,1);   
	//OSTask_Show();			
	
	return 0; 												
}  										
													
unsigned int CPU_Show_Start(void)		
{		 
	OS_Clear_Y(FONT_1,1,NULL); //���� 
	 
	return 0;	
}				
					
unsigned int CPU_Show_End(void)		
{		
	
	OS_Clear_Y(FONT_1,1,NULL); //����
	return 0;	 
}					
				
Type_AppList App_CPU_Show = {CPU_Show_Main,CPU_Show_Back,CPU_Show_Start,CPU_Show_End, \
							OS_STATE_CLOSE_ON,OS_THREAD_FREE, \
							(u8*)"CPU",10,USE_OS_ICO};			
												
									


							
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Show()     
* @Description   : WinOS������ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    	
*
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
static unsigned int Task_Show(void) 	
{ 			
	unsigned char _line = 1;  					
	Type_AppList *temp = &AppHead;   
	/* ������ʾ ------------------------------------*/ 
	while(1)			
	{ 
		if(temp ->next == NULL) break;			
		temp = temp ->next;		
		if(temp ->state == OS_STATE_SUSPEND_ON || temp ->state == OS_STATE_ACTIVE_ON)	
		{	 
			if(temp ->thread == OS_THREAD_FREE) OS_TextColor_Set(OS_COLOR_FREE);   			
			else if(temp ->thread == OS_THREAD_PRIMARY) OS_TextColor_Set(OS_COLOR_PRIMARY);		
			else if(temp ->thread == OS_THREAD_SYSTEM) OS_TextColor_Set(OS_COLOR_SYSTEM); 		
			else OS_TextColor_Set(OS_COLOR_OTHER);	 			
			OS_String_Show(20,FONT_3*2+FONT_2*_line++,temp ->name,FONT_2,1);     			
		}	
			
			
	}
	 	
	return 0;	
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





