/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Manage.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Manage.h"
#include "OS_StartFile.h" 

 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/
unsigned long int OS_RAM = 0; //RAM����
Type_Addr AppHead = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //����������е�ͷ֡
Type_Addr *pTemp = &AppHead;  
	
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Init()     
* @Description   : WinOS��ʼ�� 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Init(void)
{		
	 
	/* WindOS��ʼ�� ------------------------------------*/  
	
	/* Ӳ����ʼ�� --------------------------------------*/
	Drive_Init(); 
	
}			

 
	
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Creat()     
* @Description   : WinOS���񴴽� 
* @Data          : 2016/3/16
* @Explain       : ���� �� _AppAddr = �����ַ       _Name = �������� 
*				  		   _period = ��������    	_state = ����״̬  
*						   _thread = �߳�
*				   ����ֵ ��-1 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
signed char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _period,unsigned char _state,unsigned char _thread)
{  
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //�����ڴ� 		
	if(_p == NULL) return -1;
	
	pTemp ->next = _p;    
	_p ->last = pTemp; 			
	pTemp = _p; 		
	_p ->AppFun = _AppAddr;     
	_p ->next = AppHead.next; //ѭ������
	_p ->name = _Name; 
	_p ->reload = _period;  //��������ֵ
	_p ->loading = _p ->reload; //����װ������ֵ
	_p ->state = _state;    //����״̬
	
	OS_RAM += sizeof(Type_Addr); //��¼OSʹ�õ��ڴ�����	 
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS����ɾ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    		
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
signed char OSTask_Remove(CreatFun *_AppAddr) 
{  
	Type_Addr *pTemp = &AppHead;
	unsigned int _cnt = TASK_MAX;
	
	while(1)
	{ 
	   if(pTemp ->AppFun == _AppAddr) 
	   {
		    (pTemp ->last) ->next = pTemp ->next;
		    (pTemp ->next) ->last = pTemp ->last;
		    pTemp ->AppFun = NULL;   
		    free(pTemp); 
		    pTemp =NULL;  
		    OS_RAM -= sizeof(Type_Addr); //��¼OSʹ�õ��ڴ�����	 
		    return 0;     
	   }
	   else if(pTemp ->next == NULL)
	   {
			 return -1;   
	   }
	   else
	   {
			pTemp = pTemp ->next;        
	   }
	   
		_cnt--; 
	   if(_cnt == 0) return -2;  
	} 
	 			
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Show()     
* @Description   : WinOS������ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    		
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned int OSTask_Show(void) 
{
	TextColor_Set(YELLOW);
	LCD_ShowNum(120,0,OS_RAM,10,FONT_1); 	
	Show_String(120,FONT_1*1,pTemp ->name,FONT_1); 
	LCD_ShowNum(120,FONT_1*2,pTemp ->loading,10,FONT_1); 		
	
	return 0;
}






/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





