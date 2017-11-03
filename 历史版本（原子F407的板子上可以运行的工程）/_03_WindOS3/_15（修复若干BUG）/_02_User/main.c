/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : main.c
* @Description : None	
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/ 

/* 头文件包含 ----------------------------------------------------------------*/  
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
	/* WindOS初始化 -------------------------------*/	 					
	OS_Init();  															
																				
	/* 程序注册 -----------------------------------*/	      	 
	OSTask_Creat(&App_LED);								
	OSTask_Creat(&APP_TouchDraw); 							
	OSTask_Creat(&App_Read_ScreenID);					
	OSTask_Creat(&App_CPU_Show);	 						
	OSTask_Creat(&APP_Flash);				
	OSTask_Creat(&App_Image);
	
	//测试桌面图标及翻页功能
	OSTask_Creat(&App_LED);								
	OSTask_Creat(&APP_TouchDraw); 							
	OSTask_Creat(&App_Read_ScreenID);					
	OSTask_Creat(&App_CPU_Show);	 						
	OSTask_Creat(&APP_Flash);				
	OSTask_Creat(&App_Image);	
	OSTask_Creat(&App_Image);	 
	OSTask_Creat(&App_LED);								
	OSTask_Creat(&APP_TouchDraw); 							
	OSTask_Creat(&App_Read_ScreenID);					
	OSTask_Creat(&App_CPU_Show);	 						
	OSTask_Creat(&APP_Flash);				
	OSTask_Creat(&App_Image);
	OSTask_Creat(&App_Image);	 
	OSTask_Creat(&App_LED);								
	OSTask_Creat(&APP_TouchDraw); 							
	OSTask_Creat(&App_Read_ScreenID);						
	OSTask_Creat(&App_CPU_Show);	 						
	OSTask_Creat(&APP_Flash);				
	OSTask_Creat(&App_Image); 
	
	/* WindOS空闲程序 -----------------------------*/  		
	while(1) OSThread_Free();   			
			 
}	
	
	
	
	
	
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





