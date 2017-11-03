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

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
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
* @Description   : ���� 
* @Data          : 2016/3/22
* @Explain        
* -------------------------------------------- 
* x,y:����
* POINT_COLOR:�˵����ɫ
------------------------------------------------------------------------------*/
void OS_Points_Draw(u16 x,u16 y)
{
	LCD_Fast_DrawPoint(x,y,TextColor);
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Lines_Draw()     
* @Description   : ����
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x1,y1:�������
* x2,y2:�յ�����
------------------------------------------------------------------------------*/ 
void OS_Lines_Draw(u16 x1, u16 y1, u16 x2, u16 y2)
{ 
	LCD_DrawLine(x1, y1,x2,y2);
	
} 



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Circle_Draw()     
* @Description   : ��Բ 
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
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
* --------------------------------------------  
* x1,y1,x2,y2 ���������Խ�����  
* mode�� 0 ����   1ʵ��
------------------------------------------------------------------------------*/  
void OS_Rect_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u16 color)
{	
	u16 temp=TextColor;
	TextColor=color;
	if(mode == 1)
	{
		for(;x2>=x1;x2--)
		OS_Lines_Draw(x2,y1,x2,y2);
		
	}
	else if(mode == 0)
	{
		OS_Lines_Draw(x1,y1,x2,y1);
		OS_Lines_Draw(x1,y2,x2,y2);
		OS_Lines_Draw(x2,y1,x2,y2);
		OS_Lines_Draw(x1,y1,x1,y2);
	}
	TextColor=temp;
} 


 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Coord_Draw()     
* @Description   : �������� 
* @Data          : 2016/3/22
* @Explain        
* -------------------------------------------- 
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
* --------------------------------------------  
* RGB565  16λ�����ʾ
* mode :  0 ���ɷ���      1 ������
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
} 

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()     
* @Description   : ��ӡ���� 
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y ����    *str ���ָ��   size �����С   
------------------------------------------------------------------------------*/ 
void  OS_String_Show(u16 x,u16 y,u8*str,u8 size)
{
 		
	Show_Str(x,y,size*10,size,str,size,0);  
	 
}





/**----------------------------------------------------------------------------
* @FunctionName  : OS_Decim_Show()     
* @Description   : ��ӡС�� 
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y ����    num ��ֵ   size �����С   
* digit ������Ч����     len ��ֵ�ܳ���
------------------------------------------------------------------------------*/ 
void OS_Decim_Show(u16 x,u16 y,double num,u8 digit,u8 len,u8 size)//���� ����.����
{ 
	
	LCD_ShowDecim( x, y, num, digit, len,size);
 
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Num_Show()     
* @Description   : ��ӡ����
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y ����    num ��ֵ   size �����С   
* len ��ֵ�ܳ���
------------------------------------------------------------------------------*/ 
void OS_Num_Show(u16 x,u16 y,u32 num,u8 len,u8 size)//���� ����.����
{ 
	
	LCD_ShowNum( x, y, num, len, size);
 
}

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





