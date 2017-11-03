/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : My_Library.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "My_Library.h" 
#include "OS_StartFile.h" 


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : main()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
int main()
{
	 
	/* WindOS初始化 ---------------------------------*/			
	OS_Init();  			
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)*1000000000); //申请内存 	
	
	/* 空闲程序注册 ---------------------------------*/	  
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
	
	 
	/* 主程序注册 ----------------------------------*/	
	OSTask_Creat(LED_Flash,(u8*)"LED_Flash.wos",300,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);   
	OSTask_Creat(APP_TouchDraw,(u8*)"APP_TouchDraw.wos",4,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);    
	OSTask_Creat(OSTask_Show,(u8*)"OSTask_Show.wos",200,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);
	
	
	/* 系统程序注册 --------------------------------*/	
	OSTask_Creat(APP_TouchScan,(u8*)"APP_Touch.wos",3,OS_STATE_ACTIVE,OS_THREAD_SYSTEM); 
    
 	 
	
	/* WindOS空闲程序 -----------------------------*/  		
	OSThread_Free();   
											
return 0; 
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





