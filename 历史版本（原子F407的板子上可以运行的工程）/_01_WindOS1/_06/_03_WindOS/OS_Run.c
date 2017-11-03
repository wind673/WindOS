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
Type_Addr *FreeRun = &FreeHead;
Type_Addr *PrimaryRun = &PrimaryHead;


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
	TIM3_Config();									
	Show_String(0,0,"Drive_Init is OK!",FONT_1); //��ʶOK	
	
}	
			
/**----------------------------------------------------------------------------
* @FunctionName  : OSFree_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : �����߳�
------------------------------------------------------------------------------*/
void OSFree_Thread(void)
{
 
	while(1)
	{
		  
		if(FreeRun ->next == NULL) FreeRun = &FreeHead;
		else 
		{
			FreeRun = FreeRun ->next; 
					
			if(FreeRun ->loading == 0 ) 
			{
				if(FreeRun ->state == STATE_ACTIVE) //�ж��Ƿ񼤻�   
				{ 
					FreeRun ->AppFun(); //���г���  
					FreeRun ->loading = FreeRun ->reload;		
				}
				else if(FreeRun ->state == STATE_ONE_OFF) //�ж���һ���Եĳ���  
				{ 
					FreeRun ->AppFun(); //���г���   
					OSTask_Remove(FreeRun ->AppFun);   
				}
				else if(FreeRun ->state == STATE_SUSPEND)  
				{	
					FreeRun ->state = STATE_ACTIVE;//���¼���
					FreeRun ->loading = FreeRun ->reload;		 
				}  
			
			} 
			
		 FreeRun ->loading --;  				
		}
		
		
	} 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSPrimary_Thread()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : ���߳�
------------------------------------------------------------------------------*/
void OSPrimary_Thread(void)
{
	if(PrimaryRun ->next == NULL)PrimaryRun = &PrimaryHead;
	else
	{
		
		PrimaryRun = PrimaryRun ->next;  
		if(PrimaryRun ->loading == 0) 
	    {
			if(PrimaryRun ->state == STATE_ACTIVE) //�ж��Ƿ񼤻�
			{ 
				PrimaryRun ->AppFun(); //���г���    
				PrimaryRun ->loading = PrimaryRun->reload;
			}   
			else if(PrimaryRun ->state == STATE_ONE_OFF) //�ж���һ���Եĳ���
			{
				PrimaryRun ->AppFun(); //���г��� 
				OSTask_Remove(PrimaryRun ->AppFun);   
				 
			}  
			else if(PrimaryRun ->state == STATE_SUSPEND) //�ж���һ���Եĳ���
			{
				PrimaryRun ->state = STATE_ACTIVE; 	
			}
			                
		}
		PrimaryRun ->loading --;  
	   
	} 
	
	
		 
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





