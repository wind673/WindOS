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
#include "OS_StartFile.h" 
																		
/* ˽�к궨�� ----------------------------------------------------------------*/
											
/* ˽�У���̬���������� ------------------------------------------------------*/
										
/* ȫ�ֱ������� --------------------------------------------------------------*/
extern Type_Addr FreeHead;
extern Type_Addr PrimaryHead;
extern Type_Addr SystemHead;

Type_Addr *FreeRun = &FreeHead;
Type_Addr *PrimaryRun = &PrimaryHead;
Type_Addr *SystemRun = &SystemHead;


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
	TIM3_Config(); //���߳�
	TIM4_Config(); //ϵͳ�߳�
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





/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





