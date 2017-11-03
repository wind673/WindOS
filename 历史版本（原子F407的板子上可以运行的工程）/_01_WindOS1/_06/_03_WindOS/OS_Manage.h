/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __OS_MANAGE_H  
#define __OS_MANAGE_H   
								
/* ͷ�ļ����� ----------------------------------------------------------------*/  

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
typedef unsigned int(CreatFun)(void); //App ������������� unsigned int XXX(void)  

/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct __AppMember
{  
	unsigned char *name;   
	unsigned char thread;//�߳�  
    unsigned long int  reload;//��������ֵ   
	unsigned long int  loading;//���в�   
	volatile unsigned char state;//����״̬   
	
	CreatFun *AppFun;  //����ĵ�ַ  
													
	struct __AppMember *next; 
	struct __AppMember *last; 
}Type_Addr; //���ζ��г�Ա 
	
	
/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
signed char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T,unsigned char _state,unsigned char _thread);            
signed char OSTask_Remove(CreatFun *_AppAddr);            
unsigned int OSTask_Show(void);



#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



