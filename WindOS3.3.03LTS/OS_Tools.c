/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Tools.c
* @Description : ϵͳ�Դ�С����
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     :  
------------------------------------------------------------------------------- 
�޶���¼��	
 @Date		@Version			@Revise					@Author
2017/10/16	V1.1.1				�����ú���				Wind��л���죩 
2017/11/03	V1.1.2				�����ú���				Wind��л���죩 

����޶���
�������˳��ú�����
Bsp_ChipID_Get //��ȡоƬID������STM32L151CB�ģ������ͺŻ�Ƭ��������ֲ������Ӧ�ĵ�ַ��
Tools_Rand //����оƬID�������ص�α����루�ɸĳɸ�������AD����������룩
Tools_CRC16//CRCУ��
*=============================================================================*/     

/* ��Ҫͷ�ļ� ----------------------------------------------------------------*/
#include "OS_Tools.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
#define CRC_16_POLYNOMIALS            0x8005 //CRC16����ʽ��

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
u32 Tools_ChipID[3] = {0};

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
void OSdelay_s(uint32_t _s)
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
uint32_t OStimer_us_Get(void)
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
        Temp += (0xffffffff - _StartTime);	
		_StartTime = 0;			
    }	
	
    return (Temp - _StartTime > _Time) ? 1 : 0; //��ʱ����ʱ		

}

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_usTime_Distance()
* @Description   : ��ȡʱ����
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime����ʼʱ�� 
���أ� ʱ����  ��λ��us
------------------------------------------------------------------------------*/
uint32_t OStimer_usTime_Distance(uint32_t _StartTime)
{
    uint32_t Temp = OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
	
    if(Temp < _StartTime)  //Խ����
    {	 	
        Temp += (0xffffffff - _StartTime);	
		_StartTime = 0;			
    }	
	
    return Temp - _StartTime; //��ʱ����ʱ	 
}



/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_ms_Get()
* @Description   : ��ȡ��ǰʱ�� ��λms
* @Data          : 2016/3/19
* @Explain       : ���� ��ǰʱ��
------------------------------------------------------------------------------*/
uint32_t OStimer_ms_Get(void)
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
uint8_t OStimer_msTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{ 	 
	return OStimer_usTimeOver_Is(_StartTime*1000,_Time*1000);		 

}


/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_msTime_Distance()
* @Description   : ��ȡʱ����
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime����ʼʱ�� 
���أ� ʱ�����  ��λ��ms
------------------------------------------------------------------------------*/
uint32_t OStimer_msTime_Distance(uint32_t _StartTime)
{ 	 
	return OStimer_usTime_Distance(_StartTime*1000)/1000;		 

}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_CRC16()
* @Description   : �ж϶�ʱ���Ƿ����
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
* @Description   : STM32�ڲ�ID��ȡ 				
* @Data          : 2017/11/2 
* @Explain       : ChipUniqueID :	���������ַ��3*4Byte��					
------------------------------------------------------------------------------*/ 
void Tools_ChipID_Get(void)
{ 	 
    //��ַ��С����,�ȷŵ��ֽڣ��ٷŸ��ֽڣ�С��ģʽ 
    //��ַ��С����,�ȷŸ��ֽڣ��ٷŵ��ֽڣ����ģʽ 
	Tools_ChipID[0] = *(__IO u32 *)(ADDR_CHIPID_0); //L	
	Tools_ChipID[1] = *(__IO u32 *)(ADDR_CHIPID_1); //  	
	Tools_ChipID[2] = *(__IO u32 *)(ADDR_CHIPID_2); //M 	
}	



/**---------------------------------------------------------------------------- 
* @FunctionName  : Tools_Rand()     			
* @Description   : ����һ����һ�޶��������			
* @Data          : 2017/11/2 
* @Explain       : range ȡֵ��Χ		
------------------------------------------------------------------------------*/ 
u32 Tools_Rand(u32 RangeMin,u32 RangeMax)
{
	u32 TempRand = 0;
	if(RangeMax <= RangeMin) return rand(); 
	
	TempRand = (rand()^Tools_ChipID[0]^Tools_ChipID[1]^Tools_ChipID[2])%(RangeMax - RangeMin) + RangeMin;
	
	return TempRand;
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
















