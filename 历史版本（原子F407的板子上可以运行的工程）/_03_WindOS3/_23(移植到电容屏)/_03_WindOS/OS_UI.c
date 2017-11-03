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

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

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
* @FunctionName  : OS_FFT_Draw()     
* @Description   : ��FFTͼ 
* @Data          : 2016/5/24
* @Explain        
-------------------------------------------------------------------------------
density �����ܶ�     Rate ���� 
------------------------------------------------------------------------------*/  
void OS_FFT_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Num,float Rate,float density)
{
	u16 x=0,y=0,_cnt = 1;   
	density=(density+1)/10;
 
	//��FFTͼ 
	for(_cnt = 0;_cnt < x2-x1-2;_cnt++)
	{
		if(Buff[_cnt*Num/(x2-x1-2)]*Rate < y2-y1-2)
		{
			OS_Lines_Draw(x1+_cnt,y1+2,x1+_cnt,y2- Buff[_cnt*Num/(x2-x1-2)]*Rate,WHITE);
			OS_Lines_Draw(x1+_cnt,y2 - Buff[_cnt*Num/(x2-x1-2)]*Rate,x1+_cnt,y2 - 2,BLUE);
		}
		else OS_Lines_Draw(x1+_cnt,y1 + 2,x1+_cnt,y2,RED);
	}
	  
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK);
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,BLACK);  
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLACK);  
	
	//�����ұ߿��
	for(y=y1;y<y2;y+=10*density)							
	{
		if(y%((u16)(50*density)) == y1)
		{
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,BLACK);//��
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,BLACK);//��
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,BLACK);//��
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,BLACK);//�� 
		}
	}
	//�����±߿��
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%((u16)(50*density)) == x1)
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,BLACK);//��
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,BLACK);//��
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,BLACK);//��
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,BLACK);//��
		}
	}  
	 
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_OSC_Draw()     
* @Description   : ��ʾ����ͼ 
* @Data          : 2016/5/24
* @Explain        
-------------------------------------------------------------------------------
density �����ܶ�     Struct_OSC ʾ����������ʾ����
------------------------------------------------------------------------------*/ 
void OS_OSC_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Num,float density,Type_OSC *Struct_OSC)
{
	u16 x=0,y=0,_cnt = 1;
	u16 TempX1=0,TempY1=0,TempX2 = 0,TempY2 = 0;
	u16 MaxX = 0,MinX = 0;
	static u16 LastBuff[OS_LCD_WHITH] = {0}; 
	density=(density+1)/10; 
	 
	//��С��
	for(x=x1;x<x2-2;x+=10*density)													
	for(y=y1;y<y2-2;y+=10*density)							
	{
		OS_Circle_Draw(x+2,y+2,1,1,GRAY);  
	}		
																			
	//�����
	for(x=x1;x<x2-2;x+=50*density)													
	for(y=y1;y<y2-2;y+=50*density)							
	{
		OS_Circle_Draw(x+2,y+2,1,1,BLACK);
	}
	
	//����ϴλ��ĵ�
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{  
		TempX1 = x1+_cnt-1;
		TempY1 = LastBuff[_cnt-1];
		TempX2 = x1+_cnt;
		TempY2 = LastBuff[_cnt];
		 
		if(TempY1>y1 && TempY1<y2) 
		if(TempY2>y1 && TempY2<y2) 	
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,WHITE);    
	}
	
	Struct_OSC ->MaxValue  = 0;
	Struct_OSC ->MinValue  = 0xffff;	
	Struct_OSC ->T = 0;
	Struct_OSC ->Vpp = 0;
	
	//�������� 
	for(_cnt = 3;_cnt <Num/10;_cnt++)
	{
		if(Buff[_cnt] > Struct_OSC ->MaxValue) Struct_OSC ->MaxValue = Buff[_cnt],MaxX = _cnt;
		if(Buff[_cnt] < Struct_OSC ->MinValue) Struct_OSC ->MinValue = Buff[_cnt],MinX = _cnt;
	}		
				
	if(MaxX - MinX) Struct_OSC ->T = MaxX - MinX;	
	else Struct_OSC ->T = MinX - MaxX;	
	
	Struct_OSC ->Vpp = Struct_OSC ->MaxValue - Struct_OSC ->MinValue;	
											
	//����		
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{     
		LastBuff[_cnt] = ((u16)(Buff[(u16)((_cnt+Struct_OSC ->ShiftX)/Struct_OSC ->ZoomX)+MaxX])*Struct_OSC ->ZoomY) + Struct_OSC ->ShiftY - 100;//����������ͼ��ƫ�� 
		TempX1 = x1+_cnt-1;		
		TempY1 = LastBuff[_cnt-1];		
		TempX2 = x1+_cnt;		
		TempY2 = LastBuff[_cnt];	
										
		if(TempY1>y1 && TempY1<y2) 		
		if(TempY2>y1 && TempY2<y2) 			
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,BLUE);  		
	} 
	OS_Num_Show(0,FONT_2*1,Struct_OSC ->T,6,FONT_2,1);		 OS_Num_Show(FONT_2*4,FONT_2*1,Struct_OSC ->Vpp,6,FONT_2,1); 
	OS_Num_Show(0,FONT_2*2,Struct_OSC ->MinValue,6,FONT_2,1);OS_Num_Show(FONT_2*4,FONT_2*2,Struct_OSC ->MaxValue,6,FONT_2,1);
	 
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK);
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,BLACK);  
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLACK);  
												
	//�����ұ߿��	
	for(y=y1;y<y2;y+=10*density)							
	{
		if(y%((u16)(50*density)) == y1)
		{
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,BLACK);//��
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,BLACK);//��
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,BLACK);//��
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,BLACK);//�� 
		}
	}
	//�����±߿��
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%((u16)(50*density)) == x1)
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,BLACK);//��
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,BLACK);//��
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,BLACK);//��
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,BLACK);//��
		}
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
		  3 �̶�ͼƬλ�ã����ɷ�����
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
			if((u16)(x/2+x1) <= x2)
			if((u16)(y+y1) <= y2)		
			{
				p_color=pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				
				LCD_SetCursor(x/2+x1,y+y1);//���ù��λ�� 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color);
			}
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
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)		
			{
				p_color=pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//���ù��λ�� 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color);
			}				
			 
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
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)	
			{
				p_color=pic[x+6+y*len_x*2]<<8|+pic[(x+7)+y*len_x*2]; 
				LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//���ù��λ�� 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color); 
			}
			 
		}
	}
	
	else if(mode == 3)
	{
		u16 x,y,p_color,BitRed,BitGreen,BitBlue;
		float density_x,density_y;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		density_x=(float)(x2-x1)/len_x; 
		density_y=(float)(y2-y1)/len_y; 
		
		for(y=0;y<len_y;y++) 
		for(x=0;x<len_x*2;x+=2) 
		{ 
			
			
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)		
			{ 
				p_color = pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				BitRed   = (p_color & (0x1f << 11))>>11; 
				BitGreen = (p_color & (0x3f << 5 ))>>5;
				BitBlue = p_color & 0x1f;
				p_color = ((BitRed/3)<<11)|((BitGreen/3)<<5)|(BitBlue/3);
				
				LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//���ù��λ�� 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color);
			}				
			 
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
			if((_color != OS_Point_Read(DESK_REFRESH_1) ) 
			 ||(_color != OS_Point_Read(DESK_REFRESH_2) )
			 ||(_color != OS_Point_Read(DESK_REFRESH_3) )	
			 ||(_color != OS_Point_Read(DESK_REFRESH_4) ))
			{
				LCD_Fill(0,0,OS_LCD_WHITH,_Bar_Y+1,BLACK);  
				LCD_Fill(0,_Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,_color); 
			}
		}
		else //����ͼ
		{
			if((DeskSourceColor[0] != OS_Point_Read(DESK_REFRESH_1) ) 
			 ||(DeskSourceColor[1] != OS_Point_Read(DESK_REFRESH_2) )
			 ||(DeskSourceColor[2] != OS_Point_Read(DESK_REFRESH_3) )	
			 ||(DeskSourceColor[3] != OS_Point_Read(DESK_REFRESH_4) ))
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
		
		
		
	
	
	

