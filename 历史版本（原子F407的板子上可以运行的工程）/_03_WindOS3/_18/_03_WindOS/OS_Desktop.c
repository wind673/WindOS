/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Desktop.c
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/    

/* 头文件包含 ----------------------------------------------------------------*/          
#include "OS_Desktop.h"  

/* 私有宏定义 ----------------------------------------------------------------*/
/* 按钮位置宏定义 --------------------------------------*/
#define  X_X1  (OS_LCD_WHITH - FONT_3 - 5)
#define  X_Y1  (FONT_2)
#define  X_X2  (OS_LCD_WHITH - 5)
#define  X_Y2  (FONT_1+FONT_3) 

#define  T_X1  ( OS_LCD_WHITH - FONT_3*3)
#define  T_Y1  (FONT_2)
#define  T_X2  (OS_LCD_WHITH - FONT_3*2)
#define  T_Y2  (FONT_1+FONT_3) 
 

/* 私有（静态）函数声明 -------------------------------------------------------*/ 
 
/* 全局变量定义 --------------------------------------------------------------*/
Type_Ico  IcoHead = {NULL}; 		
Type_Ico *IcoTemp = &IcoHead;		
Type_Ico *AppRunning = NULL;		
TypeTaskbar Taskbar = {BAR_UP,0,BAR_FREE,BAR_FIRST};
Type_Button Button_X = {NULL},Button_T = {NULL}; 
u16 DeskSourceColor[4] = {0};
TypeDesk DeskPage = {0,0,0}; //0 首页
 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : Desktop()     
* @Description   : None 
* @Data          : 2016/3/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Desktop(void)  
{    
	/* 注册相关程序  -----------------------------*/ 
	OSTask_Creat(&OS_Taskbar_Show); 
	OSTask_Creat(&OS_IcoShow);			
	OSTask_Creat(&OS_AppIn);			
	OSTask_Creat(&OS_AppOut); 		 
	OSTask_Creat(&OS_Ico_Scan);	
	
	/* 创建按钮  --------------------------------*/
	OS_Button_Creat(&Button_X,X_X1,X_Y1,(u8*)"×",FONT_3,RED);
	OS_Button_Creat(&Button_T,T_X1,T_Y1,(u8*)"—",FONT_3,RED);
	
	/* 刷背景  ---------------------------------*/ 	 
	OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_CONSTRAINT,NULL); 
	
	/* 记录背景  -------------------------------*/ 
	DeskSourceColor[0] = OS_Point_Read(1,FONT_1+3);	
	DeskSourceColor[1] = OS_Point_Read(OS_LCD_WHITH - 1,FONT_1+3);	
	DeskSourceColor[2] = OS_Point_Read(1,OS_LCD_LENTH - 1);	
	DeskSourceColor[3] = OS_Point_Read(OS_LCD_WHITH - 1,OS_LCD_LENTH - 1);	
	return 0;	
}
//程序注册表 
Type_AppList OS_Desktop = {Desktop,NULL,NULL,NULL, \
						OS_STATE_ONE_OFF,OS_THREAD_FREE, \
						(u8*)"OS_Desktop",1};			
															
						 
/**----------------------------------------------------------------------------  
* @FunctionName  : AppIn()     
* @Description   : 程序入口 
* @Data          : 2016/3/24
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int AppIn(void)  
{  
	 Type_Ico *IcoStruct = &IcoHead;
	 signed int x1,x2,y1,y2,i; 
	
	 //if(TouchPoint._State == TOUCH_STATE_OFF) return 1;		
	 
	 while(IcoStruct ->next != NULL)
	 { 
		 IcoStruct = IcoStruct ->next;
		 if(DeskPage.CurrentPage != IcoStruct ->Page) continue; 
		 if(TouchPoint._SlipDirection != TOUCH_SLIP_NULL) return 2;
		 
		 if(IcoStruct ->LastState == BUTTON_DOWNED)	 
		 {    	 
			 Ico_LastClear(IcoStruct); 
			 if(Ico_State(IcoStruct) == BUTTON_VALID)
			 {  
				 AppRunning = IcoStruct; 	//记录正在运行的程序		 				
				 OSTask_Alter(&OS_AppIn,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
				 OSTask_Alter(&OS_IcoShow,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
																										
				 OSTask_Alter(&OS_AppOut,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 	
				 OSTask_Alter(IcoStruct->App,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT);  	
																								
				 x1 = IcoStruct ->x1 + IcoStruct ->x2;								
				 y1 = IcoStruct ->y1 + IcoStruct ->y2; 								
				 x1/=2; y1/=2; 						
				 x2 = x1; y2 =y1; 			
					  
				 for(i = 0;i<OS_LCD_LENTH;i++) 	//进入程序的动画
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
				OS_Clear_Y(FONT_1,OS_CLEAR_PURE|OS_CLEAR_CONSTRAINT,WHITE); //清屏	   
			} 	
		} 	
	}
													
	return 0;				
} 
//程序注册表 
Type_AppList OS_AppIn = {AppIn,NULL,NULL,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"OS_AppIn",50};		

/**----------------------------------------------------------------------------  
* @FunctionName  : AppOut()     
* @Description   : 程序出口 
* @Data          : 2016/3/24
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int AppOut(void)  
{   
	signed int x1,x2,y1,y2,i;
	
	/* 关闭程序  -----------------------------*/
	x1 = OS_LCD_WHITH - FONT_3 - 5;
	y1 = FONT_2;
	x2 = OS_LCD_WHITH - 5;
	y2 = FONT_1+FONT_3;
	
	OS_Button_Show(&Button_X,Button_X.state); //画出“×”  
	if(OS_Button_State(&Button_X) == BUTTON_VALID)	
	{     
		x1 = 0;x2 = OS_LCD_WHITH;  	
		y1 = 0;y2 = OS_LCD_LENTH;    
		OS_Rect_Draw(0,0,OS_LCD_WHITH,OS_LCD_LENTH,1,BLACK);					
		for(i = 0;i<OS_LCD_LENTH;i++) 	//退出程序的动画														
		{ 	 
			x1 +=1;x2-=1;	
			y1 +=1;y2-=1;  	
			OS_Rect_Draw(x1,y1,x2,y2,0,WHITE);   	
			if(x1 >= OS_LCD_WHITH/2 && y1 >= OS_LCD_LENTH/2) break;	
		}  	
		OSTask_Alter(AppRunning ->App,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE,OS_DEFAULT);   		
		OSTask_Alter(&OS_AppOut,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 			
		OSTask_Alter(&OS_IcoShow,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 					
		OSTask_Alter(&OS_AppIn,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT);   					
																	
		OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_CONSTRAINT,NULL);	//清屏 
		Ico_LastClear(AppRunning); 
		TouchPoint._LastX = 0xffff;
		TouchPoint._LastY = 0xffff; 
	}
	 
	/* 挂起（后台）程序  ---------------------*/  
	x1 = OS_LCD_WHITH - FONT_3*3;
	y1 = FONT_2;	
	x2 = OS_LCD_WHITH - FONT_3*2;
	y2 = FONT_1+FONT_3; 
	
	OS_Button_Show(&Button_T,Button_T.state); //画出“—”
	if(OS_Button_State(&Button_T) == BUTTON_VALID)	
	{  
		x1 = 0;x2 = OS_LCD_WHITH;  
		y1 = 0;y2 = OS_LCD_LENTH;    
		OS_Rect_Draw(0,0,OS_LCD_WHITH,OS_LCD_LENTH,1,BLACK);					
		for(i = 0;i<OS_LCD_LENTH;i++) 	//挂起程序的动画
		{ 	 
			x1 +=1;x2-=1;
			y1 +=1;y2-=1;  
			OS_Rect_Draw(x1,y1,x2,y2,0,WHITE);   	
			if(x1 >= OS_LCD_WHITH/2 && y1 >= OS_LCD_LENTH/2) break;	
		}  		 
													
		OSTask_Alter(AppRunning ->App,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT);   
		OSTask_Alter(&OS_AppOut,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
		OSTask_Alter(&OS_IcoShow,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 
		OSTask_Alter(&OS_AppIn,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT);  
		OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_CONSTRAINT,NULL); //清屏 
		Ico_LastClear(AppRunning);
		TouchPoint._LastX = 0xffff;
		TouchPoint._LastY = 0xffff;	  
	}	
 
	OS_Button_LastClear(&Button_X); 	
	OS_Button_LastClear(&Button_T);
	return 0;	
}
//程序注册表  
Type_AppList OS_AppOut = {AppOut,NULL,NULL,NULL, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"OS_AppOut",50};	

/**----------------------------------------------------------------------------
* @FunctionName  : OS_IcoCreat()     
* @Description   : 显示桌面图标
* @Data          : 2016/3/23
* @Explain        
* --------------------------------------------  
* NOx 序号     
* TextColor 文字颜色   	 BackColor 背景
------------------------------------------------------------------------------*/ 
unsigned char OS_IcoCreat(Type_AppList *_App,u16 _TextColor,u16 _BackColor)
{ 
	 u16 x1,y1,x2,y2;   
	 static u16 NOx = 0;//APP序列
	 
	 Type_Ico *p = (Type_Ico*)malloc(sizeof(Type_Ico));  		 
	 if(p == NULL) return 1;
	 
	 IcoTemp -> next = p;
	 IcoTemp = p;  
	
	 p ->next =NULL; 
	 p ->str = _App->name;
	 p ->backcolor = _BackColor;  		
	 p ->textcolor = _TextColor;		
	 p ->App = _App;	
	 p ->Nox = NOx%9;
	 p ->Page = NOx/9;
	 
	 DeskPage.EndPage = NOx/9;	
	   
	 x1 = (p ->Nox%3)*IOC_SIZE + IOC_SIZE/6*(p ->Nox%3) + FONT_1; 	
	 y1 = FONT_3+(p ->Nox/3)*(IOC_SIZE+FONT_2*2); 		
	 
	 x2 = x1 + IOC_SIZE;   	
	 y2 = y1 + IOC_SIZE;  	
	 p ->x1 = x1; p ->y1 = y1;	
	 p ->x2 = x2; p ->y2 = y2;	
	
	 
	 NOx ++;	
	 return 0;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_IcoShow()     
* @Description   : 显示桌面图标
* @Data          : 2016/3/23
* @Explain        
* --------------------------------------------  
* NOx 序号    str 语句   TextColor 文字颜色   
* BackColor 背景	
------------------------------------------------------------------------------*/ 
unsigned int IcoShow(void) 
{ 
	 Type_Ico *IcoStruct = &IcoHead;																		
	 u16 BackColor,TempColor,_x;
	 static signed char LastPage;  	 
		
	 /* 条件清屏 ------------------------------*/   	
	 OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_WEAKNESS,NULL); //清屏
	 
	 /* 换页过度动画 --------------------------*/ 
	 if(LastPage !=  DeskPage.CurrentPage) 
	 { 
		 if(DeskPage.CurrentPage > LastPage)  
		 {
			 _x = OS_LCD_WHITH;
			 while(_x--)
			 { 
				OS_Lines_Draw(_x,FONT_1,_x,OS_LCD_LENTH,BLACK);
			 }
		 }
				
		 if(DeskPage.CurrentPage < LastPage)	 
		 {
			 _x = 0; 
			 for(_x = 0;_x <= OS_LCD_WHITH;_x++) 
				OS_Lines_Draw(_x,FONT_1,_x,OS_LCD_LENTH,BLACK);
		 }
		 
		 LastPage = DeskPage.CurrentPage;
		 OS_Clear_Y(FONT_1,OS_CLEAR_IMAGE|OS_CLEAR_CONSTRAINT,NULL); //清屏
	 }
	 
	 /* 显示桌面页码 --------------------------*/ 	
	 OS_TextColor_Set(WHITE);
	 OS_BackColor_Set(BLACK);
	 if(DeskPage.CurrentPage<0)
	 {
		 OS_String_Show(OS_LCD_WHITH - FONT_1*5,0,(u8*)"Page:-",FONT_1,1);	
		 OS_Num_Show(OS_LCD_WHITH - FONT_1*2,0,128 - (u8)DeskPage.CurrentPage%128,3,FONT_1,1);
	 }
	 else 
	 {	 
		 OS_String_Show(OS_LCD_WHITH - FONT_1*5,0,(u8*)"Page: ",FONT_1,1);	
		 OS_Num_Show(OS_LCD_WHITH - FONT_1*2,0,DeskPage.CurrentPage%128,3,FONT_1,1);
	 } 
	 
	  /* 描绘图标 ------------------------------*/ 
	 while(IcoStruct ->next != NULL) 					
	 { 
		IcoStruct = IcoStruct ->next;	 
		if(DeskPage.CurrentPage != IcoStruct ->Page) continue;	
		
		if(Ico_State(IcoStruct) != BUTTON_VALID)	
		{	 		
			if( (OS_Point_Read(IcoStruct ->x1,IcoStruct ->y1) == BLACK)
				&&(OS_Point_Read(IcoStruct ->x1,IcoStruct ->y2) == BLACK)
				&&(OS_Point_Read(IcoStruct ->x2,IcoStruct ->y1) == BLACK)
				&&(OS_Point_Read(IcoStruct ->x2,IcoStruct ->y2) == BLACK) )
			{
				continue; //屏幕变化才更新			 
			}  
			 
			BackColor = IcoStruct ->backcolor; 	
			TempColor = BLACK;	
		} 
		else {BackColor = ~(IcoStruct ->backcolor); TempColor = WHITE;}	 
		
		OS_Rect_Draw(IcoStruct ->x1 + IOC_SIZE/10,IcoStruct ->y1 + IOC_SIZE/10,IcoStruct ->x2 - IOC_SIZE/10 ,IcoStruct ->y2 - IOC_SIZE/10,1,BackColor);  //内部   	 
		OS_Rect_Draw(IcoStruct ->x1,IcoStruct ->y1,IcoStruct ->x2,IcoStruct ->y2,0,TempColor);  //边框 												
		 
		OS_TextColor_Set(IcoStruct ->textcolor);	 			
		OS_BackColor_Set(OS_Point_Read(IcoStruct ->x1+FONT_2 - 1,IcoStruct ->y2+FONT_1/4+1));			 
		OS_String_Show(IcoStruct ->x1+FONT_2,IcoStruct ->y2+FONT_1/4,IcoStruct ->str,FONT_2,0);				
		
	 }
	 
	 return 0;	
}


//程序注册表 		
Type_AppList OS_IcoShow = {IcoShow,NULL,NULL,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"OS_IcoShow",200};			
/**----------------------------------------------------------------------------
* @FunctionName  : Ico_Scan()     
* @Description   : 图标扫描	
* @Data          : 2016/5/5
* @Explain       ：None   
------------------------------------------------------------------------------*/ 
unsigned int Ico_Scan(void)    
{ 	   
	Type_Ico *IcoStruct = &IcoHead;
 
	while(1)
	{ 
		if(IcoStruct ->next != NULL) IcoStruct = IcoStruct ->next;
		else break; 
		
		if(IcoStruct ->state == BUTTON_CLOSE) continue;
		 
		if(TouchPoint._X > IcoStruct->x1&&TouchPoint._X < IcoStruct->x2 \
			&&TouchPoint._Y> IcoStruct->y1&&TouchPoint._Y < IcoStruct->y2)  
		{	
			IcoStruct ->state = BUTTON_DOWN; 	 
			IcoStruct ->value ++; 	
		}	 
		else			
		{		   
			if(IcoStruct ->state == BUTTON_DOWN) IcoStruct ->LastState = BUTTON_DOWNED;
			
			IcoStruct ->value = 0;
			IcoStruct ->state = BUTTON_DEFAULT;  
		}
		 
	}
	return 0;	
}					
			
Type_AppList OS_Ico_Scan = {Ico_Scan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"Ico_Scan",TOUCH_SCAN_SPEED};			
				

/**----------------------------------------------------------------------------
* @FunctionName  : Ico_State()     
* @Description   : 图标状态	
* @Data          : 2016/5/5
* @Explain       ：None        
------------------------------------------------------------------------------*/ 
u8 Ico_State(Type_Ico *IcoStruct)    
{ 	    	 
	if( TouchPoint._LastX > IcoStruct->x1 \
		&&TouchPoint._LastX < IcoStruct->x2 \
		&&TouchPoint._LastY > IcoStruct->y1 \
		&&TouchPoint._LastY < IcoStruct->y2)  
		return BUTTON_VALID;
	else 
		return BUTTON_INVALID;
 
}

/**----------------------------------------------------------------------------
* @FunctionName  : Ico_LastClear()     
* @Description   : 图标历史状态清除
* @Data          : 2016/4/22
* @Explain    
-------------------------------------------------------------------------------
IcoStruct 图标的地址 
------------------------------------------------------------------------------*/ 
void Ico_LastClear(Type_Ico *IcoStruct)
{ 
	IcoStruct ->LastState = BUTTON_DEFAULT;  
}
	
		
/**----------------------------------------------------------------------------  
* @FunctionName  : Taskbar_Show()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Taskbar_Show(void)  
{  
	 
	 OS_TextColor_Set(WHITE);	
	 OS_BackColor_Set(BLACK);	
	 if(Taskbar.run_state == BAR_FIRST){ OS_Clear_Y(FONT_1,OS_CLEAR_PURE|OS_CLEAR_CONSTRAINT,WHITE);Taskbar.run_state = BAR_CLOSE;} 
	 if(TouchPoint._State != 0)  //判断是否按下屏幕		
	 {
		if(Taskbar.activate_point == BAR_UP) //判断激活点位置			
		if(TouchPoint._Y < FONT_1) Taskbar.activate_state = BAR_ACTIVATE;		
		
		if(Taskbar.activate_point == BAR_DOWN) 				
		{			
			if(TouchPoint._Y > OS_LCD_LENTH - FONT_3*3) Taskbar.activate_state = BAR_ACTIVATE;
			
		}				
	 } 			
	 else{ Taskbar.activate_state = BAR_CLOSE;}		 			
	  
	 if(Taskbar.activate_state == BAR_ACTIVATE) //判断用户是否按下激活点 	
	 {
		OSRunning_Break();
		Taskbar.dynamic_Y = OS_Clear_Y(TouchPoint._Y,OS_CLEAR_PURE|OS_CLEAR_CONSTRAINT,WHITE); 
		OS_String_Show(OS_LCD_WHITH/2-FONT_1*2,TouchPoint._Y,(u8*)"◎◎◎◎",FONT_1,1);	
		Taskbar.run_state = BAR_RUNNING;	
	 }	           
	 else  
	 {
		 
		if(Taskbar.run_state == BAR_RUNNING)  		
		{
			if(Taskbar.dynamic_Y > OS_LCD_LENTH/3)			
			{			
				Taskbar.activate_point = BAR_DOWN; 		  
				OS_Clear_Y(OS_LCD_LENTH,OS_CLEAR_PURE|OS_CLEAR_CONSTRAINT,WHITE);					
			}
			else 						
			{
				Taskbar.activate_point = BAR_UP;     	
				OS_Clear_Y(FONT_1,OS_CLEAR_PURE|OS_CLEAR_CONSTRAINT,WHITE);			
				OSRunning_Continue();				
			}
			Taskbar.run_state = BAR_CLOSE; //松手后 进行判断，并做相应的处理		
		   					
		}
		
	 }			
	 	
	 return 0;				
}
//程序注册表 
Type_AppList OS_Taskbar_Show = {Taskbar_Show,NULL,NULL,NULL, \
					   	   OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						   (u8*)"Taskbar",10};  		
	
						   
/**----------------------------------------------------------------------------  
* @FunctionName  : TaskbarY()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : None
------------------------------------------------------------------------------*/

//u16 Taskbar_Draw(u16 Bar_Y)  
//{
//	LCD_Fill(0,0,OS_LCD_WHITH,Bar_Y+1,BLACK); 
//	 
//	LCD_Fill(0,Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,WHITE); 		
//		   
//	return Bar_Y;		
//}
//	

 
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





