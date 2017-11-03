/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Hal.c
* @Description : ϵͳ�����
* @Date        : 2017/11/03
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : ��ֲϵͳǰ��������������ݡ�
------------------------------------------------------------------------------- 
�޶���¼��	
 @Date		@Version			@Revise					@Author
2017/10/16 	V1.1.1				��һ�θ���				Wind��л���죩

����޶���
��һ�θ���
*=============================================================================*/     

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Hal.h"
#include "OS_StartFile.h"
#include "OS_Manage.h"
#include "OS_Tools.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/
										
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : ����ʱ�� 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM2_Init(void)
{ 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = 0xffff - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx	
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : �������߳�
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM4_Init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_PRIOITY_PRIMARY;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx	
}	


/**----------------------------------------------------------------------------
* @FunctionName  : TIM6_Init()
* @Description   : ��ʱ����ʼ��
* @Data          : 2017/10/13
* @Explain       : ����ϵͳ�߳� 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM6��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = (u32)(Bsp_Clocks.PCLK1_Frequency /1000000) - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_PRIOITY_SYSTEM;  //��ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx	 
} 



/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : ����ʱ��
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM2_IRQHandler(void)
{ 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���TIMx�����жϱ�־
    OS_TimeOver_Cnt ++; 
}



/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM4_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //���TIMx�����жϱ�־
    OSThread_Handle(OS_THREAD_PRIMARY);
	
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_IRQHandler()
* @Description   : ��ʱ��������
* @Data          : 2016/8/8
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM6_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //���TIMx�����жϱ�־
    OSThread_Handle(OS_THREAD_SYSTEM);
	
}



//main Demo
/* 
int main()					
{		  
	// WindOS��ʼ�� -------------------------------
	OS_Init();      
	Bsp_Init();		
	
	// ����ע�� ----------------------------------- 		
	//OSTask_Creat(&App_Test);   	 	
	OSTask_Creat(&App_LED);   		//LED����	
	OSTask_Creat(&App_Key); 		//����		 
	
	// WindOS���г��� -----------------------------
	while(1) OSThread_Handle(OS_THREAD_FREE); 		
	
}	

*/




/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





