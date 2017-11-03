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
																	
	/* ���г���ע��(����) ---------------------------*/	    							
	OSTask_Creat(OSCPU_Show,(u8*)"OSCPU_Show.wos",20,OS_STATE_SUSPEND,OS_THREAD_FREE);	
	
	
	/* ������ע�� ----------------------------------*/	    
	OSTask_Creat(APP_Hello,(u8*)"APP_Hello.wos",50,OS_STATE_SUSPEND,OS_THREAD_PRIMARY);
	OSTask_Creat(LED_Flash,(u8*)"LED_Flash.wos",333,OS_STATE_SUSPEND,OS_THREAD_PRIMARY);   	
	OSTask_Creat(APP_TouchDraw,(u8*)"APP_TouchDraw.wos",5,OS_STATE_SUSPEND,OS_THREAD_PRIMARY);  	
	OSTask_Creat(App_Read_ScreenID,(u8*)"App_Read_ScreenID.wos",300,OS_STATE_SUSPEND,OS_THREAD_PRIMARY);	

	
	/* ϵͳ����ע��(����) --------------------------*/										
	
	/* WindOS���г��� -----------------------------*/  		
	while(1) OSThread_Free();   										
																
			
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





