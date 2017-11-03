/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Manage.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __OS_MANAGE_H  
#define __OS_MANAGE_H   
								
/* 头文件包含 ----------------------------------------------------------------*/  

/* 全局宏定义 ----------------------------------------------------------------*/
typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  

/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct __AppMember
{  
	unsigned char *name;   
	unsigned char thread;//线程  
    unsigned long int  reload;//程序重载值   
	unsigned long int  loading;//运行槽   
	volatile unsigned char state;//运行状态   
	
	CreatFun *AppFun;  //程序的地址  
													
	struct __AppMember *next; 
	struct __AppMember *last; 
}Type_Addr; //环形队列成员 
	
	
/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  
signed char OSTask_Creat(CreatFun *_AppAddr,unsigned char *_Name,unsigned long int _T,unsigned char _state,unsigned char _thread);            
signed char OSTask_Remove(CreatFun *_AppAddr);            
unsigned int OSTask_Show(void);



#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



