/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_UI.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain        
* -------------------------------------------- 
*  ��Ҫʹ��OS_UI ��Ҫ�����Ƹ��ļ��µĵײ�����
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_UI.h" 			  

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Button Button_Head = {NULL};
Type_Button *Button_Temp = &Button_Head; 

/* ȫ�ֱ������� --------------------------------------------------------------*/
extern u16 DeskSourceColor[4];

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OSTextColor_Set()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------
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
* @Description   : ���� 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x,y:����
* POINT_COLOR:�˵����ɫ
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
* @Description   : ����
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
* x1,y1:�������
* x2,y2:�յ�����
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
* @Description   : ��Բ 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* (x,y):���ĵ�
* size:Բ��ĵĴ�С
* mode: 0 ����   1 ʵ��
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
* @Description   : ������
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x1,y1,x2,y2 ���������Խ�����  
* mode�� 0 ����   1ʵ��
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
* @Description   : �������� 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* mode �Ƿ���д�߿� 1д   0��д
------------------------------------------------------------------------------*/ 
void OS_Coord_Draw(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode)
{
	u16 x=0,y=0;					
	density=(density+1)/10;
	if(mode==1)	      			
	{LCD_Fill(x1,y1,x2,y2,BLACK);}	//д�߿�		
												
	LCD_Fill(x1+density*5,y1+density*5,x2-density*5,y2-density*5,WHITE); //д����						
	
	//��С��
	for(x=x1;x<x2;x+=10*density)													
	for(y=y1;y<y2;y+=10*density)							
	{OS_Circle_Draw(x,y,1,1,GRAY);}		
																			
	//�����
	for(x=x1;x<x2;x+=50*density)													
	for(y=y1;y<y2;y+=50*density)							
	{OS_Circle_Draw(x,y,2,1,BLACK);}		
		
	//�����ұ߿��
	for(y=y1+10*density;y<y2;y+=10*density)							
	{
	OS_Rect_Draw(x1+density*5,y,x1+density*8,y+density,1,BLACK);//��
	OS_Rect_Draw(x2-density*8,y,x2-density*5,y+density,1,BLACK);//��
	}
	//�����±߿��
	for(x=x1+10*density;x<x2;x+=10*density)							
	{
	OS_Rect_Draw(x,y1+density*5,x+density,y1+density*8,1,BLACK);//��
	OS_Rect_Draw(x,y2-density*5,x+density,y2-density*8,1,BLACK);//��
	}
	
	
	
	
}
 

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Picture_Draw()     
* @Description   : ��ʾͼƬ
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
* RGB565  16λ�����ʾ
* mode :  0 ���ɷ���      1 ������       2 �̶�ͼƬλ�ã����ɷ�����
* ��ͷ���� 
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
			LCD_SetCursor(x/2+x1,y+y1);//���ù��λ�� 
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
			LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//���ù��λ�� 
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
			LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//���ù��λ�� 
			LCD_WriteRAM_Prepare(); 
			LCD_WriteRAM(p_color); 
			 
		}
	}
} 

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()     
* @Description   : ��ӡ���� 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x,y ����    *str ���ָ��   size �����С   
------------------------------------------------------------------------------*/ 
void  OS_String_Show(u16 x,u16 y,u8*str,u8 size,u8 mode)
{
 		
	Show_Str(x,y,strlen((const char*)str)*size,size,str,size,mode);  
	 
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Decim_Show()     
* @Description   : ��ӡС�� 
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
x,y ����    num ��ֵ   size �����С   
digit ������Ч����     len ��ֵ�ܳ���
------------------------------------------------------------------------------*/ 
void OS_Decim_Show(u16 x,u16 y,double num,u8 digit,u8 len,u8 size,u8 mode)//���� ����.����
{ 	
	
	LCD_ShowDecim( x, y, num, digit, len,size,mode);
 
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Num_Show()     
* @Description   : ��ӡ����	
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------  
x,y ����    num ��ֵ   size �����С   
len ��ֵ�ܳ���
------------------------------------------------------------------------------*/ 
void OS_Num_Show(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)//���� ����.����
{ 
	
	LCD_ShowNum(x,y,num,len,size,mode); 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Point_Read()     
* @Description   : ��ȡ����ɫ
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y ����    num ��ֵ   size �����С   
* len ��ֵ�ܳ���
------------------------------------------------------------------------------*/ 
u16 OS_Point_Read(u16 x,u16 y) 
{  
	return LCD_ReadPoint(x,y); 
}
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Creat()     
* @Description   : ������ť		
* @Data          : 2016/3/24
* @Explain        
-------------------------------------------------------------------------------  
x,y  ����   str ���   Color ��ť��ɫ    
Fontsize �����С      state ״̬:0δ����  1����         
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
* @Description   : ��ť��ʾ
* @Data          : 2016/4/19
* @Explain   
-------------------------------------------------------------------------------
view :��ʾ��ť��״̬
------------------------------------------------------------------------------*/ 
void OS_Button_Show(Type_Button *ButtonStruct,u8 state)    
{ 	    												
	u16 ColorTemp = ButtonStruct ->color;	  
	u16 pTextColor,pBackColor;  	
	if(ButtonStruct ->state == BUTTON_CLOSE) return;
		
	if(state == BUTTON_DOWN)  
		ColorTemp = (u16)~ColorTemp;  //��ť������	 
	if(state == BUTTON_DISABLED)   ColorTemp = GRAY; //��ť������	 
		
	if(OS_Point_Read(ButtonStruct ->x1+1,ButtonStruct ->y1+1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x1+1,ButtonStruct ->y2-1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x2-1,ButtonStruct ->y1+1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x2-1,ButtonStruct ->y2-1) == ColorTemp)	
	{
		return; //��Ļ�仯�Ÿ���			 
	}
	
	
	OS_Rect_Draw(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->x2-1,ButtonStruct ->y2-1,1,ColorTemp);   //��ť�ڲ�   
	
	//��ť��Ӱ   	 
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
* @Description   : ��ť�޸�
* @Data          : 2016/4/21
* @Explain    
-------------------------------------------------------------------------------
ButtonStruct ��ť�ĵ�ַ  state ��ť����״
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
* @Description   : ��ť��ʷ״̬���
* @Data          : 2016/4/22
* @Explain    
-------------------------------------------------------------------------------
ButtonStruct ��ť�ĵ�ַ 
------------------------------------------------------------------------------*/ 
void OS_Button_LastClear(Type_Button *ButtonStruct)
{ 
	ButtonStruct ->LastState = BUTTON_DEFAULT; 
}

/**----------------------------------------------------------------------------
* @FunctionName  : Button_Scan()     
* @Description   : ��ťɨ��	
* @Data          : 2016/4/19
* @Explain        
-------------------------------------------------------------------------------  
x,y  ����   str ���   Color ��ť��ɫ    
Fontsize �����С      state ״̬:0δ����  1����         
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
* @Description   : ��ť״̬	
* @Data          : 2016/5/4
* @Explain       ��None        
------------------------------------------------------------------------------*/ 
u8 Button_State(Type_Button *ButtonStruct)    
{ 	    	
	
	if(TouchPoint._LastX > ButtonStruct->x1&&TouchPoint._LastX < ButtonStruct->x2&&TouchPoint._LastY>ButtonStruct->y1&&TouchPoint._LastY<ButtonStruct->y2) 
		return BUTTON_VALID;
	else 
		return BUTTON_INVALID;
 
}


/**----------------------------------------------------------------------------  
* @FunctionName  : OS_Clear_Y()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : 
-------------------------------------------------------------------------------						
mode��
		����ģʽ:  (��ɫ����,��ѡ��ɫ)        (����ͼ����)  
				   OS_CLEAR_PURE	         OS_CLEAR_IMAGE
						
		����ģʽ��  �иı��ˢ��				 ǿ��ˢ��	    			
				   OS_CLEAR_WEAKNESS	     OS_CLEAR_CONSTRAINT
						
��ע������ģʽ֮���� | ���ӣ�
------------------------------------------------------------------------------*/ 
u16 OS_Clear_Y(u16 _Bar_Y,u8 _mode,u16 _color)  
{
	 
	if(_mode & OS_CLEAR_WEAKNESS) //�иı��ˢ�� 
	{
		if(_mode & OS_CLEAR_PURE) //��ɫ
		{	
			if((_color != OS_Point_Read(1,FONT_1+3) ) 
			 ||(_color != OS_Point_Read(OS_LCD_WHITH - 1,FONT_1+3) )
			 ||(_color != OS_Point_Read(1,OS_LCD_LENTH - 1) )	
			 ||(_color != OS_Point_Read(OS_LCD_WHITH - 1,OS_LCD_LENTH - 1) ))
			{
				LCD_Fill(0,0,OS_LCD_WHITH,_Bar_Y+1,BLACK);  
				LCD_Fill(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,_color); 
			}
		}
		else //����ͼ
		{
			if((DeskSourceColor[0] != OS_Point_Read(1,FONT_1+3) ) 
			 ||(DeskSourceColor[1] != OS_Point_Read(OS_LCD_WHITH - 1,FONT_1+3) )
			 ||(DeskSourceColor[2] != OS_Point_Read(1,OS_LCD_LENTH - 1) )	
			 ||(DeskSourceColor[3] != OS_Point_Read(OS_LCD_WHITH - 1,OS_LCD_LENTH - 1) ))
			{
				LCD_Fill(0,0,OS_LCD_WHITH,_Bar_Y+1,BLACK);    
				OS_Picture_Draw(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,(const u8*)DESK_IMAGE,1);		
			}
		
		}
		
	}
	else //ǿ��ˢ�� 
	{
		LCD_Fill(0,0,OS_LCD_WHITH,_Bar_Y+1,BLACK); 
		if(_mode & OS_CLEAR_PURE)//��ɫ
			LCD_Fill(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,_color); 	
		else //����ͼ
			OS_Picture_Draw(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,(const u8*)DESK_IMAGE,1);	
	
	}
	
	
	return _Bar_Y;		
}
						
			

		
	
		
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
		
		
		
	
	
	

