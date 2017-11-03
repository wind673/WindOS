#include "Drive_FFT.h"
 
struct compx {float real,imag;};                             		//����һ�������ṹ
struct compx s[FFT_N];    		//FFT������������S[0]��ʼ��ţ����ݴ�С�Լ�����
float SIN_TAB[FFT_N/4+1];   	//�������ұ�Ĵ�ſռ�



struct compx EE(struct compx a,struct compx b)      
{
 struct compx c;
 c.real=a.real*b.real-a.imag*b.imag;
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

                     
	
void FFT_Get_dat(void)//�õ�ԭʼ����
{

	u32 i; 
	for(i=0;i<FFT_N;i++)
	{                                  	
		s[i].real= ADC1_Buff[i]*3.3/4096.0f;		
	} 	
	
	
}



void create_sin_tab(float *sin_t)                     
{
  unsigned int i;
  for(i=0;i<=FFT_N/4;i++)
  sin_t[i]=sin(2*PI*i/FFT_N);
}



float sin_tab(float pi)
{
  int n;
  float a;
   n=(u16)(pi*FFT_N/2/PI);
   
  if(n>=0&&n<=FFT_N/4)
    a=SIN_TAB[n];
  else if(n>FFT_N/4&&n<FFT_N/2)
    {
     n-=FFT_N/4;
     a=SIN_TAB[FFT_N/4-n];
    }
  else if(n>=FFT_N/2&&n<3*FFT_N/4)
    {
     n-=FFT_N/2;
     a=-SIN_TAB[n];
   }
  else if(n>=3*FFT_N/4&&n<3*FFT_N)
    {
     n=FFT_N-n;
     a=-SIN_TAB[n];
   }
  
  return a;
}



float cos_tab(float pi)
{
   float a,pi2;
   pi2=pi+PI/2;
   if(pi2>2*PI)
     pi2-=2*PI;
   a=sin_tab(pi2);
   return a;
}


void FFT(struct compx *xin)
{
  int f,m,nv2,nm1,i,k,l,j=0;
  struct compx u,w,t;
   
   nv2=FFT_N/2;                  //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
   nm1=FFT_N-1;  
   for(i=0;i<nm1;i++)        
   {
    if(i<j)                    //���i<j,�����б�ַ
     {
      t=xin[j];           
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //��j����һ����λ��
    while(k<=j)               //���k<=j,��ʾj�����λΪ1   
     {           
      j=j-k;                 //�����λ���0
      k=k/2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
     }
   j=j+k;                   //��0��Ϊ1
  }

  {
   int le,lei,ip;                            //FFT����ˣ�ʹ�õ����������FFT����
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //����l��ֵ����������μ���
           ;
  for(m=1;m<=l;m++)                         // ���Ƶ��νἶ��
   {                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
    le=2<<(m-1);                            //le���ν���룬����m�����εĵ��ν����le��
    lei=le/2;                               //ͬһ���ν��вμ����������ľ���
    u.real=1.0;                             //uΪ���ν�����ϵ������ʼֵΪ1
    u.imag=0.0;
    //w.real=cos(PI/lei);                  //�����ò������sinֵ��cosֵ
    // w.imag=-sin(PI/lei);
    w.real=cos_tab(PI/lei);                //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
    w.imag=-sin_tab(PI/lei);
    for(j=0;j<=lei-1;j++)                  //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
     {
      for(i=j;i<=FFT_N-1;i=i+le)           //����ͬһ���ν����㣬������ϵ����ͬ���ν�
       {
        ip=i+lei;                          //i��ip�ֱ��ʾ�μӵ�������������ڵ�
        t=EE(xin[ip],u);                   //�������㣬�����ʽ
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
        
       }
      u=EE(u,w);                          //�ı�ϵ����������һ����������
     }
   }
  }
  
}
  

void FFT_Exchange(u16 *Buff)   
{  
  unsigned int i;  
  
  create_sin_tab(SIN_TAB);
  for(i=0;i<FFT_N;i++)                           //���ṹ�帳ֵ
  {
	  s[i].real=10+5*sin((6.28318*i-1)/FFT_N); //ʵ��Ϊ���Ҳ�FFT_N���������ֵΪ1
     if(i<8)
	  s[i].real=10+5*sin((50*3.14159*i)/FFT_N); //ʵ��Ϊ���Ҳ�FFT_N���������ֵΪ1
     else if(i<24)
	  s[i].real=0;
	 else 
      s[i].real=10;
	 s[i].imag=0;                                //�鲿Ϊ0
  }
	FFT_Get_dat();
	FFT(s);                                        //���п��ٸ���Ҷ�任
  
  for(i=0;i<FFT_N;i++)                           //��任������ģֵ�����븴����ʵ������
    Buff[i]=sqrt(s[i].real*s[i].real+s[i].imag*s[i].imag)/10;
	
 
}




















