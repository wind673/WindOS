//******************************************(c)WindRises*Start File******************************************//

//ʱ�Ӽ���Ƶ�����ļ�
#include "my_sys.h" 
#include "delay.h"
#include "My_Library.h"
#include "usart.h" 

 


void RCC_Configuration(void)
{ 
	RCC_Div(336,8,2,7);//336M��2��168MϵͳƵ��//Ĭ��HCLK ����Ƶ;APB1 4��Ƶ;APB2 2��Ƶ.
	RCC_HCLKConfig(RCC_HCLK_Div1);//AHBʱ�ӣ�HCLK��. Ϊ�˻�ýϸߵ�Ƶ�ʣ����Ƕ� SYSCLK 1��Ƶ���õ�HCLK
	RCC_PCLK2Config(RCC_HCLK_Div2);//����APB2����Ƶ  ����ADC  
	RCC_PCLK1Config(RCC_HCLK_Div1);//����APB1 ����Ƶ������һ��Ƶ���ᵼ��SPI�޷�����ʹ�ã�������EXTI_Line3 
	
}




void RCC_Div(u16 a_pll_N,u16 a_pll_M,u16 a_pll_P,u16 a_pll_Q)
{
	 
    /*����ǰ������RCC����Ϊ��ʼֵ*/
     RCC_DeInit();
 
     /*����ѡ�� �ⲿ����HSE����Ϊ ʱ��Դ��������ȴ��ⲿ����*/
     RCC_HSEConfig(RCC_HSE_ON);
     /*�ȴ��ⲿ��������ȶ�״̬*/
     while( RCC_WaitForHSEStartUp() != SUCCESS ); 
     RCC_PLLConfig(RCC_PLLSource_HSE, a_pll_M, a_pll_N, a_pll_P, a_pll_Q);
     RCC_PLLCmd(ENABLE); 
     RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
}


 
void delay_s(u16 t)
{
	t*=10;
	while(t--)
	delay_ms(100);  
		 
}










//// 
////���� RCC_PLLConfig();����
////�亯��ԭ��Ϊ��
////void RCC_PLLConfig(uint32_t  RCC_PLLSource,
////                   uint32_t  PLLM,
////                   uint32_t  PLLN,
////                   uint32_t  PLLP,
////                   uint32_t  PLLQ)��
//// 
////�Ի�ĵط��϶����ں��� 4������ PLLM / PLLN / PLLP / PLLQ.
//// 
////�ڿ⺯��Դ�ļ� system_stm32f4xx.c �п����ҵ��� 4��������˵�����뿴��ͼע�Ͳ���:
//// 
////��������Ǵ� �⺯��Դ�ļ� stm32f4xx_rcc.c ���ҵ��ġ�������������ֱ��ȥ���⺯����ע�ͷǳ���ϸ��
//// 
/////**
////  * @brief  Configures the main PLL clock source, multiplication and division factors.
////   @���   ������PLLʱ��Դ���Լ���Ƶ����          (PLL��ֹһ��,����һ������Ϊ��Ƶ�����ṩ������ʱ��)
////  * @note   This function must be used only when the main PLL is disabled.
////  * @ע��   �������ֻ������PLLʧ��ʱ����ʹ��
////  * @param  RCC_PLLSource: specifies the PLL entry clock source.
////   @����    RCC_PLLSource:ѡ��PLLʱ��Դ
////  *          This parameter can be one of the following values:
////�����������������ֵ��
////  *            @arg RCC_PLLSource_HSI: HSI oscillator clock selected as PLL clock entry
//// ѡ��HSI��ΪPLLʱ��Դ
////  *            @arg RCC_PLLSource_HSE: HSE oscillator clock selected as PLL clock entry
////ѡ��HSE��ΪPLLʱ��Դ
////  * @note   This clock source (RCC_PLLSource) is common for the main PLL and PLLI2S. 
////  *  
////  * @param  PLLM: specifies the division factor for PLL VCO input clock
////   @����    PLLM������ PLL VCO ����ʱ�ӵ� �������ӣ�division factor��
////  *          This parameter must be a number between 0 and 63.
////������� ��Χ�� 0 ~ 63
////  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
////  *         frequency ranges from 1 to 2 MHz. It is recommended to select a frequency
////  *         of 2 MHz to limit PLL jitter.
////  * @ע��         ����Ҫ��ȷѡ�� PLLM��ֵ�� ʹ�� VCO����Ƶ�� ���� 1~2MHz.
////����ѡ�� 2MHz ������PLL�𵴣�jitter����
////  * @param  PLLN: specifies the multiplication factor for PLL VCO output clock
////  *          This parameter must be a number between 192 and 432.
////   @����   PLLN     ѡ�� PLL VCO���ʱ�ӵ� �˷����ӣ�multiplication factor ��
////            ���������ֵ ���� 192 ~432
////  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
////  *         output frequency is between 192 and 432 MHz.
////  * @ע��  ��ѧҪ��ȷѡPLLN�Ĵ�С���Ա�֤VCO���ʱ�ӽ��� 192 ~432MHz 
////  * @param  PLLP: specifies the division factor for main system clock (SYSCLK)
////  *          This parameter must be a number in the range {2, 4, 6, or 8}.
////@����  PLLP ѡ�� ϵͳʱ��SYSCLK �ĳ������ӣ�division factor �������
////            ֵ������2,4,6,8
////  * @note   You have to set the PLLP parameter correctly to not exceed 168 MHz on
////  *         the System clock frequency.
////  * @ע��  ����Ҫ��ȷ����PLLP��ȷ��ϵͳʱ��SYSCLK������168MHz
////  * @param  PLLQ: specifies the division factor for OTG FS, SDIO and RNG clocks
////  *          This parameter must be a number between 4 and 15.
////@����  PLLQ ѡ��� OTG FS(USB), SDIO(SD����д), RNG���������������
////        ʱ�ӵĳ������ӣ���ֵ����4~15
////  * @note   If the USB OTG FS is used in your application, you have to set the
////  *         PLLQ parameter correctly to have 48 MHz clock for the USB. However,
////  *         the SDIO and RNG need a frequency lower than or equal to 48 MHz to work
////  *         correctly.
////  * @ע��  �������ĳ������õ� USB OTG FS,����Ҫ��ȷ����PLLQ��ȷ��USB��
////                 48MHz��ʱ�ӡ����Ƕ���SDIO��RNG��Ҫһ��С�ڻ����48MHz��ʱ��  
////  * @retval None

////	
	
	

	
	
	








//******************************************(c)WindRises*End File******************************************//

