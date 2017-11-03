/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Button.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None 
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Button.h" 			  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Button Button_Head = {NULL};
Type_Button *Button_Temp = &Button_Head; 

/* 全局变量声明 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Creat()     
* @Description   : 创建按钮		
* @Data          : 2016/3/24
* @Explain        
-------------------------------------------------------------------------------  
x,y  坐标   str 语句   Color 按钮颜色    
Fontsize 字体大小      state 状态:0未按下  1按下         
------------------------------------------------------------------------------*/ 
void OS_Button_Creat(Type_Button *pStruct,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color)    
{ 	     	
	 pStruct ->x1 = x; 				
	 pStruct ->y1 = y;			
	 pStruct ->x2 = x + strlen((const char*)str)*Fontsize/2;					
	 pStruct ->y2 = y + Fontsize;												
	 pStruct ->str = str;		
	 pStruct ->color = Color;		
     pStruct ->fontsize = Fontsize;		
	 Button_Temp ->next = pStruct;		
	 Button_Temp = pStruct;		
	 pStruct ->next = NULL;		
}						
		
			


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Show()     
* @Description   : 按钮显示
* @Data          : 2016/4/19
* @Explain   
-------------------------------------------------------------------------------
view :显示按钮的状态
------------------------------------------------------------------------------*/ 
void OS_Button_Show(Type_Button *ButtonStruct,u8 state)    
{ 	    												
	u16 ColorTemp = ButtonStruct ->color;	  
	u16 pTextColor,pBackColor;  	
	if(ButtonStruct ->state == BUTTON_CLOSE) return;
		
	if(state == BUTTON_DOWN)  
		ColorTemp = (u16)~ColorTemp;  //按钮被按下	 
	if(state == BUTTON_DISABLED)   ColorTemp = GRAY; //按钮不可用	 
		
	if(OS_Point_Read(ButtonStruct ->x1+1,ButtonStruct ->y1+1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x1+1,ButtonStruct ->y2-1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x2-1,ButtonStruct ->y1+1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x2-1,ButtonStruct ->y2-1) == ColorTemp)	
	{
		return; //屏幕变化才更新			 
	}
	
	
	OS_Rect_Draw(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->x2-1,ButtonStruct ->y2-1,1,ColorTemp);   //按钮内部   
	
	//按钮阴影   	 
	OS_Lines_Draw(ButtonStruct ->x1,ButtonStruct ->y2,ButtonStruct ->x2,ButtonStruct ->y2, \
	~OS_Point_Read(ButtonStruct ->x2+2,ButtonStruct ->y2+2)); 	
				 
	OS_Lines_Draw(ButtonStruct ->x2,ButtonStruct ->y1,ButtonStruct ->x2,ButtonStruct ->y2, \
	~OS_Point_Read(ButtonStruct ->x2+2,ButtonStruct ->y2+2)); 		
											
	pTextColor = OS_TextColor_Set(~ColorTemp);		 			
	pBackColor = OS_BackColor_Set(ColorTemp);								  
	OS_String_Show(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->str,ButtonStruct ->fontsize,1);		
	OS_TextColor_Set(pTextColor);	
	OS_BackColor_Set(pBackColor);	
	 
}



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Alter()     
* @Description   : 按钮修改
* @Data          : 2016/4/21
* @Explain    
-------------------------------------------------------------------------------
ButtonStruct 按钮的地址  state 按钮的现状
------------------------------------------------------------------------------*/ 
void OS_Button_Alter(Type_Button *ButtonStruct,u8 state,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color)   
{ 	    	
	 if(ButtonStruct == NULL) return;	
	
	 if(x != OS_DEFAULT) 
	 {
		 ButtonStruct ->x1 = x; 	
		 ButtonStruct ->x2 = x + strlen((const char*)str)*Fontsize/2;
	 }	
	 
	 if(y != OS_DEFAULT)  
	 {
		 ButtonStruct ->y1 = y;		 
		 ButtonStruct ->y2 = y + Fontsize;		
	 }
	 
	 if(str != OS_DEFAULT) 		ButtonStruct ->str = str;	 
	 if(Color != OS_DEFAULT)	ButtonStruct ->color = Color;		
     if(Fontsize != OS_DEFAULT)	ButtonStruct ->fontsize = Fontsize;	 
	 if(state != OS_DEFAULT)  	ButtonStruct ->state = state;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Alter()     
* @Description   : 按钮历史状态清除
* @Data          : 2016/4/22
* @Explain    
-------------------------------------------------------------------------------
ButtonStruct 按钮的地址 
------------------------------------------------------------------------------*/ 
void OS_Button_LastClear(Type_Button *ButtonStruct)
{ 
	ButtonStruct ->LastState = BUTTON_DEFAULT;  
}

/**----------------------------------------------------------------------------
* @FunctionName  : Button_Scan()     
* @Description   : 按钮扫描	
* @Data          : 2016/4/19
* @Explain        
-------------------------------------------------------------------------------  
x,y  坐标   str 语句   Color 按钮颜色    
Fontsize 字体大小      state 状态:0未按下  1按下         
------------------------------------------------------------------------------*/ 
unsigned int Button_Scan(void)    
{ 	   
	Type_Button *ButtonStruct = &Button_Head;	
 
	while(1)
	{ 
		if(ButtonStruct ->next != NULL) ButtonStruct = ButtonStruct ->next;
		else break; 
		
		if(ButtonStruct ->state == BUTTON_CLOSE) continue;
		 
		if(TouchPoint._X > ButtonStruct->x1&&TouchPoint._X < ButtonStruct->x2 \
			&&TouchPoint._Y> ButtonStruct->y1&&TouchPoint._Y < ButtonStruct->y2)  
		{	
			ButtonStruct ->state = BUTTON_DOWN; 	 
			ButtonStruct ->value ++; 	
		}	 
		else			
		{		   
			if(ButtonStruct ->state == BUTTON_DOWN) ButtonStruct ->LastState = BUTTON_DOWNED;
			
			ButtonStruct ->value = 0;
			ButtonStruct ->state = BUTTON_DEFAULT;  
		}
		 
	}
	return 0;	
}					
			
Type_AppList OS_Button_Scan = {Button_Scan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"Button_Scan",TOUCH_SCAN_SPEED};			
				
						
/**----------------------------------------------------------------------------
* @FunctionName  : Button_State()     
* @Description   : 按钮状态	
* @Data          : 2016/5/4
* @Explain       ：None        
------------------------------------------------------------------------------*/ 
u8 OS_Button_State(Type_Button *ButtonStruct)    
{ 	    
	u8 state;	
	if(ButtonStruct ->LastState == BUTTON_DOWNED) 
	{	
		if( TouchPoint._LastX > ButtonStruct->x1 \
			&&TouchPoint._LastX < ButtonStruct->x2 \
			&&TouchPoint._LastY>ButtonStruct->y1 \
			&&TouchPoint._LastY<ButtonStruct->y2 ) 
			state = BUTTON_VALID;
		else 
			state = BUTTON_INVALID;
	} 
	return state;
}

 		

		
	
		
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
		
		
		
	
	
	

