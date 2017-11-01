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
/* App --------------------------------------------*/
Type_Addr FreeHead = {0}; //������г������е�ͷ֡   
Type_Addr PrimaryHead = {0}; //�������������е�ͷ֡ 
Type_Addr SystemHead= {0}; //����ϵͳ�������е�ͷ֡ 

Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  
Type_Addr *SystemTemp = &SystemHead;  

Type_Addr *FreeRun = &FreeHead;
Type_Addr *PrimaryRun = &PrimaryHead;
Type_Addr *SystemRun = &SystemHead;

/* RAM --------------------------------------------*/
unsigned long int OS_RAM = 0; //RAM����

/* RAM --------------------------------------------*/
unsigned long int OS_CPU = 0; //CPU��ʱ
unsigned char OS_CPU_Flag = 0; //RAM����

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Init()     
* @Description   : WinOS��ʼ�� 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Init(void)
{		 
	/* WindOS��ʼ�� ------------------------------------*/  
												
	/* Ӳ����ʼ�� --------------------------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//8����ռ�ȼ� 2����Ӧ���ȼ�        
	delay_init(168);	    //��ʼ����ʱ����  						
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200					
	TFT_Init(); 																	
	RCC_Configuration();    //��ʼ��ʱ��	 
	My_GPIO_Init();	
	TIM2_Config(); //ϵͳʱ��
	TIM3_Config(); //���߳�
	TIM4_Config(); //ϵͳ�߳�
	tp_dev.init(); //��������ʼ��
	Show_String(0,0,"Drive_Init is OK!",FONT_1); //��ʶOK	
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSCPU_Monitor()     
* @Description   : WinOS CPU��⣨������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int OSCPU_Monitor(void) 
{
	unsigned long int _CPU_Time = 0; 
    unsigned long int _CPU_Cnt = 0;
	
	//if(OS_CPU_Flag) return 1;
	
	if(TIM_GetCounter(TIM2) > 0xfff0ffff) TIM_SetCounter(TIM2,0);
	_CPU_Time = TIM_GetCounter(TIM2); 
	_CPU_Cnt = 0;
	while( TIM_GetCounter(TIM2)<_CPU_Time+1000 ) _CPU_Cnt++;   
	OS_CPU = 10000-_CPU_Cnt;
	
	//LCD_ShowDecim(0,FONT_2*5,_CPU_Cnt,2,12,FONT_2);  
	
	OS_CPU_Flag = 1;	 
	return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Show()     
* @Description   : WinOS������ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    	
*
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned int OSTask_Show(void) 
{
	unsigned int Temp_color;  
	static long int _cnt = 0;
	unsigned char _line = 0;  

	Type_Addr *temp =NULL;  
	_cnt++; 
	Temp_color = TextColor_Set(YELLOW);  
	LCD_ShowDecim(0,FONT_3*6,_cnt,1,10,FONT_3); 
	/* CPU ��ʾ ------------------------------------*/  
	Show_String(0,FONT_2,(u8*)"CPU:",FONT_2); 
	Show_String(FONT_2*5,FONT_2,(u8*)"%",FONT_2);  
	LCD_ShowDecim(FONT_2*2,FONT_2,(double)OS_CPU/100.0f,2,5,FONT_2); 
	OS_CPU_Flag = 0;
	/* ������ʾ ------------------------------------*/
	temp = &FreeHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		TextColor_Set(GREEN); 
		temp = temp ->next;
		Show_String(120,FONT_1*_line++,temp ->name,FONT_1);          
	}
	temp = &PrimaryHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		TextColor_Set(YELLOW); 
		temp = temp ->next;
		Show_String(120,FONT_1*_line++,temp ->name,FONT_1);          
	}
	temp = &SystemHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		TextColor_Set(RED); 
		temp = temp ->next;
		Show_String(120,FONT_1*_line++,temp ->name,FONT_1);       
	}
	
	TextColor_Set(Temp_color); 
	
	return 0;
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




