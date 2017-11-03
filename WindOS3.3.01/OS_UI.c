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
*  ��Ҫʹ��OS_UI ��Ҫ������OS_UI_Hal�ĵײ�����
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_UI.h"
#include "OS_UI_Hal.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Line_Draw()
* @Description   : ����
* @Data          : 2016/7/14
* @Explain
-------------------------------------------------------------------------------
x1,y1	:�������
x2,y2	:�յ�����
size	:�������
------------------------------------------------------------------------------*/
int OS_Line_Draw(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol; 
    if(x1 == x2 && y1 == y2) x1 = x2 + 1;
 
    delta_x = x2 - x1; //������������
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if(delta_x > 0)incx = 1; //���õ�������
    else if(delta_x == 0)incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if(delta_y > 0)incy = 1;
    else if(delta_y == 0)incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if( delta_x > delta_y)distance = delta_x; //ѡȡ��������������
    else distance = delta_y;
    for(t = 0; t <= distance + 1; t++ ) //�������
    {
        OS_Point_Draw(uRow, uCol, color); //����
        xerr += delta_x ;
        yerr += delta_y ;
        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
 
    return 0;
}




/**----------------------------------------------------------------------------
* @FunctionName  : OS_Circle_Draw()
* @Description   : ��Բ
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
(x,y)		:���ĵ�
r			:Բ�İ뾶
size		:�����Ŀ��  	0,��ʾʵ��
------------------------------------------------------------------------------*/
int OS_Circle_Draw(u16 x, u16 y, u8 r, u8 size, u16 color)
{
    u16 temp = TextColor; 

    TextColor = color;
    if(size == 0)
    {
        LCD_DrawCircleS(x, y, r, color);
    }
    else
    {
        while(size--)
            LCD_DrawCircle(x, y, r - size);
    }
    TextColor = temp;
	
    return 0;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Rect_Draw()
* @Description   : ������
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
x1,y1,x2,y2 ���������Խ�����
size		���������   0,��ʾʵ��
------------------------------------------------------------------------------*/
int OS_Rect_Draw(u16 x1, u16 y1, u16 x2, u16 y2, u8 size, u16 color)
{
    u16 temp = TextColor; 
	 
    TextColor = color;
    if(size == 0)
    {
        LCD_DrawRectS(x1, y1, x2, y2, color);

    }
    else
    {
        while(size --)
        {
            OS_Line_Draw(x1, y1 + size, x2, y1 + size, color);
            OS_Line_Draw(x1, y2 - size, x2, y2 - size, color);
            OS_Line_Draw(x2 - size, y1, x2 - size, y2, color);
            OS_Line_Draw(x1 + size, y1, x1 + size, y2, color);
        }
    }
    TextColor = temp;
 
    return 0;
}



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Picture_Draw()
* @Description   : ��ʾͼƬ
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
* RGB565  16λ�����ʾ
* mode :  0 ���ɷ���      1 ������       2 �����ţ�����ʾ��ɫ
		  3 �����ţ�����ʾ��ɫ,�ұ��
* ��ͷ����
------------------------------------------------------------------------------*/
int OS_Picture_Draw(u16 x1, u16 y1, u16 x2, u16 y2, u8 mode, const u8 *pic)
{
    u16 temp = TextColor;
    static u8 UeseState = 0;

    if(UeseState) return -1;
    UeseState = 1;

    if(mode == 0)
    {
        u16 x, y, p_color;
        u16 len_x = (pic[2] << 8) | pic[3];
        u16 len_y = (pic[4] << 8) | pic[5];

        for(y = 0; y < len_y; y++)
            for(x = 0; x < len_x * 2; x += 2)
            {
                if((u16)(x / 2 + x1) <= x2)
                    if((u16)(y + y1) <= y2)
                    {
                        p_color = pic[x + 6 + y * len_x * 2] << 8 | pic[(x + 7) + y * len_x * 2];

                        LCD_SetCursor(x / 2 + x1, y + y1); //���ù��λ��
                        LCD_WriteRAM_Prepare();
                        LCD_WriteRAM(p_color);
                    }
            }
    }
    else if(mode == 1)
    {
        u16 x, y, p_color;
        float density_x, density_y;
        u16 len_x = (pic[2] << 8) | pic[3];
        u16 len_y = (pic[4] << 8) | pic[5];

        density_x = (float)(x2 - x1) / len_x;
        density_y = (float)(y2 - y1) / len_y;

        for(y = 0; y < len_y; y++)
            for(x = 0; x < len_x * 2; x += 2)
            {
                if((u16)((x / 2)*density_x + x1) <= x2)
                    if((u16)(y * density_y + y1) <= y2)
                    {
                        p_color = pic[x + 6 + y * len_x * 2] << 8 | pic[(x + 7) + y * len_x * 2];
                        LCD_SetCursor((x / 2)*density_x + x1, y * density_y + y1); //���ù��λ��
                        LCD_WriteRAM_Prepare();
                        LCD_WriteRAM(p_color);
                    }

            }

    }

    else if(mode == 2)
    {
        u16 x, y, p_color;
        float density_x, density_y;
        u16 len_x = (pic[2] << 8) | pic[3];
        u16 len_y = (pic[4] << 8) | pic[5];

        density_x = (float)(x2 - x1) / len_x;
        density_y = (float)(y2 - y1) / len_y;

        for(y = 0; y < len_y; y++)
            for(x = 0; x < len_x * 2; x += 2)
            {
                if((u16)((x / 2)*density_x + x1) <= x2)
                    if((u16)(y * density_y + y1) <= y2)
                    {
                        p_color = pic[x + 6 + y * len_x * 2] << 8 | pic[(x + 7) + y * len_x * 2];
                        if(p_color > 1) //����ʾ��ɫ����
                        {
                            LCD_SetCursor((x / 2)*density_x + x1, y * density_y + y1); //���ù��λ��
                            LCD_WriteRAM_Prepare();
                            LCD_WriteRAM(p_color);
                        }
                    }

            }
    }

    else if(mode == 3)
    {
        u16 x, y, p_color, BitRed, BitGreen, BitBlue;
        float density_x, density_y;
        u16 len_x = (pic[2] << 8) | pic[3];
        u16 len_y = (pic[4] << 8) | pic[5];

        density_x = (float)(x2 - x1) / len_x;
        density_y = (float)(y2 - y1) / len_y;

        for(y = 0; y < len_y; y++)
            for(x = 0; x < len_x * 2; x += 2)
            {
                if((u16)((x / 2)*density_x + x1) <= x2)
                    if((u16)(y * density_y + y1) <= y2)
                    {
                        p_color = pic[x + 6 + y * len_x * 2] << 8 | pic[(x + 7) + y * len_x * 2];
                        if(p_color > 1) //����ʾ��ɫ����
                        {
                            p_color = pic[x + 6 + y * len_x * 2] << 8 | pic[(x + 7) + y * len_x * 2];
                            BitRed   = (p_color & (0x1f << 11)) >> 11;
                            BitGreen = (p_color & (0x3f << 5 )) >> 5;
                            BitBlue = p_color & 0x1f;
                            p_color = ((BitRed / 3) << 11) | ((BitGreen / 3) << 5) | (BitBlue / 3);

                            LCD_SetCursor((x / 2)*density_x + x1, y * density_y + y1); //���ù��λ��
                            LCD_WriteRAM_Prepare();
                            LCD_WriteRAM(p_color);
                        }
                    }

            }

    }
    TextColor = temp;

    UeseState = 0;
    return 0;
}







/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()
* @Description   : ��ӡ����
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
x,y 		����
str 		���ָ��
size 		�����С 16 24 32
mode 		0,�ޱ���ɫ��1������ɫ
return 		0,��ӡ���		-1,��ӡ��ռ��
------------------------------------------------------------------------------*/
int OS_String_Show(u16 x, u16 y, u8 size, u8 mode, char *str)
{
    uint16_t x0 = x;
    uint8_t bHz = 0;   //�ַ���������
 

    while(*str != 0)		//����δ����
    {

        if(!bHz)
        {
            if((signed char)*str < 0)bHz = 1; //����
            else              //�ַ�
            {
                if(*str == '\n') //���з���
                {
                    y += size;
                    x = x0;
                    str++;
                }
                OS_Char_Show(x, y, *str, size, mode);
                str++;
                x += size / 2; //�ַ�,Ϊȫ�ֵ�һ��
            }
        }
        else //����
        {
            bHz = 0; //�к��ֿ�
            OS_Font_Show(x, y, str, size, mode);
            str += 2;
            x += size; //��һ������ƫ��
        }
    }
 
    return 0;
}




/**----------------------------------------------------------------------------
* @FunctionName  : OS_Num_Show()
* @Description   : �๦�ܴ�ӡ��ֵ
* @Data          : 2017/7/12
* @Explain
-------------------------------------------------------------------------------
x,y 		����
num 		��ֵ
size 		�����С 12 16 24 32
mode 		0,�ޱ���ɫ��1������ɫ
format		--------------------------------
			%d ʮ�����з�����������BUG������%0.0f���
			%u ʮ�����޷�������
			%f ������	%lf ��������
			%s �ַ���
			%c �����ַ�
			%p ָ���ֵ
			%e ָ����ʽ�ĸ�����
			%x,%X �޷�����ʮ�����Ʊ�ʾ������
			%o �޷����԰˽��Ʊ�ʾ������
			%g,NULL �Զ�ѡ����ʵı�ʾ��
			%p �����ַ��
			--------------------------------
return 		0,��ӡ���		-1,��ӡ��ռ��
ע��format����������÷������磺"ʱ�䣺%0.0f ms"
------------------------------------------------------------------------------*/
int OS_Num_Show(u16 x, u16 y, u8 size, u8 mode, double num, char *format)
{ 
    char temp[100] = {0}; 

    if(format == NULL) sprintf(temp, "%g", num); //�Զ�ѡ���ʽ
    else sprintf(temp, format, num);

    OS_String_Show(x, y, size, mode, temp);
	
	return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Wave_Draw()
* @Description   : ��������Ϻ���
* @Data          : 2017/7/13
* @Explain
-------------------------------------------------------------------------------
Struct_OSC��--------------------------------
			u16 x,y;//OSC���ڵ�λ�� 
			float ZoomWindows;//��ʾ����������
			u16 BackColor;//������ɫ
			
			float ShiftX; //����ƫ����	1.0�Ǳ�׼��
			float ShiftY; //����ƫ����
			float ZoomX;  //����������
			float ZoomY;  //����������
			u16 LineColor;//������ɫ
			u8 LineSize;//������ϸ�ĳߴ�
			u8 Mode;//	OSC_MODE_NORMAL:����ʾ��� 	OSC_MODE_FFT����ʾ�����FFTģʽ��
			u16 BuffLenth;//����
			u8 BuffFormat;//Buff�ĸ�ʽ
			u16 *Buff_u16;
			u8 *Buff_u8;
			float *Buff_float;
			double *Buff_double; 
			--------------------------------
mode		--------------------------------
			OSC_MODE_WINDOWS_SHOW	//������
            OSC_MODE_LINE_SHOW		//���� 
			--------------------------------
return 		0,��ӡ���		-1,��ӡ��ռ��	-2,���δ���
ע�⣺double float �����ݵ�����������룻��u8 u16 �����ݵ�����ڵ׶�
------------------------------------------------------------------------------*/
int OS_Wave_Windows_Show(Type_OSC *Struct_OSC)
{ 
    u16 x1 = Struct_OSC->x;
    u16 y1 = Struct_OSC->y;
    u16 x2 = Struct_OSC->x + OS_LCD_WHITH * Struct_OSC->ZoomWindows;
    u16 y2 = Struct_OSC->y + OS_LCD_HEIGHT* Struct_OSC->ZoomWindows;
    u8 size = 10 * Struct_OSC->ZoomWindows;
    u16 i = 0;
    u16 cnt = 0;
 
    /* ���߿򼰱��� --------------------------------------*/
    if(size < 1) size = 1;
    OS_Rect_Draw(x1 + size, y1 + size, x2 - size - 1, y2 - size - 1, 0, Struct_OSC->BackColor); //����
    OS_Rect_Draw(x1, y1, x2 - 1, y2 - 1, size, Struct_OSC->WindowsColor); //����
    OS_Line_Draw(x1 + 1, y2, x2, y2 - 1, (Struct_OSC->WindowsColor / 2)); //��Ӱ
    OS_Line_Draw(x2, y1 + 1, x2, y2, (Struct_OSC->WindowsColor / 2)); //��Ӱ

    /* ��� ---------------------------------------------*/
    for(i = y1 + size - 1; i < y2 - size; i += size) //Y��
    {
        cnt = (cnt + 1) % 5;
        if(cnt == 0)
        {
            OS_Line_Draw(x1 + size, i, x1 + size * 3, i, Struct_OSC->WindowsColor);
            OS_Line_Draw(x2 - size * 3, i, x2 - size, i, Struct_OSC->WindowsColor);
        }
        else
        {
            OS_Line_Draw(x1 + size, i, x1 + size * 2, i, Struct_OSC->WindowsColor);
            OS_Line_Draw(x2 - size * 2, i, x2 - size, i, Struct_OSC->WindowsColor);
        }
    }

    for(i = x1 + size - 1; i < x2 - size; i += size) //X��
    {
        cnt = (cnt + 1) % 5;
        if(cnt == 0)
        {
            OS_Line_Draw(i, y1 + size, i, y1 + size * 3, Struct_OSC->WindowsColor);
            OS_Line_Draw(i, y2 - size * 3, i, y2 - size, Struct_OSC->WindowsColor);
        }
        else
        {
            OS_Line_Draw(i, y1 + size, i, y1 + size * 2, Struct_OSC->WindowsColor);
            OS_Line_Draw(i, y2 - size * 2, i, y2 - size, Struct_OSC->WindowsColor);
        }
    }
 
    return 0;

}





int OS_Wave_Line_Show(Type_OSC *Struct_OSC)
{ 
    u8 size = 10 * Struct_OSC->ZoomWindows;
    u16 x1 = Struct_OSC->x + size * 3 + Struct_OSC->LineSize + 3;
    u16 y1 = Struct_OSC->y + size * 3 + Struct_OSC->LineSize + 3;
    u16 x2 = Struct_OSC->x + OS_LCD_WHITH * Struct_OSC->ZoomWindows - size * 3 - Struct_OSC->LineSize - 3;
    u16 y2 = Struct_OSC->y + OS_LCD_HEIGHT* Struct_OSC->ZoomWindows - size * 3 - Struct_OSC->LineSize - 3;
    u16 i = 0, j = 0;
    u16 mid_y = (y1 + y2) / 2;
    u16 WD_lenth = x2 - x1;
    u16 t_x1 = 0, t_y1 = 0, t_x2 = 0, t_y2 = 0;
    u16 ZeroLine = 0;
	 
	 
    for(i = 0; i < WD_lenth - 1; i ++)
    {
        /* �����һ�εĺۼ� ----------------------------------------*/  
		if(Struct_OSC ->LastMode != OSC_MODE_ERROR)
		{
			 if(Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1] >= y1//��ֹԽ������
				 && Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1 + 1] >= y1
				 && Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1] <= y2
				 && Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1 + 1] <= y2) 
			 {
				 if(Struct_OSC ->LastMode == OSC_MODE_NORMAL)
				 {
					for(j = 0; j < Struct_OSC->LastLineSize; j++) 
					 {
						 OS_Line_Draw(i + x1 - j, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1], i + x1 + 1 - j, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1 + 1], Struct_OSC->BackColor);
						 OS_Line_Draw(i + x1 + j, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1], i + x1 + 1 + j, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1 + 1], Struct_OSC->BackColor);
						 OS_Line_Draw(i + x1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1] + j, i + x1 + 1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1 + 1] + j, Struct_OSC->BackColor);
						 OS_Line_Draw(i + x1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1] - j, i + x1 + 1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1 + 1] - j, Struct_OSC->BackColor);
					 }
				 }
				 else if(Struct_OSC ->LastMode == OSC_MODE_FFT)
				 {
					if(Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1] < ZeroLine)
						OS_Line_Draw(i + x1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1], i + x1, Struct_OSC->LastZeroLine + 1, Struct_OSC->BackColor);
					else if(Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1] > ZeroLine) 
						OS_Line_Draw(i + x1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1], i + x1, Struct_OSC->LastZeroLine + 3, Struct_OSC->BackColor);
						
					 OS_Line_Draw(i + x1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1], i + x1 + 1, Struct_OSC->LastBuff[Struct_OSC->LastBuff_Cnt][i + x1+1], Struct_OSC->BackColor); 
				 } 
				
				if(Struct_OSC->LastZeroLine >= y1 && Struct_OSC->LastZeroLine <= y2)//��ֹԽ������
				{
					OS_Point_Draw(i + x1 + 1, Struct_OSC->LastZeroLine + 1, Struct_OSC->BackColor);
					OS_Point_Draw(i + x1 + 1, Struct_OSC->LastZeroLine + 2, Struct_OSC->BackColor);
					OS_Point_Draw(i + x1 + 1, Struct_OSC->LastZeroLine + 3, Struct_OSC->BackColor);
				}
			 }
		}
		
        /* ����ת�� ------------------------------------------*/
        t_x1 = x1 + i / Struct_OSC->ZoomX - Struct_OSC->ShiftX;
        t_x2 = x1 + (i + 1) / Struct_OSC->ZoomX - Struct_OSC->ShiftX;

        if((t_x1 < Struct_OSC->BuffLenth) && (t_x2 < Struct_OSC->BuffLenth))
        {
            if(Struct_OSC->BuffFormat == OSC_FORMAT_U8)
            {
                t_y1 = y2 - Struct_OSC->Buff_u8[t_x1] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                t_y2 = y2 - Struct_OSC->Buff_u8[t_x2] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                ZeroLine = y2 - Struct_OSC->ShiftY;
            }
            else if(Struct_OSC->BuffFormat == OSC_FORMAT_U16)
            {
                t_y1 = y2 - Struct_OSC->Buff_u16[t_x1] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                t_y2 = y2 - Struct_OSC->Buff_u16[t_x2] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                ZeroLine = y2 - Struct_OSC->ShiftY;
            }
            else if(Struct_OSC->BuffFormat == OSC_FORMAT_FLOAT)
            {
                t_y1 = mid_y - Struct_OSC->Buff_float[t_x1] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                t_y2 = mid_y - Struct_OSC->Buff_float[t_x2] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                ZeroLine = mid_y - Struct_OSC->ShiftY;
            }
            else if(Struct_OSC->BuffFormat == OSC_FORMAT_DOUBLE)
            {
                t_y1 = mid_y - Struct_OSC->Buff_double[t_x1] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                t_y2 = mid_y - Struct_OSC->Buff_double[t_x2] * Struct_OSC->ZoomY - Struct_OSC->ShiftY;
                ZeroLine = mid_y - Struct_OSC->ShiftY;
            }

            /* ��ֹ��ͼԽ�� ------------------------------------------*/
            if(t_y1 < y1) t_y1 = y1;
            else if(t_y1 > y2)  t_y1 = y2;

            if(t_y2 < y1) t_y2 = y1;
            else if(t_y2 > y2)  t_y2 = y2;

            /* �����εĲ��� ------------------------------------------*/
            if(t_x1 != 0 && t_x2 != 0)
            {
                if(Struct_OSC->Mode == OSC_MODE_NORMAL)//����
                {
                    for(j = 0; j < Struct_OSC->LineSize; j++)
                    {
                        OS_Line_Draw(i + x1, t_y1 + j, i + x1 + 1, t_y2 + j, Struct_OSC->LineColor);
                        OS_Line_Draw(i + x1, t_y1 - j, i + x1 + 1, t_y2 - j, Struct_OSC->LineColor);
                        OS_Line_Draw(i + x1 + j, t_y1 , i + x1 + 1 + j, t_y2 , Struct_OSC->LineColor);
                        OS_Line_Draw(i + x1 - j, t_y1 , i + x1 + 1 - j, t_y2 , Struct_OSC->LineColor);
                    }
                }
                if(Struct_OSC->Mode == OSC_MODE_FFT)//�����
                {
					if(t_y1 < ZeroLine)
						OS_Line_Draw(i + x1, t_y1, i + x1, ZeroLine + 1, Struct_OSC->LineColor);
					else if(t_y1 > ZeroLine)
						OS_Line_Draw(i + x1, t_y1, i + x1, ZeroLine + 3, Struct_OSC->LineColor);
					
                    OS_Line_Draw(i + x1, t_y1, i + x1 + 1, t_y2, ~Struct_OSC->LineColor);
                }
            } 
			
			if((ZeroLine >= y1 && ZeroLine <= y2))
			{
				OS_Point_Draw(i + x1 + 1, ZeroLine + 1, ~BLACK);//�����
				OS_Point_Draw(i + x1 + 1, ZeroLine + 2, BLACK);
				OS_Point_Draw(i + x1 + 1, ZeroLine + 3, ~BLACK);
			}
            /* ��¼��β��ε�λ�� ---------------------------------*/
            if(i == 0)
            {
                Struct_OSC->LastBuff[(Struct_OSC->LastBuff_Cnt + 1) % 2][x1] = t_y1;
            }
            Struct_OSC->LastBuff[(Struct_OSC->LastBuff_Cnt + 1) % 2][i + x1 + 1] = t_y2;
            Struct_OSC->LastZeroLine = ZeroLine;
        }
		else 
		{
			Struct_OSC ->LastMode = OSC_MODE_ERROR;
		}

    }
    /* ��¼������ò��� ---------------------------------*/
    Struct_OSC->LastBuff_Cnt = (Struct_OSC->LastBuff_Cnt + 1) % 2;
    Struct_OSC->LastLineSize = Struct_OSC->LineSize;
    Struct_OSC->LastMode = Struct_OSC->Mode;
	
    return 0;
}

int OS_Wave_Unite(Type_OSC *Struct_OSC_Source, Type_OSC *Struct_New)
{
	if(Struct_New != NULL && Struct_OSC_Source != NULL)
	{
		Struct_New->ZoomWindows = Struct_OSC_Source->ZoomWindows;
		Struct_New->BackColor = Struct_OSC_Source->BackColor;
		Struct_New->WindowsColor = Struct_OSC_Source->WindowsColor;
		Struct_New->x = Struct_OSC_Source->x;
		Struct_New->y = Struct_OSC_Source->y;
		return 0;
	}
	
	return -1; 
}

int OS_Wave_Draw(Type_OSC *Struct_OSC, u8 mode)
{
    if(mode == OSC_MODE_WINDOWS_SHOW)
        return OS_Wave_Windows_Show(Struct_OSC);
    else if(mode == OSC_MODE_LINE_SHOW)
        return OS_Wave_Line_Show(Struct_OSC);
    else return -2;

}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



















