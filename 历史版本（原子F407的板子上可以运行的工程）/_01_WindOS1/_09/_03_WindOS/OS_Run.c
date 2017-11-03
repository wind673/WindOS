/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Run.h" 
																		
/* ˽�к궨�� ----------------------------------------------------------------*/
											
/* ˽�У���̬���������� ------------------------------------------------------*/
										
/* ȫ�ֱ������� --------------------------------------------------------------*/

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
* @FunctionName  : OSFree_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : �����߳�
------------------------------------------------------------------------------*/
void OSThread_Free(void)
{
	 
	while(1)
	{  
		TIM_GetCounter(TIM2);
		if(FreeRun ->next == NULL) FreeRun = &FreeHead;
		else 
		{
			FreeRun = FreeRun ->next; 
					
			if(FreeRun ->loading == 0 ) 
			{
				if(FreeRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�   
				{ 
					FreeRun ->AppFun(); //���г���  
					FreeRun ->loading = FreeRun ->reload;		
				}
				else if(FreeRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���  
				{ 
					FreeRun ->AppFun(); //���г���   
					OSTask_Remove(FreeRun ->AppFun);   
				}
				else if(FreeRun ->state == OS_STATE_SUSPEND)  
				{	
					FreeRun ->state = OS_STATE_ACTIVE;//���¼���
					FreeRun ->loading = FreeRun ->reload;		 
				}  
			
			} 
		   			
		}
		
	FreeRun ->loading --;	
	} 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSPrimary_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : ���߳�
------------------------------------------------------------------------------*/
void OSThread_Primary(void)
{
	Type_Addr *temp = &PrimaryHead;
	if(PrimaryRun ->next == NULL)PrimaryRun = &PrimaryHead;
	else
	{
		
		PrimaryRun = PrimaryRun ->next;  
		if(PrimaryRun ->loading == 0) 
	    {
			if(PrimaryRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				PrimaryRun ->AppFun(); //���г���    
				PrimaryRun ->loading = PrimaryRun->reload;
			}   
			else if(PrimaryRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���
			{
				PrimaryRun ->AppFun(); //���г��� 
				OSTask_Remove(PrimaryRun ->AppFun);   
				 
			}  
			else if(PrimaryRun ->state == OS_STATE_SUSPEND) //�ж���һ���Եĳ���
			{
				PrimaryRun ->state = OS_STATE_ACTIVE; 	   
			}
			                
		}
		 
	} 
	
	while(1)
	{
		if(temp ->next == NULL) return;
		temp = temp ->next;
		if(temp ->loading != 0) temp ->loading --;   
		  
	}
		 
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSPrimary_Thread()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : ϵͳ�߳�
------------------------------------------------------------------------------*/
void OSThread_System(void)
{
	Type_Addr *temp = &SystemHead;
	if(SystemRun ->next == NULL)SystemRun = &SystemHead;
	else
	{
		
		SystemRun = SystemRun ->next;  
		if(SystemRun ->loading == 0) 
	    {
			if(SystemRun ->state == OS_STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				SystemRun ->AppFun(); //���г���    
				SystemRun ->loading = SystemRun->reload;
			}   
			else if(SystemRun ->state == OS_STATE_ONE_OFF) //�ж���һ���Եĳ���
			{
				SystemRun ->AppFun(); //���г��� 
				OSTask_Remove(SystemRun ->AppFun);   
				 
			}  
			else if(SystemRun ->state == OS_STATE_SUSPEND) //�ж���һ���Եĳ���
			{
				SystemRun ->state = OS_STATE_ACTIVE; 	   
			}
			                
		}
		 
	} 
	
	while(1)
	{
		if(temp ->next == NULL) return;
		temp = temp ->next;
		if(temp ->loading != 0) temp ->loading --;   
		  
	}
	
	
	
	
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
	unsigned long int _RAM = 0;
	static long int _cnt = 0;
	unsigned char _line = 0;
    int *_RAM_Test = (int*)malloc(sizeof(int)); 
	Type_Addr *temp =NULL;
	
	_cnt++; 
	Temp_color = TextColor_Set(RED); 
    Show_String(0,50+FONT_3*3,(u8*)"OSTask_Show",FONT_3);  
	TextColor_Set(GREEN);	
	LCD_ShowNum(150,60+FONT_3*3,_cnt,7,FONT_2); 
	
	
	/* RAM ��ʾ ------------------------------------*/
	TextColor_Set(YELLOW);
	Show_String(0,FONT_1,(u8*)"RAM:",FONT_1); 
	_RAM = 0x20000 - ((unsigned long int)&_RAM_Test - 0x20000000);
	LCD_ShowDecim(FONT_1*5,FONT_1,(double)_RAM/0x20000,2,5,FONT_1);  
	Show_String(FONT_1*8,FONT_1,(u8*)"%",FONT_1); 
	
	Show_String(0,FONT_1*2,(u8*)"RAM_Used:",FONT_1); 
	_RAM = (unsigned long int)&_RAM_Test - 0x20000000;
	LCD_ShowNum(FONT_1*5,FONT_1*2,_RAM,6,FONT_1); 
	
	Show_String(0,FONT_1*3,(u8*)"RAM_All:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*3,(unsigned long int)0x20000,6,FONT_1); 
	
	Show_String(0,FONT_1*4,(u8*)"RAM_Start:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*4,(unsigned long int)0x20000000,9,FONT_1); 
	
	Show_String(0,FONT_1*5,(u8*)"RAM_Now:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*5,(unsigned long int)&_RAM_Test,9,FONT_1); 
	
	/* ������ʾ ------------------------------------*/
	temp = &FreeHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		Show_String(150,FONT_1*_line++,temp ->name,FONT_1);          
	}
	temp = &PrimaryHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		Show_String(150,FONT_1*_line++,temp ->name,FONT_1);          
	}
	temp = &SystemHead;
	while(1)
	{
		if(temp ->next == NULL) break;
		temp = temp ->next;
		Show_String(150,FONT_1*_line++,temp ->name,FONT_1);       
	}
	
	TextColor_Set(Temp_color); 
	
	free(_RAM_Test);
	return 0;
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





