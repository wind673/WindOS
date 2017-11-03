/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Desktop.c
* @Description : None
* @Date        : 2016/3/23
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/    

/* ͷ�ļ����� ----------------------------------------------------------------*/          
#include "OS_Desktop.h"  

/* ˽�к궨�� ----------------------------------------------------------------*/
/* ��ťλ�ú궨�� --------------------------------------*/
#define  X_X1  (OS_LCD_WHITH - FONT_3 - 5)
#define  X_Y1  (FONT_2)
#define  X_X2  (OS_LCD_WHITH - 5)
#define  X_Y2  (FONT_1+FONT_3) 

#define  T_X1  ( OS_LCD_WHITH - FONT_3*3)
#define  T_Y1  (FONT_2)
#define  T_X2  (OS_LCD_WHITH - FONT_3*2)
#define  T_Y2  (FONT_1+FONT_3) 
 

/* ˽�У���̬���������� -------------------------------------------------------*/ 
 
/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Ico  Ico_Head = {NULL}; 		
Type_Ico *Ico_Temp = &Ico_Head;		
Type_Ico *AppRunning = NULL;		
TypeTaskbar Taskbar = {BAR_UP,0,BAR_FREE,BAR_FIRST};
Type_Button *Button_X = NULL,*Button_T = NULL; 


/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------  
* @FunctionName  : Desktop()     
* @Description   : None 
* @Data          : 2016/3/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Desktop(void)  
{    
	OSTask_Creat(&OS_IcoShow);			
	OSTask_Creat(&OS_AppIn);			
	OSTask_Creat(&OS_AppOut); 	
	OSTask_Creat(&OS_Button_Show); 
	
	if(Button_X == NULL) //������ť
	{
		Button_X = OS_Button_Creat(X_X1,X_Y1,(u8*)"��",FONT_3,RED);
		Button_T = OS_Button_Creat(T_X1,T_Y1,(u8*)"��",FONT_3,RED);
	} 
	
// 	OS_IcoCreat(&App_Read_ScreenID,BLUE,GREEN);			
//	OS_IcoCreat(&App_LED,BLUE,GREEN); 		
//	OS_IcoCreat(&APP_TouchDraw,BLUE,GREEN);	 			
	Taskbar_Draw(FONT_1);	 	
	return 0;	
}
//����ע��� 
Type_AppList OS_Desktop = {Desktop,NULL,NULL,NULL, \
						OS_STATE_ONE_OFF,OS_THREAD_FREE, \
						(u8*)"OS_Desktop",200,200};			
															
						 
/**----------------------------------------------------------------------------  
* @FunctionName  : AppIn()     
* @Description   : ������� 
* @Data          : 2016/3/24
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int AppIn(void)  
{  
	 Type_Ico *temp = &Ico_Head;
	 signed int x1,x2,y1,y2,i; 
	 if(TouchPoint._state == TOUCH_STATE_OFF) return 1;
	 
	 while(temp ->next != NULL)
	 {
		  
		 temp = temp ->next;
		 if(TouchPoint._Y >= temp ->y1&&TouchPoint._Y <= temp ->y2  \
			&&TouchPoint._X >= temp ->x1&&TouchPoint._X <= temp ->x2 )     
		 {
				while(TouchPoint._state != TOUCH_STATE_OFF);//�ȴ�����̧��
				if(TouchPoint._LastY >= temp ->y1&&TouchPoint._LastY <= temp ->y2  \
				&&TouchPoint._LastX >= temp ->x1&&TouchPoint._LastX <= temp ->x2 )     
				{
					temp ->state = 1;  
					AppRunning = temp; 	//��¼�������еĳ���			
																
					OSTask_Alter(&OS_AppIn,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
					OSTask_Alter(&OS_IcoShow,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
																								
					OSTask_Alter(&OS_AppOut,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 	
					OSTask_Alter(temp->App,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE,OS_DEFAULT);  	
																						
					x1 = temp ->x1 + temp ->x2;								
					y1 = temp ->y1 + temp ->y2; 								
					x1/=2; y1/=2; 						
					x2 = x1; y2 =y1; 			
			  
					for(i = 0;i<OS_LCD_LENTH;i++) 	//�������Ķ���
					{
						if(x1 > 0) x1-=3;	
						if(y1 > 0) y1-=5;   	
						if(x2 < OS_LCD_WHITH) x2 +=3;   	
						if(y2 < OS_LCD_LENTH) y2 +=5;  	
						if(x1 < 0) x1 = 0;if(y1 < 0) y1 = 0;	
						if(x2 > OS_LCD_WHITH) x2 = OS_LCD_WHITH;	
						if(y2 > OS_LCD_LENTH) y2 = OS_LCD_LENTH;  	
						OS_Rect_Draw(x1,y1,x2,y2,1,BLACK);   	
						if(x1 == 0&&y1 == 0&&x2==OS_LCD_WHITH&&y2 == OS_LCD_LENTH) break;	
					}
					Taskbar_Draw(FONT_1);	//����
				}
		 }
		 else temp ->state = 0;  	
	}			
				
	 return 0;				
} 
//����ע��� 
Type_AppList OS_AppIn = {AppIn,NULL,NULL,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"OS_AppIn",50};		

/**----------------------------------------------------------------------------  
* @FunctionName  : AppOut()     
* @Description   : ������� 
* @Data          : 2016/3/24
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int AppOut(void)  
{   
	signed int x1,x2,y1,y2,i;
	
	/* �رճ���  -----------------------------*/
	x1 = OS_LCD_WHITH - FONT_3 - 5;
	y1 = FONT_2;
	x2 = OS_LCD_WHITH - 5;
	y2 = FONT_1+FONT_3;
	
	Button_X ->state = Button_Up; //���������� 																		
	if(TouchPoint._X > x1&&TouchPoint._X < x2&&TouchPoint._Y>y1&&TouchPoint._Y<y2) 
	{  
		Button_X ->state = Button_Down; //���������� 		
		while(TouchPoint._state != TOUCH_STATE_OFF); //�ȴ�����̧�� 		
		if(TouchPoint._LastX > x1&&TouchPoint._LastX < x2&&TouchPoint._LastY>y1&&TouchPoint._LastY<y2) 
		{	
			x1 = 0;x2 = OS_LCD_WHITH;  
			y1 = 0;y2 = OS_LCD_LENTH;    
			OS_Rect_Draw(0,0,OS_LCD_WHITH,OS_LCD_LENTH,1,BLACK);					
			for(i = 0;i<OS_LCD_LENTH;i++) 	//�˳�����Ķ���
			{ 	 
				x1 +=1;x2-=1;
				y1 +=1;y2-=1;  
				OS_Rect_Draw(x1,y1,x2,y2,0,WHITE);   	
				if(x1 >= OS_LCD_WHITH/2 && y1 >= OS_LCD_LENTH/2) break;	
			} 
			
			OSTask_Alter(AppRunning ->App,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE,OS_DEFAULT);   
			OSTask_Alter(&OS_AppOut,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
			OSTask_Alter(&OS_IcoShow,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 		
			OSTask_Alter(&OS_AppIn,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT);  
			Button_X ->state = Button_Close;
			Button_T ->state = Button_Close;
			Taskbar_Draw(FONT_1); //����  
			 
			return 1;
		}
	}
	
	/* ���𣨺�̨������  ---------------------*/
	x1 = OS_LCD_WHITH - FONT_3*3;
	y1 = FONT_2;
	x2 = OS_LCD_WHITH - FONT_3*2;
	y2 = FONT_1+FONT_3; 
	
	Button_T ->state = Button_Up; //����������
	if(TouchPoint._X > x1&&TouchPoint._X < x2&&TouchPoint._Y>y1&&TouchPoint._Y<y2) 
	{  
		Button_T ->state = Button_Down;
		while(TouchPoint._state != TOUCH_STATE_OFF);//�ȴ�����̧�� 
		if(TouchPoint._LastX > x1&&TouchPoint._LastX < x2&&TouchPoint._LastY>y1&&TouchPoint._LastY<y2) 		
		{
			x1 = 0;x2 = OS_LCD_WHITH;  
			y1 = 0;y2 = OS_LCD_LENTH;    
			OS_Rect_Draw(0,0,OS_LCD_WHITH,OS_LCD_LENTH,1,BLACK);					
			for(i = 0;i<OS_LCD_LENTH;i++) 	//�������Ķ���
			{ 	 
				x1 +=1;x2-=1;
				y1 +=1;y2-=1;  
				OS_Rect_Draw(x1,y1,x2,y2,0,WHITE);   	
				if(x1 >= OS_LCD_WHITH/2 && y1 >= OS_LCD_LENTH/2) break;	
			}  		 
													
			OSTask_Alter(AppRunning ->App,OS_DEFAULT,OS_DEFAULT,OS_STATE_SUSPEND,OS_DEFAULT);   
			OSTask_Alter(&OS_AppOut,OS_DEFAULT,OS_DEFAULT,OS_STATE_CLOSE_ON,OS_DEFAULT); 	
			OSTask_Alter(&OS_IcoShow,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 
			OSTask_Alter(&OS_AppIn,OS_DEFAULT,OS_DEFAULT,OS_STATE_ACTIVE_ON,OS_DEFAULT); 
			Button_X ->state = Button_Close;	
			Button_T ->state = Button_Close;	
			Taskbar_Draw(FONT_1); //���� 
			
			return 2;
		}
		
		
	}	
		
	return 0;	
}
//����ע���  
Type_AppList OS_AppOut = {AppOut,NULL,NULL,NULL, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"OS_AppOut",50};	

/**----------------------------------------------------------------------------
* @FunctionName  : OS_IcoCreat()     
* @Description   : ��ʾ����ͼ��
* @Data          : 2016/3/23
* @Explain        
* --------------------------------------------  
* NOx ���    str ���   
* TextColor ������ɫ    BackColor ����
------------------------------------------------------------------------------*/ 
unsigned char OS_IcoCreat(Type_AppList *_App,u16 _TextColor,u16 _BackColor)
{ 
	 u16 x1,y1,x2,y2;   
	 static u16 NOx = 0;//APP����
	
	 Type_Ico *p = (Type_Ico*)malloc(sizeof(Type_Ico));  		 
	 if(p == NULL) return 1;
	 
	 Ico_Temp -> next = p;
	 Ico_Temp = p;  
	 p ->next =NULL;
	 
	 u16 color = OS_Point_Read(x2+1,y2+1);
	 
	   
	 x1 = (NOx%3)*IOC_SIZE + IOC_SIZE/6*(NOx%3) + FONT_1; 
	 y1 = FONT_3+(NOx/3)*(IOC_SIZE+FONT_2*2); 
	 
	 x2 = x1 + IOC_SIZE;   	
	 y2 = y1 + IOC_SIZE;  	
	 p ->x1 = x1; p ->y1 = y1;	
	 p ->x2 = x2; p ->y2 = y2;	
	 p ->str = _App->name;
	 p ->backcolor = _BackColor;  		
	 p ->textcolor = _TextColor;		
	 p ->App = _App;	 
	 NOx ++;	
	 return 0;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_IcoShow()     
* @Description   : ��ʾ����ͼ��
* @Data          : 2016/3/23
* @Explain        
* --------------------------------------------  
* NOx ���    str ���   TextColor ������ɫ   
* BackColor ����
------------------------------------------------------------------------------*/ 
unsigned int IcoShow(void) 
{ 
	 Type_Ico *temp = &Ico_Head;																	
	 u16 TempColor;
	 static char flag = 1;  					
	 u16 i = 0;	 								
	  														
	 while(temp ->next != NULL) 					
	 {
		 temp = temp ->next;			
		 TempColor = temp ->backcolor;				
		 
		 if(temp ->state == 1)	
		 { 
			 if(flag%2) TempColor = ~TempColor; 	
			 flag ++; 
		 }		 
		  
		 
		 for(i = 1;i < IOC_SIZE/10;i++)	  														
		 OS_Rect_Draw(temp ->x1 + i,temp ->y1 + i,temp ->x2 - i,temp ->y2 - i,0,~(TempColor)); //�ⲿ  													
																														
		 OS_Rect_Draw(temp ->x1 + IOC_SIZE/10,temp ->y1 + IOC_SIZE/10,temp ->x2 - IOC_SIZE/10 ,temp ->y2 - IOC_SIZE/10,1,TempColor);  //�ڲ�   													
																	 
		 OS_Rect_Draw(temp ->x1,temp ->y1,temp ->x2,temp ->y2,0,BLACK);  //�߿� 												
		 
		 OS_TextColor_Set(temp ->textcolor);	 			
		 OS_BackColor_Set(OS_Point_Read(temp ->x1+FONT_2 - 1,temp ->y2+FONT_1/4+1));			 
		 OS_String_Show(temp ->x1+FONT_2,temp ->y2+FONT_1/4,temp ->str,FONT_2);				
		 
	 }
	 return 0;
}
//����ע��� 
Type_AppList OS_IcoShow = {IcoShow,NULL,NULL,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"OS_IcoShow",200};			
	
	 
/**----------------------------------------------------------------------------  
* @FunctionName  : Taskbar_Creat()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Taskbar_Creat(void)  
{  
	 
	 OS_TextColor_Set(WHITE);	
	 OS_BackColor_Set(BLACK);	
	 if(Taskbar.run_state == BAR_FIRST){ Taskbar_Draw(FONT_1); Taskbar.run_state = BAR_CLOSE;} 
	 if(TouchPoint._state != 0)  //�ж��Ƿ�����Ļ		
	 {
		if(Taskbar.activate_point == BAR_UP) //�жϼ����λ��			
		if(TouchPoint._Y < FONT_1) Taskbar.activate_state = BAR_ACTIVATE;		
		
		if(Taskbar.activate_point == BAR_DOWN) 				
		{			
			if(TouchPoint._Y > OS_LCD_LENTH - FONT_3*3) Taskbar.activate_state = BAR_ACTIVATE;
			
		}				
	 } 			
	 else{ Taskbar.activate_state = BAR_CLOSE;}		 			
	  
	 if(Taskbar.activate_state == BAR_ACTIVATE) //�ж��û��Ƿ��¼���� 	
	 {
		OSRunning_Break();
		Taskbar.dynamic_Y = Taskbar_Draw(TouchPoint._Y);   
		OS_String_Show(OS_LCD_WHITH/2-FONT_1*2,TouchPoint._Y,(u8*)"�����",FONT_1);	
		Taskbar.run_state = BAR_RUNNING;	
	 }	           
	 else  
	 {
		 
		if(Taskbar.run_state == BAR_RUNNING)  		
		{
			if(Taskbar.dynamic_Y > OS_LCD_LENTH/3)			
			{			
				Taskbar.activate_point = BAR_DOWN; 			
				Taskbar_Draw(OS_LCD_LENTH); 	 
								
			}
			else 						
			{
				Taskbar.activate_point = BAR_UP;     
				Taskbar_Draw(FONT_1);
				OSRunning_Continue();			
			}
			Taskbar.run_state = BAR_CLOSE; //���ֺ� �����жϣ�������Ӧ�Ĵ���		
		   					
		}
		
	 }			
	 	
	 return 0;				
}
//����ע��� 
Type_AppList App_Taskbar = {Taskbar_Creat,NULL,NULL,NULL, \
					   	   OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						   (u8*)"Taskbar",10};  		
		
		
		
/**----------------------------------------------------------------------------  
* @FunctionName  : TaskbarY()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain       : None
------------------------------------------------------------------------------*/
u16 Taskbar_Draw(u16 Bar_Y)  
{
	LCD_Fill(0,0,OS_LCD_WHITH,Bar_Y+1,BLACK); 
	LCD_Fill(0,Bar_Y+1,OS_LCD_WHITH,OS_LCD_LENTH,WHITE); 
				
	return Bar_Y;		
}
	

 
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





