/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : My_Library.c
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
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : main()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
int main()
{
	 
	/* WindOS��ʼ�� ---------------------------------*/			
	OS_Init();  			
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)*1000000000); //�����ڴ� 	
	
	/* ���г���ע�� ---------------------------------*/	  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);         
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);     
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE); 
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE); 
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);     
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);  
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE); 
	OSTask_Creat(APP_Hello,(u8*)"Hello.wos",1,OS_STATE_ACTIVE,OS_THREAD_FREE);
	
	 
	/* ������ע�� ----------------------------------*/	
	OSTask_Creat(LED_Flash,(u8*)"LED_Flash.wos",300,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);   
	OSTask_Creat(APP_TouchDraw,(u8*)"APP_TouchDraw.wos",4,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);    
	OSTask_Creat(OSTask_Show,(u8*)"OSTask_Show.wos",200,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);
	
	
	/* ϵͳ����ע�� --------------------------------*/	
	OSTask_Creat(APP_TouchScan,(u8*)"APP_Touch.wos",3,OS_STATE_ACTIVE,OS_THREAD_SYSTEM); 
    
 	 
	
	/* WindOS���г��� -----------------------------*/  		
	OSThread_Free();   
											
return 0; 
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





