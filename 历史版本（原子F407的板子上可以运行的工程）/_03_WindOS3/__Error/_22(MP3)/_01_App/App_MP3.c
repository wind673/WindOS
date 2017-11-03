/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_MP3.c
* @Description : None
* @Date        : 2016/3/31
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* 头文件包含 ----------------------------------------------------------------*/          
#include "App_MP3.h" 
#include "audioplay.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Button *Button_MP3_Play,*Button_MP3_Next,*Button_MP3_Last,*Button_MP3_State; 
u8 MP3_Button;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : MP3()     
* @Description   : None 
* @Data          : 2016/5/7
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int MP3(void)  
{  
	 OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_WEAKNESS,NULL); 
	 OS_String_Show(60,80,(u8*)"MP3播放器",FONT_3,0);   
	
	 audio_play(); 
	 return 0;
}
 

unsigned int MP3_Back(void)   
{  
	 audio_play();
	 return 0;
}

unsigned int MP3_Start(void) 
{ 
	static u8 flag = 0;
	if(flag == 0)
	{
		MP3_Init();
		flag = 1;
	}
	
	/* 创建按钮 --------------------------------*/
	Button_MP3_Play = OS_Button_Creat(FONT_3*4,FONT_3*9,(u8*)" Play ",FONT_3,GREEN);
	Button_MP3_Next = OS_Button_Creat(FONT_3*1,FONT_3*10,(u8*)" Next ",FONT_3,GREEN);  
	Button_MP3_Last = OS_Button_Creat(FONT_3*6,FONT_3*10,(u8*)" Last ",FONT_3,GREEN);  
	Button_MP3_State = OS_Button_Creat(FONT_3*4,FONT_3*5,(u8*)"●",FONT_3,RED);  
	
	return 0;
}


unsigned int MP3_End(void) 
{ 
	OS_Button_Remove(Button_MP3_Play);  
	OS_Button_Remove(Button_MP3_Next);  
	OS_Button_Remove(Button_MP3_Last);  
	OS_Button_Remove(Button_MP3_Next);  
	
	return 0;	
}

 
Type_AppList App_MP3 = {MP3,MP3_Back,MP3_Start,MP3_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"MP3",100,USE_OS_ICO,gImage_IcoMp3};			
	

void MP3_Init(void)
{
	W25QXX_Init();				//初始化W25Q128
	WM8978_Init();				//初始化WM8978
	WM8978_HPvol_Set(40,40);	//耳机音量设置
	WM8978_SPKvol_Set(50);		//喇叭音量设置
	f_mount(fs[0],"0:",1); 		//挂载SD卡 
	 
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池 
	exfuns_init();				//为fatfs相关变量申请内存   

}	

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





