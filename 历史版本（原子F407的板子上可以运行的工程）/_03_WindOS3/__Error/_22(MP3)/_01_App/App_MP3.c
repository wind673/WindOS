/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_MP3.c
* @Description : None
* @Date        : 2016/3/31
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "App_MP3.h" 
#include "audioplay.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Button *Button_MP3_Play,*Button_MP3_Next,*Button_MP3_Last,*Button_MP3_State; 
u8 MP3_Button;

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : MP3()     
* @Description   : None 
* @Data          : 2016/5/7
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int MP3(void)  
{  
	 OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_WEAKNESS,NULL); 
	 OS_String_Show(60,80,(u8*)"MP3������",FONT_3,0);   
	
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
	
	/* ������ť --------------------------------*/
	Button_MP3_Play = OS_Button_Creat(FONT_3*4,FONT_3*9,(u8*)" Play ",FONT_3,GREEN);
	Button_MP3_Next = OS_Button_Creat(FONT_3*1,FONT_3*10,(u8*)" Next ",FONT_3,GREEN);  
	Button_MP3_Last = OS_Button_Creat(FONT_3*6,FONT_3*10,(u8*)" Last ",FONT_3,GREEN);  
	Button_MP3_State = OS_Button_Creat(FONT_3*4,FONT_3*5,(u8*)"��",FONT_3,RED);  
	
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
	W25QXX_Init();				//��ʼ��W25Q128
	WM8978_Init();				//��ʼ��WM8978
	WM8978_HPvol_Set(40,40);	//������������
	WM8978_SPKvol_Set(50);		//������������
	f_mount(fs[0],"0:",1); 		//����SD�� 
	 
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�   

}	

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





