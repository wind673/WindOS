/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Tools.c
* @Description : ϵͳ�Դ�С����
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     :  
-------------------------------------------------------------------------------
�汾�ţ�		WindOS3.2.01
�޶���¼��	
 @Date		@Version			@Revise					@Author
2017/10/16	WindOS3.2.01		�����ú���				Wind��л���죩

����޶���
�������� OStimer_usTimeOver_Is��OStimer_msTimeOver_Is��
OStimer_usTimeOver_Is��OStimer_msTimeOver_Is �ȳ��ú�����
*=============================================================================*/     

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Tools.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()
* @Description   : WindOS us��ʱ����
* @Data          : 2016/3/19
* @Explain       : ���� ��_us = ��ʱʱ��
------------------------------------------------------------------------------*/
void OSdelay_us(uint32_t _us)
{
    uint32_t _TimeNow = OStimer_us_Get(); 	
	if(_us > 6) _us -= 6;
	else return;
		
    while(!OStimer_usTimeOver_Is(_TimeNow,_us));	//�ȴ����
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()
* @Description   : WindOS ms��ʱ����
* @Data          : 2016/3/19
* @Explain       : ���� ��_ms = ��ʱʱ��
------------------------------------------------------------------------------*/
void OSdelay_ms(uint32_t _ms)
{ 
	while(_ms --)	
		OSdelay_us(998);
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_s()
* @Description   : WindOS s��ʱ����
* @Data          : 2016/3/19
* @Explain       : ���� ��_s = ��ʱʱ��
------------------------------------------------------------------------------*/
inline void OSdelay_s(uint32_t _s)
{   
	while(_s --)	
		OSdelay_ms(998);
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_us_Get()
* @Description   : ��ȡ��ǰʱ�� ��λus
* @Data          : 2016/3/19
* @Explain       : ���� ��ǰʱ��
------------------------------------------------------------------------------*/
inline uint32_t OStimer_us_Get(void)
{
    return OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_usTimeOver_Is()
* @Description   : �ж϶�ʱ���Ƿ����
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime����ʼʱ��
_Time����Ҫ��ʱʱ��(_Time < 2000 s)	��λ��us
���أ� ��� = 1
------------------------------------------------------------------------------*/
uint8_t OStimer_usTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{
    uint32_t Temp = OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
	
    if(Temp < _StartTime)  //Խ����
    {	
        _StartTime = 0;					
        Temp += (0xffffffff - _StartTime);	
    }	
	
    return (Temp - _StartTime > _Time) ? 1 : 0; //��ʱ����ʱ		

}

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_ms_Get()
* @Description   : ��ȡ��ǰʱ�� ��λms
* @Data          : 2016/3/19
* @Explain       : ���� ��ǰʱ��
------------------------------------------------------------------------------*/
inline uint32_t OStimer_ms_Get(void)
{	
    return (OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX)/1000;		
}	

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_msTimeOver_Is()
* @Description   : �ж϶�ʱ���Ƿ����
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime����ʼʱ��
_Time����Ҫ��ʱʱ��(_Time < 2000 s)	��λ��ms
���أ� ��� = 1
------------------------------------------------------------------------------*/
inline uint8_t OStimer_msTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{ 
	
	return OStimer_usTimeOver_Is(_StartTime*1000,_Time*1000);		 

}





/**----------------------------------------------------------------------------
* @FunctionName  : �ж���غ���
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
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
















