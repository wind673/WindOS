/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : main.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
#include "OS_StartFile.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : main()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
int main()
{
	 
	/* WindOS��ʼ�� --------------------------------*/			
	OS_Init();  			
													
	/* ���г���ע�� --------------------------------*/	    	
	OSTask_Creat(OSCPU_Show,(u8*)"OSCPU_Show.wos",10,OS_STATE_ACTIVE,OS_THREAD_FREE);		
	     
	/* ������ע�� ----------------------------------*/	  
	OSTask_Creat(LED_Flash,(u8*)"LED_Flash.wos",333,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);   	
	OSTask_Creat(AppTaskbar,(u8*)"AppTaskbar.wos",100,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);   	
	 			
	/* ϵͳ����ע�� --------------------------------*/	
	OSTask_Creat(APP_TouchScan,(u8*)"APP_Touch.wos",100,OS_STATE_ACTIVE,OS_THREAD_SYSTEM);   	
	
	/* WindOS���г��� ------------------------------*/  		
	OSThread_Free();   
					
	
return 0; 
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





