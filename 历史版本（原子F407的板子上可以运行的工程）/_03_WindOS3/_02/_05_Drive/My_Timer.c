/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : My_Timer.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "My_Timer.h"
#include "My_Library.h" 
#include "OS_StartFile.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Config()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : ����ϵͳʱ��  1us��
------------------------------------------------------------------------------*/
void TIM2_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff;//��װ��ֵ 32λ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@
	
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM2_IRQn; //��ʱ�� x �ж�							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_1 ; //��ռ���ȼ� 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC
 	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ�� x												//@
/*---------------------------------------------------------------------------------------------*/
}   

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_Config()     
* @Description   : None 
* @Data          : 2016/3/18
* @Explain       : 1msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM3_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period =OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//����ʱ��9�����ж�							//@
	
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM3_IRQn; //��ʱ�� x �ж�				//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_PRIMARY ; //��ռ���ȼ� 7
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //��Ӧ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC		
 	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ�� x												//@
/*---------------------------------------------------------------------------------------------*/
}   
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Config()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : 10msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM4_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period =OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM4_IRQn; //��ʱ�� x �ж�							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_SYSTEM ; //��ռ���ȼ� 4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC
 	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@
/*---------------------------------------------------------------------------------------------*/
}

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





