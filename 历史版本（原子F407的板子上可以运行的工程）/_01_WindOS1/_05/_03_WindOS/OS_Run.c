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
extern Type_Addr AppHead;
Type_Addr *pAppRun = &AppHead;

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Run()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Run(void)
{
	while(1)
	{
		if(pAppRun ->next == NULL) pAppRun = &AppHead;
		else 
		{
			pAppRun = pAppRun ->next;  
			if(pAppRun ->loading == 0) 
			{
				if(pAppRun ->state == STATE_ACTIVE) //�ж��Ƿ񼤻�
				{
					pAppRun ->loading = pAppRun ->reload; //����
					pAppRun ->AppFun(); //���г��� 
				}
				else if(pAppRun ->state == STATE_ONE_OFF) //�ж���һ���Եĳ���
				{
					pAppRun ->AppFun(); //���г��� 
					OSTask_Remove(pAppRun ->AppFun);
				}
				                      
			}
			else
			{ 
				pAppRun ->loading --; 
			}
		}
		OSTask_Show();
	}
	
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





