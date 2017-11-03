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
Type_Addr FreeHead = {0}; //������г������е�ͷ֡   
Type_Addr PrimaryHead = {0}; //�������������е�ͷ֡ 
Type_Addr SystemHead= {0}; //����ϵͳ�������е�ͷ֡ 
Type_Addr *FreeTemp = &FreeHead;  
Type_Addr *PrimaryTemp = &PrimaryHead;  
Type_Addr *SystemTemp = &SystemHead;  



/* ȫ�ֺ�����д --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Creat()     
* @Description   : WinOS���񴴽� 
* @Data          : 2016/3/16
* @Explain       : ���� �� _AppAddr = �����ַ       _Name = �������� 
*				  		   _T = ��������    	_state = ����״̬  
*						   _thread = �߳�
*	
*				   ����ֵ ��-1 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
signed char OSTask_Creat(  CreatFun *_AppAddr \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					    )
						   
{  
	if( _thread   != THREAD_FREE \
		&&_thread != THREAD_PRIMARY \
	    &&_thread != THREAD_SYSTEM  \
	   )return -1;
		
	
	Type_Addr *_p = (Type_Addr*)malloc(sizeof(Type_Addr)); //�����ڴ� 		
	if(_p == NULL) return -2;
	
	if(_thread == THREAD_PRIMARY) //���߳�
	{
		PrimaryTemp ->next = _p;    
		_p ->last = PrimaryTemp; 			
		PrimaryTemp = _p; 		 
	}
	else if(_thread == THREAD_FREE)  //���У���̨���߳�
	{ 
		FreeTemp ->next = _p;    
		_p ->last = FreeTemp; 			
		FreeTemp = _p; 	 
	} 
	else if(_thread == THREAD_SYSTEM)   //ϵͳ�߳� 
	{
		SystemTemp ->next = _p;    
		_p ->last = SystemTemp; 			
		SystemTemp = _p; 		 
	}
	
	_p ->AppFun = _AppAddr;     
	_p ->next = NULL; //ѭ������   	
	_p ->name = _Name;  
	_p ->reload = _T;  //��������ֵ     
	_p ->loading = _p ->reload; //��װ���в�  
	_p ->state = _state;    //����״̬   
	
	  
	OS_RAM = (unsigned long int)_p; //��¼OSʹ�õ��ڴ�����    	 
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS����ɾ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    
*
*				   ����ֵ ��-1,-2,-3 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/	
signed char OSTask_Remove(CreatFun *_AppAddr)    
{   
	Type_Addr *pTemp = &FreeHead;  
	unsigned char thread_cnt = 0;   
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
		    OS_RAM = (unsigned long int)pTemp; //��¼OSʹ�õ��ڴ�����	 	
		    return 0;     	
	   }	
	   else if(pTemp ->next == NULL)		
	   {		
		     if(thread_cnt == 0) pTemp = &PrimaryHead; 
		     if(thread_cnt == 1) pTemp = &FreeHead; 
		     if(thread_cnt == 2) pTemp = &SystemHead; 
		     if(thread_cnt >= 3) return -1;   
			 thread_cnt++;  	
	   }			
	   		
	   if(pTemp ->next != NULL) pTemp = pTemp ->next;       	 
	    		 
		_cnt--; 			
	   if(_cnt == 0) return -2;  			
	}  			
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Show()     
* @Description   : WinOS������ʾ��������ģʽ�� 
* @Data          : 2016/3/16		
* @Explain       : ���� ��_AppAddr = �����ַ    	
*
*				   ����ֵ ��-1,-2 = ��������ʧ��				0 = �ɹ�
------------------------------------------------------------------------------*/
unsigned int OSTask_Show(void) 
{
	unsigned int Temp_color; 
	unsigned long int _RAM = 0;
	static long int _cnt = 0;
    int *_RAM_Test = (int*)malloc(sizeof(int)); 
	
	_cnt++; 
	Temp_color = TextColor_Set(RED); 
    Show_String(0,50+FONT_3*3,(u8*)"OSTask_Show",FONT_3);  
	TextColor_Set(GREEN);	
	LCD_ShowNum(150,60+FONT_3*3,_cnt,7,FONT_2); 
	
	
	/* RAM ��ʾ ------------------------------------*/
	TextColor_Set(YELLOW);
	Show_String(0,FONT_1,(u8*)"RAM:",FONT_1); 
	_RAM = 0x20000 - ((unsigned long int)&_RAM_Test - 0x20000000);
	LCD_ShowDecim(FONT_1*5,FONT_1,(double)_RAM/0x20000,2,5,FONT_1);  
	Show_String(FONT_1*8,FONT_1,(u8*)"%",FONT_1); 
	
	Show_String(0,FONT_1*2,(u8*)"RAM_Used:",FONT_1); 
	_RAM = (unsigned long int)&_RAM_Test - 0x20000000;
	LCD_ShowNum(FONT_1*5,FONT_1*2,_RAM,6,FONT_1); 
	
	Show_String(0,FONT_1*3,(u8*)"RAM_All:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*3,(unsigned long int)0x20000,6,FONT_1); 
	
	Show_String(0,FONT_1*4,(u8*)"RAM_Start:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*4,(unsigned long int)0x20000000,9,FONT_1); 
	
	Show_String(0,FONT_1*5,(u8*)"RAM_Now:",FONT_1);  
	LCD_ShowNum(FONT_1*5,FONT_1*5,(unsigned long int)&_RAM_Test,9,FONT_1); 
	
	Show_String(150,0,FreeTemp ->name,FONT_1);                    
	Show_String(150,FONT_1*1,PrimaryTemp ->name,FONT_1);   
	Show_String(150,FONT_1*2,SystemTemp ->name,FONT_1);
	TextColor_Set(Temp_color); 
	
	free(_RAM_Test);
	return 0;
}






/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





