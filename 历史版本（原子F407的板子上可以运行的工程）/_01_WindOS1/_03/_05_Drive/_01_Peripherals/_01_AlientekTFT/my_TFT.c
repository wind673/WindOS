//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//

//TFT显示屏文件
#include "my_TFT.h"  

__IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;


void TFT_Init(void)
{
	

//***************************************************************************	
 	LCD_Init();					//LCD初始化  
    font_init();//检查字库
	LCD_Clear(WHITE);//清屏	
	
//***************************************************************************
	
	
	
	
}




//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
//=========================================================================
void LCD_DrawPoints(u16 x,u16 y)
{
LCD_Fast_DrawPoint(x,y,TextColor);
}
//=========================================================================



//画线
//x1,y1:起点坐标
//x2,y2:终点坐标
//=========================================================================
void LCD_DrawLines(u16 x1, u16 y1, u16 x2, u16 y2)
{
	
LCD_DrawLine(x1, y1,x2,y2);
}
//=========================================================================


//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
////=========================================================================
//void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
//{	
//	uint32_t x,y;

//	for(y=y1;y<y2;y++)
//	{
//		LCD_SetCursor(x1,y);			
//		LCD_WriteRAM_Prepare();
//		
//		for(x=x1;x<x2;x++)
//		LCD->LCD_RAM =color;
//	}
//	
//}
////=========================================================================


////显示字符串
////x y 起始坐标
////*p:字符串起始地址	
////=========================================================================
//void LCD_ShowString(u16 x,u16 y,u8 *p)
//{
//LCD_DisplayStringLine(y,x,p);
//}
////=========================================================================



////x,y:起点坐标
////digit:保留位数
////num:数值(0~4294967295).
////size:字体大小  12/16/24/90(预留位，暂时不能实现)
////=========================================================================
//void LCD_ShowNum(u16 x,u16 y,double num,u8 digit,u8 size)
//{
//	u8 ch_inte[50]={0},ch_deci[50]={0};
//	int i=0,_0=0;
//	u32 integer=(u32)num,temp=integer,decimal=0,len_inte=0,len_deci=0,temp1=0,temp0=temp,digit0=digit;
//	double temp01=num;
//	
//	temp01*=10;
//	temp0*=10;
//	while((--digit0)&&(u32)(temp01-temp0)==0)
//	{	
//		_0++;
//		temp01*=10;
//		temp0*=10;
//		
//	}
//	
//	while(digit--)
//	num*=10,temp*=10;
//	decimal=(u32)(num-temp);
//	temp=integer;
//	while(temp/=10) len_inte++;
//	temp=decimal;
//	while(temp/=10) len_deci++;
//	
//	temp=len_inte;
//	temp1=len_deci;
//	for(i=len_inte;i>=0;i--) ch_inte[i]='0'+integer%10,integer/=10;
//	
//	for(i=len_deci+_0;i>=_0;i--) ch_deci[i]='0'+decimal%10,decimal/=10;
//	for(i=_0-1;i>=0;i--)  ch_deci[i]='0';
//	
//	len_inte=temp+1;
//	Show_String(x,y,ch_inte,size);
//	
//	if(temp1!=0)
//	{	
//		
//		
//	if(size==16)
//	{
//	Show_String(x+len_inte*8+7,y,ch_deci,size);
//	Show_String(x+len_inte*8+1,y,".",size);
//	}	
//	else if(size==24)
//	{
//	Show_String(x+len_inte*8+7,y,ch_deci,size);
//	Show_String(x+len_inte*8+1,y,".",size);
//	}
//	else
//	{
//	Show_String(x+len_inte*16+14,y,ch_deci,32);
//	Show_String(x+len_inte*16,y,".",32);
//	}

//	
//	}
//	
//}
////=========================================================================



//画实心圆点
//(x,y):中心点
//size:圆点的的大小
//=========================================================================
void LCD_Big_Point(u16 x,u16 y,u16 size,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	if (x<=size) x=size+1;
	for(;size>0;size--)
	LCD_Draw_Circle(x,y,size);
	TextColor=temp;
}
//=========================================================================




//画实心矩形
//x,y,xi,yi 矩形四个角
//=========================================================================
void LCD_Big_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{	
	u16 temp=TextColor;
	TextColor=color;
	for(;x2>=x1;x2--)
	LCD_DrawLines(x2,y1,x2,y2);
	TextColor=temp;
}
//=========================================================================


//画空心矩形
//x,y,xi,yi 矩形四个角
//=========================================================================
void Draw_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 tc=TextColor,bc=BackColor;
	TextColor=color;
	LCD_DrawLines(x1,y1,x2,y1);
	LCD_DrawLines(x1,y2,x2,y2);
	LCD_DrawLines(x2,y1,x2,y2);
	LCD_DrawLines(x1,y1,x1,y2);
	TextColor=tc;
}
//=========================================================================

 


//创建坐标
//mode 是否重写边框 1写   0不写
//=========================================================================
void Creat_Coord(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode)
{
	u16 x=0,y=0;					
	density=(density+1)/10;
	if(mode==1)	      			
	{LCD_Fill(x1,y1,x2,y2,BLACK);}	//写边框		
												
	LCD_Fill(x1+density*5,y1+density*5,x2-density*5,y2-density*5,WHITE); //写背景						
	
	//画小点
	for(x=x1;x<x2;x+=10*density)													
	for(y=y1;y<y2;y+=10*density)							
	{LCD_Big_Point(x,y,1,GRAY);}		
																			
	//画大点
	for(x=x1;x<x2;x+=50*density)													
	for(y=y1;y<y2;y+=50*density)							
	{LCD_Big_Point(x,y,2,BLACK);}		
		
	//画左右边框点
	for(y=y1+10*density;y<y2;y+=10*density)							
	{
	LCD_Big_Rect(x1+density*5,y,x1+density*8,y+density,BLACK);//左
	LCD_Big_Rect(x2-density*8,y,x2-density*5,y+density,BLACK);//右
	}
	//画上下边框点
	for(x=x1+10*density;x<x2;x+=10*density)							
	{
	LCD_Big_Rect(x,y1+density*5,x+density,y1+density*8,BLACK);//上
	LCD_Big_Rect(x,y2-density*5,x+density,y2-density*8,BLACK);//下
	}
	
	
	
	
}
//=========================================================================



//显示图片
//RGB565  16位真彩显示
//不可放缩
//带头数据
//=========================================================================
void Show_Picture0(u16 x1,u16 y1,const u8 *pic)
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
//=========================================================================



//显示图片
//RGB565  16位真彩显示
//可放缩
//带头数据
//=========================================================================
void Show_Picture1(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic)
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

//=========================================================================



//=========================================================================
void  Show_String(uint16_t x,uint16_t y,u8*str,u8 size)
{

			
 Show_Str(x,y,size*10,size,str,size,0);
	
	
}


//=========================================================================

	
////=========================================================================
//void LCD_Fonts_Init(void)
//{
//	
//	LCD_Init();
//	font_init();
//	 
//	LCD_Clear(Black);
// 
//	
//}

////=========================================================================





//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//
