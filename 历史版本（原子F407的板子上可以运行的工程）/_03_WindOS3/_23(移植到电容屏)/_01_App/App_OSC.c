/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_DMA.c
* @Description : DMA传输测试
* @Date        : 2016/05/22
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_OSC.h"   
 
/* 私有宏定义 ----------------------------------------------------------------*/
#define DEFAULT_OSC_SHIFTX 			200
#define DEFAULT_OSC_SHIFTY 			200
#define DEFAULT_OSC_ZOOMX 			1.0f
#define DEFAULT_OSC_ZOOMY			(30*3.3f/256)
#define DEFAULT_OSC_VPP 			0
#define DEFAULT_OSC_T 				0
#define DEFAULT_OSC_MAXVALUE 		0
#define DEFAULT_OSC_MINVALUE		0xffff

/* 私有（静态）函数声明 ------------------------------------------------------*/ 

/* 全局变量定义 --------------------------------------------------------------*/
u16 ADC1_Buff[ADC1_BUFF_LENTH] = {0};   
Type_OSC Struct_OSC = {DEFAULT_OSC_SHIFTX,DEFAULT_OSC_SHIFTY,DEFAULT_OSC_ZOOMX,DEFAULT_OSC_ZOOMY, \
					   DEFAULT_OSC_VPP,DEFAULT_OSC_T,DEFAULT_OSC_MAXVALUE,DEFAULT_OSC_MINVALUE };

Type_Button *Button_OSCUp,*Button_OSCDown,*Button_OSCLeft,*Button_OSCRight; 
Type_Button *Button_OSCZoomXAdd,*Button_OSCZoomYAdd,*Button_OSCZoomXReduce,*Button_OSCZoomYReduce; 
Type_AppList APP_OSC_ButtonHandle;
					  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OSC()    	 
* @Description   : None 	
* @Data          : 2016/5/22	
* @Explain       : None	
------------------------------------------------------------------------------*/ 
unsigned int OSC_Main(void)  
{	      
	if(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0) == SET) 
	{    
		OS_OSC_Draw(FONT_1,FONT_3*2,240-FONT_1,270,ADC1_Buff,ADC1_BUFF_LENTH,10.0,&Struct_OSC); 
		APP_DMA_ReStart(0);  
	}
	return 0;	
}	 

unsigned int OSC_Start(void)  
{	 
	static u8 first = 0;
	
	APP_DMA_Init();	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); //使能ADC1时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
	
	/* 创建按钮 --------------------------------*/
	Button_OSCUp = 			OS_Button_Creat(1,FONT_3*12,(u8*)"↑",FONT_3,GREEN);
	Button_OSCDown = 		OS_Button_Creat((FONT_3+6)*1,FONT_3*12,(u8*)"↓",FONT_3,GREEN); 
	Button_OSCLeft = 		OS_Button_Creat((FONT_3+6)*2,FONT_3*12,(u8*)"←",FONT_3,GREEN); 
	Button_OSCRight = 		OS_Button_Creat((FONT_3+6)*3,FONT_3*12,(u8*)"→",FONT_3,GREEN); 
	Button_OSCZoomXAdd = 	OS_Button_Creat((FONT_3+6)*4,FONT_3*12,(u8*)"十",FONT_3,GREEN);	
	Button_OSCZoomXReduce = OS_Button_Creat((FONT_3+6)*5,FONT_3*12,(u8*)"—",FONT_3,GREEN);	
	Button_OSCZoomYAdd = 	OS_Button_Creat((FONT_3+6)*6,FONT_3*12,(u8*)"∧",FONT_3,GREEN);
	Button_OSCZoomYReduce = OS_Button_Creat((FONT_3+6)*7,FONT_3*12,(u8*)"∨",FONT_3,GREEN);
	
	/* 创建按钮处理函数 ------------------------*/
	if(first == 0) {OSTask_Creat(&APP_OSC_ButtonHandle);first = 1;}
	OSTask_Alter(&APP_OSC_ButtonHandle,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 	 
	
	return 0; 
}
	
unsigned int OSC_End(void)  
{	  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,DISABLE); //失能ADC1时钟  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,DISABLE);//DMA2时钟使能 
	
	/* 删除按钮，释放内存 ---------------------*/ 
	OS_Button_Remove(Button_OSCUp);  
	OS_Button_Remove(Button_OSCDown);  
	OS_Button_Remove(Button_OSCLeft); 
	OS_Button_Remove(Button_OSCRight); 
	OS_Button_Remove(Button_OSCZoomXAdd); 							
	OS_Button_Remove(Button_OSCZoomXReduce);    			
	OS_Button_Remove(Button_OSCZoomYAdd);  
	OS_Button_Remove(Button_OSCZoomYReduce); 
	
	/* 关闭按钮处理函数 -----------------------*/
	OSTask_Alter(&APP_OSC_ButtonHandle,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE,OS_DEFAULT); 	 
	
	return 0;	
} 
Type_AppList APP_OSC = {OSC_Main,NULL,OSC_Start,OSC_End, \
							  OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
							  (u8*)"OSC",300,USE_OS_ICO,NULL};  
	
 
unsigned int OSC_ButtonHandle(void)  
{	      
	OS_Button_Show(Button_OSCUp,Button_OSCUp->state);
	OS_Button_Show(Button_OSCDown,Button_OSCDown->state);
	OS_Button_Show(Button_OSCLeft,Button_OSCLeft->state);
	OS_Button_Show(Button_OSCRight,Button_OSCRight->state);
	
	OS_Button_Show(Button_OSCZoomXAdd,Button_OSCZoomXAdd->state);
	OS_Button_Show(Button_OSCZoomXReduce,Button_OSCZoomXReduce->state);
	OS_Button_Show(Button_OSCZoomYAdd,Button_OSCZoomYAdd->state);
	OS_Button_Show(Button_OSCZoomYReduce,Button_OSCZoomYReduce->state);
	
	if(OS_Button_State(Button_OSCUp,0) == BUTTON_VALID)		Struct_OSC.ShiftY -=3;
	if(OS_Button_State(Button_OSCDown,0) == BUTTON_VALID)	Struct_OSC.ShiftY +=3;
	if(OS_Button_State(Button_OSCRight,0) == BUTTON_VALID)	Struct_OSC.ShiftX -=3;
	if(OS_Button_State(Button_OSCLeft,0) == BUTTON_VALID)	Struct_OSC.ShiftX +=3; 
	if(Struct_OSC.ShiftX < 4) Struct_OSC.ShiftX = 4; 
	if(Struct_OSC.ShiftY < 4) Struct_OSC.ShiftY = 4;
	if(Struct_OSC.ShiftY > 400) Struct_OSC.ShiftY = 400;
	if(Struct_OSC.ShiftY > 400) Struct_OSC.ShiftY = 400;
	
	if(OS_Button_State(Button_OSCZoomXAdd,0) == BUTTON_VALID)		Struct_OSC.ZoomX += 0.01f,Struct_OSC.ShiftX +=4;
	if(OS_Button_State(Button_OSCZoomXReduce,0) == BUTTON_VALID)	Struct_OSC.ZoomX -= 0.01f,Struct_OSC.ShiftX -=4;
	if(OS_Button_State(Button_OSCZoomYAdd,0) == BUTTON_VALID)		Struct_OSC.ZoomY += 0.03f,Struct_OSC.ShiftY -=4;
	if(OS_Button_State(Button_OSCZoomYReduce,0) == BUTTON_VALID)	Struct_OSC.ZoomY -= 0.03f,Struct_OSC.ShiftY +=4; 
	if(Struct_OSC.ZoomX < 0.1f) Struct_OSC.ZoomX = 0.1,Struct_OSC.ShiftX +=4; //最大10倍
	if(Struct_OSC.ZoomY < 0) Struct_OSC.ZoomY = 0,Struct_OSC.ShiftY -=4;
	if(Struct_OSC.ZoomX > 50.0f) Struct_OSC.ZoomX = 50,Struct_OSC.ShiftX -=4;
	if(Struct_OSC.ZoomY > 10.0f) Struct_OSC.ZoomY = 10,Struct_OSC.ShiftY +=4;
	 
	OS_Button_LastClear(Button_OSCUp);
	OS_Button_LastClear(Button_OSCDown);
	OS_Button_LastClear(Button_OSCRight);
	OS_Button_LastClear(Button_OSCLeft);
	OS_Button_LastClear(Button_OSCZoomXAdd);
	OS_Button_LastClear(Button_OSCZoomXReduce);
	OS_Button_LastClear(Button_OSCZoomYAdd);
	OS_Button_LastClear(Button_OSCZoomYReduce);
	
	return 0;	
}	

unsigned int OSC_ButtonHandle_End(void)  
{
	OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_CONSTRAINT,NULL); //清屏  
	return 0;
}
	
Type_AppList APP_OSC_ButtonHandle = {OSC_ButtonHandle,NULL,NULL,OSC_ButtonHandle_End, \
							  OS_STATE_ACTIVE_ON,OS_THREAD_PRIMARY, \
							  (u8*)"OSC_ButtonHandle",50,NO_USE_OS_ICO,NULL};  
																						
							  
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/


							  
							  
							  
							  
							  
							  



