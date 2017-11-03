/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_StartFile.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "My_Library.h" 
#include "OS_StartFile.h"


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
u32 OS_Msg = NULL;	


/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Init()     
* @Description   : WinOS��ʼ�� 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Init(void)
{		 
	static unsigned char _line =0;
	/* WindOS��ʼ�� ------------------------------------*/  
	OSTask_Creat(&APP_TouchScan); 	  			
	OSTask_Creat(&App_Taskbar);  				
	OSTask_Creat(&OS_Desktop); 			
	
	/* Ӳ����ʼ�� --------------------------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//8����ռ�ȼ� 2����Ӧ���ȼ�        
	delay_init(168);	    //��ʼ����ʱ����  						
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200	
	
	LCD_Init();					//LCD��ʼ��  
    font_init();//����ֿ�
	LCD_Clear(BLACK);//����	
	OS_BackColor_Set(BLACK);
	OS_TextColor_Set(WHITE);  
	OS_String_Show(0,FONT_1*_line++,(u8*)"TFT_Init is OK!",FONT_1); 
	
	RCC_Configuration();  OS_String_Show(0,FONT_1*_line++,(u8*)"RCC_Configuration is OK!",FONT_1);   //��ʼ��ʱ��	 
	My_GPIO_Init();	 OS_String_Show(0,FONT_1*_line++,(u8*)"My_GPIO_Init is OK!",FONT_1); 
	TIM2_Config(); 	 OS_String_Show(0,FONT_1*_line++,(u8*)"TIM2_Config is OK!",FONT_1); 
	TIM3_Config(); 	 OS_String_Show(0,FONT_1*_line++,(u8*)"TIM3_Config is OK!",FONT_1); //���߳�
	TIM4_Config();   OS_String_Show(0,FONT_1*_line++,(u8*)"TIM4_Config is OK!",FONT_1); //ϵͳ�߳�
	tp_dev.init();   OS_String_Show(0,FONT_1*_line++,(u8*)"LCD_Touch is OK!",FONT_1); //��������ʼ��
	 
	LCD_Clear(0xafff);		
	OS_TextColor_Set(BLACK); 		
	OS_BackColor_Set(0xafff);			
}
		
			
/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()     
* @Description   : WinOSus��ʱ���� 
* @Data          : 2016/3/19		
* @Explain       : ���� ��_us = ��ʱʱ��   
------------------------------------------------------------------------------*/	
void OSdelay_us(unsigned long int _us)    
{   
	unsigned long int _TimeNow = TIM_GetCounter(TIM2);
  	if(_TimeNow > 0xfff0ffff) {TIM_SetCounter(TIM2,0);_TimeNow = 0; }
	
	while(TIM_GetCounter(TIM2) -_TimeNow < _us); 
		
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()     
* @Description   : WinOSus��ʱ���� 
* @Data          : 2016/3/19		
* @Explain       : ���� ��_ms = ��ʱʱ��   
------------------------------------------------------------------------------*/	
void OSdelay_ms(unsigned long int _ms)    
{   
	unsigned long int _TimeNow = TIM_GetCounter(TIM2);
	_ms*=1000;
  	if(_TimeNow > 0xfff0ffff) {TIM_SetCounter(TIM2,0);_TimeNow = 0; }
	
	while(TIM_GetCounter(TIM2) -_TimeNow < _ms); 
		
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_s()     
* @Description   : WinOSus��ʱ���� 
* @Data          : 2016/3/19		
* @Explain       : ���� ��_s = ��ʱʱ��   
------------------------------------------------------------------------------*/	
void OSdelay_s(unsigned long int _s)    
{   
	OSdelay_ms(_s*1000); 
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





