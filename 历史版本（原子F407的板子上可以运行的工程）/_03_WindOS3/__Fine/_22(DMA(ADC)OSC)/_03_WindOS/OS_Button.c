/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Button.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None 
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Button.h" 			  

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Button Button_Head = {NULL};


/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Creat()     
* @Description   : ������ť		
* @Data          : 2016/5/5
* @Explain        
-------------------------------------------------------------------------------  
x,y  ����   str ���   Color ��ť��ɫ    
Fontsize �����С      
------------------------------------------------------------------------------*/ 
Type_Button *OS_Button_Creat(u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color)    
{ 	 
	 Type_Button *pStruct;
	 Type_Button *Temp = &Button_Head; 	
	
 	 pStruct = (Type_Button*)malloc(sizeof(Type_Button));
	 if(pStruct == NULL) {OS_Error |= OS_ERROR_MALLOC;  return NULL;} //���ݴ��󾯸���Ϣ��ϵͳ
	 
	 while(Temp ->next != NULL)	//�ҵ����һ����ַ
	 {
	 	Temp = Temp ->next; 
	 } 
	 pStruct ->x1 = x; 				
	 pStruct ->y1 = y;			
	 pStruct ->x2 = x + strlen((const char*)str)*Fontsize/2;					
	 pStruct ->y2 = y + Fontsize;												
	 pStruct ->str = str;		
	 pStruct ->color = Color;		
     pStruct ->fontsize = Fontsize;	
	 pStruct ->state = BUTTON_UP;
	 Temp ->next = pStruct;		 	
	 pStruct ->next = NULL;		
	 
	return pStruct;	
}						
		
			
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Remove()     
* @Description   : ɾ����ť		
* @Data          : 2016/5/5
* @Explain       ��None
------------------------------------------------------------------------------*/ 
u8 OS_Button_Remove(Type_Button *pStruct)    
{ 	 
	Type_Button *Temp = &Button_Head;	 
	while(Temp ->next != NULL)	
	{
		Temp = Temp ->next;
		if(Temp ->next == pStruct) break; //�ҵ� pStruct ��һ����ť�ĵ�ַ
	} 
	Temp ->next = pStruct ->next;  
	free(pStruct); 
	pStruct = NULL;	
	
	return 0;	
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Show()     
* @Description   : ��ť��ʾ
* @Data          : 2016/4/19
* @Explain   
-------------------------------------------------------------------------------
view :��ʾ��ť��״̬
------------------------------------------------------------------------------*/ 
void OS_Button_Show(Type_Button *ButtonStruct,u8 state)    
{ 	    												
	u16 ColorTemp = ButtonStruct ->color;	  
	u16 pTextColor,pBackColor;  	
	if(ButtonStruct ->state == BUTTON_CLOSE) return;
		
	if(state == BUTTON_DOWN)  
		ColorTemp = (u16)~ColorTemp;  //��ť������	 
	if(state == BUTTON_DISABLED)   ColorTemp = GRAY; //��ť������	 
		
	if(OS_Point_Read(ButtonStruct ->x1+1,ButtonStruct ->y1+1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x1+1,ButtonStruct ->y2-1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x2-1,ButtonStruct ->y1+1) == ColorTemp)
	if(OS_Point_Read(ButtonStruct ->x2-1,ButtonStruct ->y2-1) == ColorTemp)	
	{
		return; //��Ļ�仯�Ÿ���			 
	}
	
	
	OS_Rect_Draw(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->x2-1,ButtonStruct ->y2-1,1,ColorTemp);   //��ť�ڲ�   
	
	//��ť��Ӱ   	 
	OS_Lines_Draw(ButtonStruct ->x1,ButtonStruct ->y2,ButtonStruct ->x2,ButtonStruct ->y2, \
	~OS_Point_Read(ButtonStruct ->x2+2,ButtonStruct ->y2+2)); 	
				 
	OS_Lines_Draw(ButtonStruct ->x2,ButtonStruct ->y1,ButtonStruct ->x2,ButtonStruct ->y2, \
	~OS_Point_Read(ButtonStruct ->x2+2,ButtonStruct ->y2+2)); 		
											
	pTextColor = OS_TextColor_Set(~ColorTemp);		 			
	pBackColor = OS_BackColor_Set(ColorTemp);								  
	OS_String_Show(ButtonStruct ->x1,ButtonStruct ->y1,ButtonStruct ->str,ButtonStruct ->fontsize,1);		
	OS_TextColor_Set(pTextColor);	
	OS_BackColor_Set(pBackColor);	
	 
}



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Alter()     
* @Description   : ��ť�޸�
* @Data          : 2016/4/21
* @Explain    
-------------------------------------------------------------------------------
ButtonStruct ��ť�ĵ�ַ  state ��ť����״
------------------------------------------------------------------------------*/ 
void OS_Button_Alter(Type_Button *ButtonStruct,u8 state,u16 x,u16 y,u8 *str ,u16 Fontsize,u16 Color)   
{ 	    	
	 if(ButtonStruct == NULL) return;	
	
	 if(x != OS_DEFAULT) 
	 {
		 ButtonStruct ->x1 = x; 	
		 ButtonStruct ->x2 = x + strlen((const char*)str)*Fontsize/2;
	 }	
	 
	 if(y != OS_DEFAULT)  
	 {
		 ButtonStruct ->y1 = y;		 
		 ButtonStruct ->y2 = y + Fontsize;		
	 }
	 
	 if(str != OS_DEFAULT) 		ButtonStruct ->str = str;	 
	 if(Color != OS_DEFAULT)	ButtonStruct ->color = Color;		
     if(Fontsize != OS_DEFAULT)	ButtonStruct ->fontsize = Fontsize;	 
	 if(state != OS_DEFAULT)  	ButtonStruct ->state = state;
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Button_Alter()     
* @Description   : ��ť��ʷ״̬���
* @Data          : 2016/4/22
* @Explain    
-------------------------------------------------------------------------------
ButtonStruct ��ť�ĵ�ַ 
------------------------------------------------------------------------------*/ 
void OS_Button_LastClear(Type_Button *ButtonStruct)
{ 
	ButtonStruct ->LastState = BUTTON_DEFAULT;  
}

/**----------------------------------------------------------------------------
* @FunctionName  : Button_Scan()     
* @Description   : ��ťɨ��	
* @Data          : 2016/4/19
* @Explain        
-------------------------------------------------------------------------------  
x,y  ����   str ���   Color ��ť��ɫ    
Fontsize �����С      state ״̬:0δ����  1����         
------------------------------------------------------------------------------*/ 
unsigned int Button_Scan(void)    
{ 	   
	Type_Button *ButtonStruct = &Button_Head;	
 
	while(1)
	{ 
		if(ButtonStruct ->next != NULL) ButtonStruct = ButtonStruct ->next;
		else break; 
		
		if(ButtonStruct ->state == BUTTON_CLOSE) continue;
		 
		if(TouchPoint._X > ButtonStruct->x1&&TouchPoint._X < ButtonStruct->x2 \
			&&TouchPoint._Y> ButtonStruct->y1&&TouchPoint._Y < ButtonStruct->y2)  
		{	
			ButtonStruct ->state = BUTTON_DOWN; 	 
			ButtonStruct ->value ++; 	
		}	 
		else			
		{		   
			if(ButtonStruct ->state == BUTTON_DOWN) ButtonStruct ->LastState = BUTTON_DOWNED;
			
			ButtonStruct ->value = 0;
			ButtonStruct ->state = BUTTON_DEFAULT;  
		}
		 
	}
	return 0;	
}					
			
Type_AppList OS_Button_Scan = {Button_Scan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"Button_Scan",TOUCH_SCAN_SPEED};			
				
						
/**----------------------------------------------------------------------------
* @FunctionName  : Button_State()     
* @Description   : ��ť״̬	
* @Data          : 2016/5/4
* @Explain       ��mode :  0(�ɳ���)        1��ֻ��Ӧһ�Σ�
------------------------------------------------------------------------------*/ 
u8 OS_Button_State(Type_Button *ButtonStruct,u8 mode)    
{ 	    
	u8 state = BUTTON_INVALID;	
	if(mode == 0)
	{
		if( TouchPoint._X > ButtonStruct->x1 \
			&&TouchPoint._X < ButtonStruct->x2 \
			&&TouchPoint._Y>ButtonStruct->y1 \
			&&TouchPoint._Y<ButtonStruct->y2 ) 
			state = BUTTON_VALID;
		else 
			state = BUTTON_INVALID;	
		
	}
	else if(mode == 1)
	if(ButtonStruct ->LastState == BUTTON_DOWNED) 
	{	
		if( TouchPoint._LastX > ButtonStruct->x1 \
			&&TouchPoint._LastX < ButtonStruct->x2 \
			&&TouchPoint._LastY>ButtonStruct->y1 \
			&&TouchPoint._LastY<ButtonStruct->y2 ) 
			state = BUTTON_VALID;
		else  
			state = BUTTON_INVALID;
	} 
	return state;
}

 		

		
	
		
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
		
		
		
	
	
	

