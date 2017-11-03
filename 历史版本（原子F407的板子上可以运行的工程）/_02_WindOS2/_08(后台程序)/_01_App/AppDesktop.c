/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Appdesktop.c
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/             

/* 头文件包含 ----------------------------------------------------------------*/          
#include "AppDesktop.h" 
#include "OS_StartFile.h" 

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/ 
static unsigned char OS_Ico_Creat(CreatFun *_AppAddr,CreatFun *_AppStart,CreatFun *_AppEnd,u8 *str ,u16 _TextColor,u16 _BackColor) ;

/* 全局变量定义 --------------------------------------------------------------*/
Type_Ico  Ico_Head = {NULL};
Type_Ico *Ico_Temp = &Ico_Head;
Type_Ico *AppRunning = NULL;
 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : App_Desktop()     
* @Description   : None 
* @Data          : 2016/3/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int App_Desktop(void)  
{   
	 static u8 launch_init = 0;
	 if(launch_init == 0)
	 {
		OSTask_Creat(OS_Ico_Show,(u8*)"OS_Ico_Show.wos",100,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);
		OSTask_Creat(App_In,(u8*)"App_In.wos",5,OS_STATE_ACTIVE,OS_THREAD_PRIMARY);
		OSTask_Creat(App_Out,(u8*)"App_Out.wos",5,OS_STATE_SUSPEND,OS_THREAD_PRIMARY); 
		 
		OS_Ico_Creat(LED_Flash,LED_Flash_Start,LED_Flash_End,(u8*)"LED灯",BLUE,GREEN);
		OS_Ico_Creat(APP_TouchDraw,APP_TouchDraw_Start,APP_TouchDraw_End,(u8*)"画板",BLUE,GREEN);
		OS_Ico_Creat(APP_Hello,APP_Hello_Start,APP_Hello_End,(u8*)"Hello",BLUE,GREEN);
		OS_Ico_Creat(OSCPU_Show,OSCPU_Show_Start,OSCPU_Show_End,(u8*)"CPU",BLUE,GREEN); 
		 
		launch_init = 1; 
	 }
	 
	 
	 
	 
	 return 0;
}


/**----------------------------------------------------------------------------  
* @FunctionName  : App_In()     
* @Description   : 程序入口 
* @Data          : 2016/3/24
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int App_In(void)  
{  
	 Type_Ico *temp = &Ico_Head;
	 signed int x1,x2,y1,y2,i;
	 if(TouchPoint._state == 0) return 1;
	 
	 while(temp ->next != NULL)
	 {
		  
		 temp = temp ->next;
		 if(TouchPoint._Y >= temp ->y1&&TouchPoint._Y <= temp ->y2  \
			&&TouchPoint._X >= temp ->x1&&TouchPoint._X <= temp ->x2   
		   ) 
		 {
			temp ->state = 1;  
			AppRunning = temp; 	//记录正在运行的程序		
			
			OSTask_Alter(App_In,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT); 
		    OSTask_Alter(OS_Ico_Show,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT); 
			 
			
			OSTask_Alter(App_Out,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT); 
			OSTask_Alter(temp->_AppAddr,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT);  
			
			 
			x1 = temp ->x1 + temp ->x2;
			y1 = temp ->y1 + temp ->y2; 
			x1/=2; y1/=2; 
			x2 = x1; y2 =y1; 
	  
			for(i = 0;i<OS_LCD_LENTH;i++) 
			 {
				if(x1 > 0) x1-=3;
				if(y1 > 0) y1-=5;  
				 
				if(x2 < OS_LCD_WHITH) x2 +=3;   
				if(y2 < OS_LCD_LENTH) y2 +=5;  
				if(x1 < 0) x1 = 0;if(y1 < 0) y1 = 0;
				if(x2 > OS_LCD_WHITH) x2 = OS_LCD_WHITH;
				if(y2 > OS_LCD_LENTH) y2 = OS_LCD_LENTH;  
				OS_Rect_Draw(x1,y1,x2,y2,1,BLACK);   
				if(x1 == 0&&y1 == 0&&x2==OS_LCD_WHITH&&y2 == OS_LCD_LENTH) break;
			 }
			 if(temp ->_AppStart!= NULL)	temp ->_AppStart();
		 }
		 else temp ->state = 0;  
	}
	  
	 return 0;
}


/**----------------------------------------------------------------------------  
* @FunctionName  : App_Out()     
* @Description   : 程序出口 
* @Data          : 2016/3/24
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int App_Out(void)  
{   
	u16 x1,x2,y1,y2;
	
	/* 关闭程序  -----------------------------*/
	x1 = OS_LCD_WHITH - FONT_3 - 5;
	y1 = FONT_2;
	x2 = OS_LCD_WHITH - 5;
	y2 = FONT_1+FONT_3;
	if(OS_Point_Read(x1+1,y1+1) != RED)
	OS_Button_Creat(x1,y1,x2,y2,(u8*)"×",FONT_3,RED); //画出“×” 																		
	if(TouchPoint._X > x1&&TouchPoint._X < x2&&TouchPoint._Y>y1&&TouchPoint._Y<y2) 
	{ 
		
		OSTask_Alter(AppRunning ->_AppAddr,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT);  
		OSTask_Alter(App_Out,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT); 
		
		while(TouchPoint._state);//等待触摸抬起 
		Taskbar_Draw(FONT_1); //清屏 
		if(AppRunning ->_AppEnd!= NULL)	AppRunning ->_AppEnd();  
		
		OSTask_Alter(OS_Ico_Show,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT); 
		OSTask_Alter(App_In,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT);   
		   
		return 1;
	}
	
	/* 挂起（后台）程序  -----------------------------*/
	x1 = OS_LCD_WHITH - FONT_3*3;
	y1 = FONT_2;
	x2 = OS_LCD_WHITH - FONT_3*2;
	y2 = FONT_1+FONT_3; 
	if(OS_Point_Read(x1+1,y1+1) != RED)
	OS_Button_Creat(x1,y1,x2,y2,(u8*)"—",FONT_3,RED); //画出“—”
	if(TouchPoint._X > x1&&TouchPoint._X < x2&&TouchPoint._Y>y1&&TouchPoint._Y<y2) 
	{ 
		
		//OSTask_Alter(AppRunning ->_AppAddr,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT);  
		OSTask_Alter(App_Out,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT); 
		
		while(TouchPoint._state);//等待触摸抬起 
		Taskbar_Draw(FONT_1); //清屏 
		//if(AppRunning ->_AppEnd!= NULL)	AppRunning ->_AppEnd();  
		
		OSTask_Alter(OS_Ico_Show,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT); 
		OSTask_Alter(App_In,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT);   
		   
		return 2;
	}



	
	return 0;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Ico_Creat()     
* @Description   : 显示桌面图标
* @Data          : 2016/3/23
* @Explain        
* --------------------------------------------  
* NOx 序号    str 语句   
* TextColor 文字颜色    BackColor 背景
------------------------------------------------------------------------------*/ 
static unsigned char OS_Ico_Creat(CreatFun *_AppAddr,CreatFun *_AppStart,CreatFun *_AppEnd,u8 *str ,u16 _TextColor,u16 _BackColor) 
{ 
	 u16 x1,y1,x2,y2;   
	 static u16 NOx = 0;
	
	 Type_Ico *p = (Type_Ico*)malloc(sizeof(Type_Ico));  		 
	 if(p == NULL) return 1;
	 
	 Ico_Temp -> next = p;
	 Ico_Temp = p;  
	 p ->next =NULL;
	 
	 u16 color = OS_Point_Read(x2+1,y2+1);
	 
	   
	 x1 = (NOx%3)*IOC_SIZE + IOC_SIZE/6*(NOx%3) + FONT_1; 
	 y1 = FONT_3+(NOx/3)*(IOC_SIZE+FONT_2*2); 
	 
	 x2 = x1 + IOC_SIZE;   	
	 y2 = y1 + IOC_SIZE;  	
	 p ->x1 = x1; p ->y1 = y1;
	 p ->x2 = x2; p ->y2 = y2;
	 p ->str = str;
	 p ->backcolor = _BackColor;  		
	 p ->textcolor = _TextColor;	
	 p ->_AppAddr = _AppAddr;
	 p ->_AppStart = _AppStart;
	 p ->_AppEnd = _AppEnd;
	  
	 NOx ++;	
	 return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Ico_Show()     
* @Description   : 显示桌面图标
* @Data          : 2016/3/23
* @Explain        
* --------------------------------------------  
* NOx 序号    str 语句   TextColor 文字颜色   
* BackColor 背景
------------------------------------------------------------------------------*/ 
unsigned int OS_Ico_Show(void) 
{ 
	 Type_Ico *temp = &Ico_Head;																	
	 u16 TempColor;  					
	 u16 i = 0;	 								
	  														
	 while(temp ->next != NULL) 					
	 {
		 temp = temp ->next;			
		 TempColor = temp ->backcolor;				
		                               
		 if(temp ->state == 1)	TempColor = ~TempColor;			
																		
		 for(i = 1;i < IOC_SIZE/10;i++)	  
		 OS_Rect_Draw(temp ->x1 + i,temp ->y1 + i,temp ->x2 - i,temp ->y2 - i,0,~(TempColor)); //外部  
																														
		 OS_Rect_Draw(temp ->x1 + IOC_SIZE/10,temp ->y1 + IOC_SIZE/10,temp ->x2 - IOC_SIZE/10 ,temp ->y2 - IOC_SIZE/10,1,TempColor);  //内部   
																	 
		 OS_Rect_Draw(temp ->x1,temp ->y1,temp ->x2,temp ->y2,0,BLACK);  //边框 
		 
		 OS_TextColor_Set(temp ->textcolor);	 			
		 OS_BackColor_Set(OS_Point_Read(temp ->x1+FONT_2 - 1,temp ->y2+FONT_1/4+1));			 
		 OS_String_Show(temp ->x1+FONT_2,temp ->y2+FONT_1/4,temp ->str,FONT_2);				
		 
	 }
	 return 0;
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





