/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_UI_Hal.c
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
#include "OS_UI_Hal.h"
#include "OS_UI.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_LCD_Init()
* @Description   : 初始化函数
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
int OS_LCD_Init(void)
{
    TFT_LCD_Init(); 
    LCD_Clear(BLACK);//清屏
    if(font_init())
    {
        OS_String_Show(400, 200, 32, 1, "Font Error!!!"); //检查字库
        return -1;
    }
    TextColor = WHITE;
    BackColor = BLACK;

    return 0;

}

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
* @FunctionName  : OS_LCD_Clear()
* @Description   : None
* @Data          : 2016/7/12
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
int OS_LCD_Clear(u16 color)
{   
    LCD_Clear(color); 
    return 0;
}



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Point_Draw()
* @Description   : 画点
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
* x,y:坐标
* POINT_COLOR:此点的颜色
------------------------------------------------------------------------------*/
int OS_Point_Draw(u16 x, u16 y, u16 color)
{ 
    LCD_SetCursor(x, y); //设置光标位置
    LCD_WriteRAM_Prepare();
    LCD_WriteRAM(color); 
    return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Char_Show()
* @Description   : 打印字符
* @Data          : 2016/7/14
* @Explain
-------------------------------------------------------------------------------
在指定位置显示一个字符
x,y:起始坐标
num:要显示的字符:" "--->"~"
size:字体大小 16/24/32
mode:叠加方式(1)还是非叠加方式(0)
------------------------------------------------------------------------------*/
void OS_Char_Show(u16 x, u16 y, u8 num, u8 size, u8 mode)
{
    u8 temp, t1, t;
    u16 y0 = y;
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);		//得到字体一个字符对应点阵集所占的字节数
    //设置窗口
    num = num - ' '; //得到偏移后的值
    for(t = 0; t < csize; t++)
    {
        if(size == 16)temp = asc2_1608[num][t];	//调用1608字体
        else if(size == 24)temp = asc2_2412[num][t]; //调用2412字体
        else if(size == 32)temp = asc2_3216[num][t]; //调用3216字体
        else return;//没有的字库
        for(t1 = 0; t1 < 8; t1++)
        {
            if(temp & 0x80)OS_Point_Draw(x, y, TextColor);
            else if(mode == 1)OS_Point_Draw(x, y, BackColor);
            temp <<= 1;
            y++;
            if(y >= 480)return;		//超区域了
            if((y - y0) == size)
            {
                y = y0;
                x++;
                if(x >= 800)return;	//超区域了
                break;
            }
        }
    }
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()
* @Description   : 打印句子
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
* x,y 坐标    *code 语句指针   size 字体大小
------------------------------------------------------------------------------*/
void OS_HzMat_Get(char *code, uint8_t *mat, u8 size)
{
    uint8_t qh, ql;
    uint8_t i;
    uint32_t foffset;

    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size); //得到字体一个字符对应点阵集所占的字节数
    qh = *code;
    ql = *(++code);
    if(qh < 0x81 || ql < 0x40 || ql == 0xff || qh == 0xff) //非常用汉字
    {
        for(i = 0; i < csize; i++)*mat++ = 0x00; //填充满格
        return; //结束访问
    }
    if(ql < 0x7f)ql -= 0x40; //注意!
    else ql -= 0x41;
    qh -= 0x81;
    foffset = ((uint32_t)190 * qh + ql) * csize;	//得到字库中的字节偏移量
    switch(size)
    {
    case 32:
        W25Q64_Read(mat, foffset + ftinfo.f12addr, csize);
        break;
    case 16:
        W25Q64_Read(mat, foffset + ftinfo.f16addr, csize);
        break;
    case 24:
        W25Q64_Read(mat, foffset + ftinfo.f24addr, csize);
        break;

    }
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Font_Show()
* @Description   : 打印句子
* @Data          : 2016/3/22
* @Explain
-------------------------------------------------------------------------------
* x,y 坐标    *str 语句指针   size 字体大小
------------------------------------------------------------------------------*/
void OS_Font_Show(u16 x, u16 y, char *font, u8 size, u8 mode)
{
    u8 temp, t, t1;
    u16 y0 = y;
    u8 dzk[144];
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size); //得到字体一个字符对应点阵集所占的字节数
    if(size != 32 && size != 16 && size != 24) return;	//不支持的size
    OS_HzMat_Get(font, dzk, size);	//得到相应大小的点阵数据
    for(t = 0; t < csize; t++)
    {
        temp = dzk[t];			//得到点阵数据
        for(t1 = 0; t1 < 8; t1++)
        {
            if(temp & 0x80) OS_Point_Draw(x, y, TextColor);
            else if(mode == 1) OS_Point_Draw(x, y, BackColor);
            temp <<= 1;
            y++;
            if((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

 


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



















