/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_UI.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain        
* -------------------------------------------- 
*  若要使用OS_UI 则要求完善该文件下的底层驱动
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_UI.h" 			  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Button Button_Head = {NULL};
Type_Button *Button_Temp = &Button_Head;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OSTextColor_Set()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain        
* -------------------------------------------- 
* None
------------------------------------------------------------------------------*/
unsigned int OS_TextColor_Set(u16 _color)
{
	uint16_t temp = TextColor;
	TextColor = _color;
	return temp;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_BackColor_Set()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain        
* -------------------------------------------- 
* None
------------------------------------------------------------------------------*/
unsigned int OS_BackColor_Set(u16 _color)
{
	uint16_t temp = BackColor;
	BackColor = _color;
	return temp;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Points_Draw()     
* @Description   : 画点 
* @Data          : 2016/3/22
* @Explain        
* -------------------------------------------- 
* x,y:坐标
* POINT_COLOR:此点的颜色
------------------------------------------------------------------------------*/
void OS_Points_Draw(u16 x,u16 y,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	LCD_Fast_DrawPoint(x,y,TextColor);
	TextColor=temp;
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Lines_Draw()     
* @Description   : 画线
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x1,y1:起点坐标
* x2,y2:终点坐标
------------------------------------------------------------------------------*/ 
void OS_Lines_Draw(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{ 
	u16 temp=TextColor;
	TextColor=color;
	LCD_DrawLine(x1, y1,x2,y2);
	TextColor=temp;
} 



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Circle_Draw()     
* @Description   : 画圆 
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* (x,y):中心点
* size:圆点的的大小
* mode: 0 空心   1 实心
------------------------------------------------------------------------------*/  
void OS_Circle_Draw(u16 x,u16 y,u8 size,u8 mode,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	if(mode == 1)
	{
		if(x<=size) x=size+1;
		for(;size>0;size--)
		LCD_Draw_Circle(x,y,size);
	}
	else if(mode == 0)
	{
		LCD_Draw_Circle(x,y,size);
	}
	TextColor=temp;
} 

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Rect_Draw()     
* @Description   : 画矩形
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x1,y1,x2,y2 ：矩形两对角坐标  
* mode： 0 空心   1实心
------------------------------------------------------------------------------*/  
void OS_Rect_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u16 color)
{	
  
	if(mode == 1)
	{ 
		LCD_Fill(x1,y1,x2,y2,color);
		
	}
	else if(mode == 0)
	{
		OS_Lines_Draw(x1,y1,x2,y1,color);
		OS_Lines_Draw(x1,y2,x2,y2,color);
		OS_Lines_Draw(x2,y1,x2,y2,color);
		OS_Lines_Draw(x1,y1,x1,y2,color);
	} 
} 


 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Coord_Draw()     
* @Description   : 创建坐标 
* @Data          : 2016/3/22
* @Explain        
* -------------------------------------------- 
* mode 是否重写边框 1写   0不写
------------------------------------------------------------------------------*/ 
void OS_Coord_Draw(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode)
{
	u16 x=0,y=0;					
	density=(density+1)/10;
	if(mode==1)	      			
	{LCD_Fill(x1,y1,x2,y2,BLACK);}	//写边框		
												
	LCD_Fill(x1+density*5,y1+density*5,x2-density*5,y2-density*5,WHITE); //写背景						
	
	//画小点
	for(x=x1;x<x2;x+=10*density)													
	for(y=y1;y<y2;y+=10*density)							
	{OS_Circle_Draw(x,y,1,1,GRAY);}		
																			
	//画大点
	for(x=x1;x<x2;x+=50*density)													
	for(y=y1;y<y2;y+=50*density)							
	{OS_Circle_Draw(x,y,2,1,BLACK);}		
		
	//画左右边框点
	for(y=y1+10*density;y<y2;y+=10*density)							
	{
	OS_Rect_Draw(x1+density*5,y,x1+density*8,y+density,1,BLACK);//左
	OS_Rect_Draw(x2-density*8,y,x2-density*5,y+density,1,BLACK);//右
	}
	//画上下边框点
	for(x=x1+10*density;x<x2;x+=10*density)							
	{
	OS_Rect_Draw(x,y1+density*5,x+density,y1+density*8,1,BLACK);//上
	OS_Rect_Draw(x,y2-density*5,x+density,y2-density*8,1,BLACK);//下
	}
	
	
	
	
}
 

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Picture_Draw()     
* @Description   : 显示图片
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* RGB565  16位真彩显示
* mode :  0 不可放缩      1 可缩放       2 固定图片位置（不可放缩）
* 带头数据 
------------------------------------------------------------------------------*/ 
void OS_Picture_Draw(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic,u8 mode)
{	
	if(mode == 0)
	{
		u16 x,y,p_color;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		for(y=0;y<len_y;y++)
		for(x=0;x<len_x*2;x+=2)
		{
			p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2];
			LCD_SetCursor(x/2+x1,y+y1);//设置光标位置 
			LCD_WriteRAM_Prepare(); 
			LCD_WriteRAM(p_color);
		}
	}
	else if(mode == 1)
	{
		u16 x,y,p_color;
		float density_x,density_y;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		density_x=(float)(x2-x1)/len_x; 
		density_y=(float)(y2-y1)/len_y; 
		
		for(y=0;y<len_y;y++) 
		for(x=0;x<len_x*2;x+=2) 
		{ 
			p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2]; 
			LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
			LCD_WriteRAM_Prepare(); 
			LCD_WriteRAM(p_color); 
			 
		}
	
	}
	
	else if(mode == 2)
	{
		u16 x,y,p_color;
		float density_x,density_y;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		density_x=(float)(x2-x1)/len_x; 
		density_y=(float)(y2-y1)/len_y; 
		
		for(y=y1;y<y2;y++) 
		for(x=x1;x<x2*2;x+=2) 
		{ 
			p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2]; 
			LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
			LCD_WriteRAM_Prepare(); 
			LCD_WriteRAM(p_color); 
			 
		}
	}
} 

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()     
* @Description   : 打印句子 
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y 坐标    *str 语句指针   size 字体大小   
------------------------------------------------------------------------------*/ 
void  OS_String_Show(u16 x,u16 y,u8*str,u8 size)
{
 		
	Show_Str(x,y,size*10,size,str,size,0);  
	 
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Decim_Show()     
* @Description   : 打印小数 
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
x,y 坐标    num 数值   size 字体大小   
digit 保留有效数字     len 数值总长度
------------------------------------------------------------------------------*/ 
void OS_Decim_Show(u16 x,u16 y,double num,u8 digit,u8 len,u8 size)//长度 包括.在内
{ 
	
	LCD_ShowDecim( x, y, num, digit, len,size);
 
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Num_Show()     
* @Description   : 打印整数	
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
x,y 坐标    num 数值   size 字体大小   
len 数值总长度
------------------------------------------------------------------------------*/ 
void OS_Num_Show(u16 x,u16 y,u32 num,u8 len,u8 size)//长度 包括.在内
{ 
	
	LCD_ShowNum(x,y,num,len,size); 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Point_Read()     
* @Description   : 读取点颜色
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y 坐标    num 数值   size 字体大小   
* len 数值总长度
------------------------------------------------------------------------------*/ 
u16 OS_Point_Read(u16 x,u16 y) 
{  
	return LCD_ReadPoint(x,y); 
}
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Creat()     
* @Description   : 创建按钮		
* @Data          : 2016/3/24
* @Explain        
* --------------------------------------------  
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
------------------------------------------------------
view :显示按钮的状态
------------------------------------------------------------------------------*/ 
void OS_Button_Show(Type_Button *ButtonStruct,u8 view)    
{ 	    												
	u16 ColorTemp = ButtonStruct ->color;	  
	u16 pTextColor,pBackColor;  	
	if(ButtonStruct ->state == Button_Close) return;
		
	if(view == Button_Down)  
		ColorTemp = (u16)~ColorTemp;  //按钮被按下	 
	if(view == Button_Disabled)   ColorTemp = GRAY; //按钮不可用	 
		
	if(OS_Point_Read(ButtonStruct ->x1,ButtonStruct ->y1) == ColorTemp) return; //屏幕变化才更新			 
	
	OS_Rect_Draw(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->x2-1,ButtonStruct ->y2-1,1,ColorTemp);   //按钮内部   
	
	//按钮阴影   	 
	OS_Lines_Draw(ButtonStruct ->x1,ButtonStruct ->y2,ButtonStruct ->x2,ButtonStruct ->y2, \
	~OS_Point_Read(ButtonStruct ->x2+2,ButtonStruct ->y2+2)); 	
				 
	OS_Lines_Draw(ButtonStruct ->x2,ButtonStruct ->y1,ButtonStruct ->x2,ButtonStruct ->y2, \
	~OS_Point_Read(ButtonStruct ->x2+2,ButtonStruct ->y2+2)); 		
											
	pTextColor = OS_TextColor_Set(~ColorTemp);		 			
	pBackColor = OS_BackColor_Set(ColorTemp);								  
	OS_String_Show(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->str,ButtonStruct ->fontsize);		
	OS_TextColor_Set(pTextColor);	
	OS_BackColor_Set(pBackColor);	
	 
}



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Alter()     
* @Description   : 按钮修改
* @Data          : 2016/4/21
* @Explain    
---------------------------------------------------
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
---------------------------------------------------
ButtonStruct 按钮的地址 
------------------------------------------------------------------------------*/ 
void OS_Button_LastClear(Type_Button *ButtonStruct)
{
	
	ButtonStruct ->LastState = NULL;
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : Button_Scan()     
* @Description   : 按钮扫描	
* @Data          : 2016/4/19
* @Explain        
* --------------------------------------------  
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
		if(ButtonStruct ->state == Button_Close) continue;
		 
		if(TouchPoint._X > ButtonStruct->x1&&TouchPoint._X < ButtonStruct->x2 \
			&&TouchPoint._Y> ButtonStruct->y1&&TouchPoint._Y < ButtonStruct->y2)  
		{	
			ButtonStruct ->state = Button_Down; 
			ButtonStruct ->LastState = Button_Down;
			ButtonStruct ->value ++; 	
		}
		else 
		{
			ButtonStruct ->value = 0;
			ButtonStruct ->state = Button_Up;	
		}
		 
	}
	return 0;
}					
			
Type_AppList OS_Button_Scan = {Button_Scan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"Button_Scan",TOUCH_SCAN_SPEED};			
																
																	
/**----------------------------------------------------------------------------  
* @FunctionName  : OS_Clear_Y()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : mode 0(无背景清屏,可选颜色)   mode 1(带背景清屏)  
------------------------------------------------------------------------------*/ 
u16 OS_Clear_Y(u16 _Bar_Y,u8 _mode,u16 _color)  
{
	LCD_Fill(0,0,OS_LCD_WHITH,_Bar_Y+1,BLACK); 
	
	if(_mode == 0) 
	LCD_Fill(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,_color); 	
	
	if(_mode == 1)
	OS_Picture_Draw(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,(const u8*)DESK_IMAGE,1);		
	 
	return _Bar_Y;		
}
						
			

		
	
		
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
		
		
		
	
	
	

