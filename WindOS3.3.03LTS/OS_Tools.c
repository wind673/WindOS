/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Tools.c
* @Description : 系统自带小工具
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     :  
------------------------------------------------------------------------------- 
修订记录：	
 @Date		@Version			@Revise					@Author
2017/10/16	V1.1.1				增添常用函数				Wind（谢玉伸） 
2017/11/03	V1.1.2				增添常用函数				Wind（谢玉伸） 

最后修订：
这次添加了常用函数：
Bsp_ChipID_Get //获取芯片ID（这是STM32L151CB的，其他型号或单片机请根据手册更换对应的地址）
Tools_Rand //根据芯片ID产生独特的伪随机码（可改成根据悬空AD产生真随机码）
Tools_CRC16//CRC校验
*=============================================================================*/     

/* 需要头文件 ----------------------------------------------------------------*/
#include "OS_Tools.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define CRC_16_POLYNOMIALS            0x8005 //CRC16多项式码

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u32 Tools_ChipID[3] = {0};

/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()
* @Description   : WindOS us延时函数
* @Data          : 2016/3/19
* @Explain       : 参数 ：_us = 延时时间
------------------------------------------------------------------------------*/
void OSdelay_us(uint32_t _us)
{
    uint32_t _TimeNow = OStimer_us_Get(); 	
	if(_us > 6) _us -= 6;	
	else return;	
	
    while(!OStimer_usTimeOver_Is(_TimeNow,_us));	//等待溢出
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()
* @Description   : WindOS ms延时函数
* @Data          : 2016/3/19
* @Explain       : 参数 ：_ms = 延时时间
------------------------------------------------------------------------------*/
void OSdelay_ms(uint32_t _ms)
{ 
	while(_ms --)	
		OSdelay_us(998);
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_s()
* @Description   : WindOS s延时函数
* @Data          : 2016/3/19
* @Explain       : 参数 ：_s = 延时时间
------------------------------------------------------------------------------*/
void OSdelay_s(uint32_t _s)
{   
	while(_s --)	
		OSdelay_ms(998);
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_us_Get()
* @Description   : 获取当前时间 单位us
* @Data          : 2016/3/19
* @Explain       : 返回 当前时间
------------------------------------------------------------------------------*/
uint32_t OStimer_us_Get(void)
{
    return OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_usTimeOver_Is()
* @Description   : 判断定时器是否溢出
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime：开始时间
_Time：需要定时时间(_Time < 2000 s)	单位：us
返回： 溢出 = 1
------------------------------------------------------------------------------*/
uint8_t OStimer_usTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{
    uint32_t Temp = OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
	
    if(Temp < _StartTime)  //越界了
    {	 	
        Temp += (0xffffffff - _StartTime);	
		_StartTime = 0;			
    }	
	
    return (Temp - _StartTime > _Time) ? 1 : 0; //定时器超时		

}

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_usTime_Distance()
* @Description   : 获取时间差距
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime：开始时间 
返回： 时间差距  单位：us
------------------------------------------------------------------------------*/
uint32_t OStimer_usTime_Distance(uint32_t _StartTime)
{
    uint32_t Temp = OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
	
    if(Temp < _StartTime)  //越界了
    {	 	
        Temp += (0xffffffff - _StartTime);	
		_StartTime = 0;			
    }	
	
    return Temp - _StartTime; //定时器超时	 
}



/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_ms_Get()
* @Description   : 获取当前时间 单位ms
* @Data          : 2016/3/19
* @Explain       : 返回 当前时间
------------------------------------------------------------------------------*/
uint32_t OStimer_ms_Get(void)
{	
    return (OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX)/1000;		
}	


/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_msTimeOver_Is()
* @Description   : 判断定时器是否溢出
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime：开始时间
_Time：需要定时时间(_Time < 2000 s)	单位：ms
返回： 溢出 = 1
------------------------------------------------------------------------------*/
uint8_t OStimer_msTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{ 	 
	return OStimer_usTimeOver_Is(_StartTime*1000,_Time*1000);		 

}


/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_msTime_Distance()
* @Description   : 获取时间差距
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime：开始时间 
返回： 时间距离  单位：ms
------------------------------------------------------------------------------*/
uint32_t OStimer_msTime_Distance(uint32_t _StartTime)
{ 	 
	return OStimer_usTime_Distance(_StartTime*1000)/1000;		 

}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_CRC16()
* @Description   : 判断定时器是否溢出
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
1. MSB first; 
2. Initial value is 0xAA;
------------------------------------------------------------------------------*/
uint16_t Tools_CRC16(uint8_t* Buff,uint16_t wDataLen) 
{
    uint16_t chChar;
    uint16_t wCRC = 0xAA,i,j;
	 
	for (j = 0; j < wDataLen;j ++)
    {	
        chChar = Buff[j];   
        wCRC ^= (((u16) chChar) << 8);
        for (i = 0; i < 8; i++)
        {	
            if (wCRC & 0x8000)
                wCRC = (wCRC << 1) ^ CRC_16_POLYNOMIALS;	
            else	
                wCRC <<= 1;		
        }	
    }	 
	
    return wCRC;
}


/**---------------------------------------------------------------------------- 
* @FunctionName  : Bsp_ChipID_Get()     			
* @Description   : STM32内部ID获取 				
* @Data          : 2017/11/2 
* @Explain       : ChipUniqueID :	传递数组地址（3*4Byte）					
------------------------------------------------------------------------------*/ 
void Tools_ChipID_Get(void)
{ 	 
    //地址从小到大,先放低字节，再放高字节：小端模式 
    //地址从小到大,先放高字节，再放低字节：大端模式 
	Tools_ChipID[0] = *(__IO u32 *)(ADDR_CHIPID_0); //L	
	Tools_ChipID[1] = *(__IO u32 *)(ADDR_CHIPID_1); //  	
	Tools_ChipID[2] = *(__IO u32 *)(ADDR_CHIPID_2); //M 	
}	



/**---------------------------------------------------------------------------- 
* @FunctionName  : Tools_Rand()     			
* @Description   : 产生一个独一无二的随机数			
* @Data          : 2017/11/2 
* @Explain       : range 取值范围		
------------------------------------------------------------------------------*/ 
u32 Tools_Rand(u32 RangeMin,u32 RangeMax)
{
	u32 TempRand = 0;
	if(RangeMax <= RangeMin) return rand(); 
	
	TempRand = (rand()^Tools_ChipID[0]^Tools_ChipID[1]^Tools_ChipID[2])%(RangeMax - RangeMin) + RangeMin;
	
	return TempRand;
}




/**----------------------------------------------------------------------------
* @FunctionName  : 中断相关函数
* @Description   : None
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}





 






/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
















