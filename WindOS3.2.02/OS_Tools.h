/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Tools.h
* @Description : ��ϵͳ�Դ���С����
* @Date        : 2017/9/21
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/            
#ifndef __OS_TOOLS_H
#define __OS_TOOLS_H

/* ͷ�ļ����� ----------------------------------------------------------------*/ 		 
#include "OS_StartFile.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define 	OS_TIMER_CNT_MAX			(0xffff)
#define 	OS_Clock_us					(TIM_GetCounter(TIM2))

/* �ṹ������ ---------------------------------------------------------------*/  

/* ȫ�ֱ������� --------------------------------------------------------------*/  

/* ȫ�ֺ������� --------------------------------------------------------------*/   
void OSdelay_us(uint32_t _us);			
void OSdelay_ms(uint32_t _ms);   		
void OSdelay_s(uint32_t _s);	 

uint32_t OStimer_us_Get(void);
uint8_t OStimer_usTimeOver_Is(uint32_t _StartTime,uint32_t _Time);    

uint32_t OStimer_ms_Get(void);
uint8_t OStimer_msTimeOver_Is(uint32_t _StartTime, uint32_t _Time);









void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(uint32_t addr);	//���ö�ջ��ַ 

#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





