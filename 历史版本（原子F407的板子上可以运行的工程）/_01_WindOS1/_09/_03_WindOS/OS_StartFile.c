/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : My_Library.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "My_Library.h" 
#include "OS_StartFile.h"


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 unsigned long int OS_RAM = 0; //RAM����
Type_Addr FreeHead = {0}; //������г������е�ͷ֡   
Type_Addr PrimaryHead = {0}; //�������������е�ͷ֡ 
Type_Addr SystemHead= {0}; //����ϵͳ�������е�ͷ֡ 
Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  
Type_Addr *SystemTemp = &SystemHead;  
Type_Addr *FreeRun = &FreeHead;
Type_Addr *PrimaryRun = &PrimaryHead;
Type_Addr *SystemRun = &SystemHead;

/* ȫ�ֺ�����д --------------------------------------------------------------*/



/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





