#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "pwm.h"
#include "algorithms.h"

#include "key.h"
//Ϊ�˶�ȡ�ļ�
#include "stdio.h"    
#include <stdlib.h>
#include <string.h>



//��������ͷ�ļ�
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define N 3
#define epsilon  0.005
#define M 2


///*const  char* hz;
//char buff[100] = {0};

//	unsigned char qh, wh;
//	unsigned long offset;
//	FILE* HZK;

//	���ֿ��ļ�hzk16*/
//	if ((HZK = fopen("hzk16", "rb")) == NULL )
//	{
//		printf("Can't open haz16 �ֿ��ļ�\n");
//		//exit(0);
//	}
//	HZK = fopen("hzk16", "rb");
//	/*����=����(���ֽ�)-160??λ��=����(���ֽ�)-160*/
//	qh = *(hz)-160;	  //��1��ʼ���
//	wh = *(hz + 1) - 160; //��1��ʼ���
//	offset = (94 * (qh - 1) + (wh - 1)) * 32; //ÿ������32�ֽڣ�16*16=512λ��512/8=32 
//	fseek(HZK, offset, SEEK_SET);	/*���ļ�ָ���ƶ���ƫ������λ��*/
//	fread(buff, 32, 1, HZK);	/*��ƫ������λ�ö�ȡ32���ֽ�*/
//	fclose(HZK);   */





//ALIENTEK ̽����STM32F407������ ʵ��18
//ADCģ��ת��ʵ��-�⺯���汾  
//����֧�֣�www.openedv.com
//�Ա����̣�
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

 //��ad��ȡ�ĵ�ѹ������Ӧ��Һ��߶��ź�
float  adc_voltage2height(float voltage)
{
	return voltage;
}

/*һ�׹��Ի��� + �ӳٻ���  ����ʵ��  */
float  inertia_delay_element(float giveValue , float T , float time)  // ��������ֵ��ʱ�䳣��T , �ӳ�ʱ��time
{
	
	  float result;
	static  float ResultValueBack = 0;
	delay_ms(10);


	result = (T*ResultValueBack + giveValue)/(1+T);  //c(t)=(r(t)+Tc(t-1))/(T+1);

	ResultValueBack = result;

	return result;
	
}

/*���׹��Ի��� + �ӳٻ���  ����ʵ��  */
float  second_element(float giveValue , float T1 ,float T2, float k )  // ��������ֵ��ʱ�䳣��T
{
	
	static  float result;
	static	float ResultValueBack = 0;
	static	float lastVal = 0;
	
	float tem = 0;
	float tem2 = 0;
	
	 tem  =  T1 * T2 * 0.5;
	 tem2 = T1 + T2 + 1;
	
	delay_ms(10);
	
	result = (k * giveValue + tem * lastVal + tem2 * ResultValueBack  )  / ( tem + tem2);

	ResultValueBack = result;
	lastVal = ResultValueBack;
	
	return result;
	
}



//*************************************************************************************
float get_control_height(float reference_height , float last_height , float T)  
	
{
	float control_height = 0;
	control_height = reference_height * (T + 1 ) * 1  -    last_height * T * 0;
	return control_height;
	 
}



	float refer_point[300] = {0}; //�ο��켣
    float curData[300] =  {0};   //�����ϵĵ�
	float pValue[300]  =  {0};
	float  iValue[300] =  {0};
	float  dValue[300] =  {0};

//********************��������ʵ��*****************************************	
	
	/*
	����A������b����˽������Ab��
*/
void matrixTimesVec11(double A[M][N], double B[N][M], double AB[M][M])
{
	
	
	int i = 0, j = 0 , m = 0 , n = 0;
//	printf("%lf , %lf , %lf , %lf ,%lf ,%lf\r\n" ,A[1][0] ,A[1][1],A[1][2] ,B[0][0] , B[1][0] , B[2][0]);		

  for(  m = 0; m < M; m++)
 {
	for(n = 0; n < M ; n++)
	 {
		 for (i = 0 , j = 0 ; i < N , j < N; i++ , j++)
			{
				
				AB[m][n] += A[m][i]  * B[j][n];
				
			}
		 
		 
	 }
	
 }
//	printf("%lf , %lf , %lf , %lf ,%lf ,%lf\r\n" ,A[1][0] ,A[1][1],A[1][2] ,B[0][0] , B[1][0] , B[2][0]);		
	
	
}


void matrixTimesVec(double A[2][1], double B[1][2], double AB[M][M])
{
	
	
	int i = 0, j = 0 , m = 0 , n = 0;
//	printf("%lf , %lf , %lf , %lf ,%lf ,%lf\r\n" ,A[1][0] ,A[1][1],A[1][2] ,B[0][0] , B[1][0] , B[2][0]);		

  for(  m = 0; m < M; m++)
 {
	for(n = 0; n < M ; n++)
	 {
		 for (i = 0 , j = 0 ; i < 1 , j < 1; i++ , j++)
			{
				
				AB[m][n] += A[m][i]  * B[j][n];
				
			}
		 
		 
	 }
	
 }
//	printf("%lf , %lf , %lf , %lf ,%lf ,%lf\r\n" ,A[1][0] ,A[1][1],A[1][2] ,B[0][0] , B[1][0] , B[2][0]);		
	
	
}

void matrixTimesVec3(double A[2][2], double B[2][1], double AB[2][1])
{
	
	
	int i = 0, j = 0 , m = 0 , n = 0;	

  for(  m = 0; m < 2; m++)
 {
		 for (i = 0 , j = 0 ; i < 2 , j < 2; i++ , j++)
			{	       
				AB[m][0] += A[m][i]  * B[j][0];	
//				printf("%lf , %lf\r\n" ,  A[m][i] , B[j][0]);
			}
		 
		
	 
	
 }
//	printf("%lf , %lf , %lf , %lf ,%lf ,%lf\r\n" ,A[1][0] ,A[1][1],A[1][2] ,B[0][0] , B[1][0] , B[2][0]);		
	
	
}











void vecPlus(double A[2][2], double B[2][2], double AB[M][M] )
{
	int i = 0 , j = 0; 
	for (i = 0; i < 2; i++)
	{
		for(j = 0; j < 2; j++)
		{
			AB[i][j]  =  A[i][j] + B[i][j];
		}
	}
}

//������ת�þ���
void    transpose ( double A[2][2], double B[2][2])
{
	int i = 0 , j = 0; 
	for (i = 0; i < 2; i++)
	{
		for(j = 0; j < 2; j++)
		{
			if(i == j )
			{
				B[i][j] = A[i][j];

			}
			else
			{
				B[i][j] = A[j][i];
			
			}
		}
		
	}


}

//����֪����������
void   inverseMatrix (  double A[2][2], double B[2][2])
{
	//��������������ʽ
	double res = 0;
	res = ((A[0][0]) * (A[1][1])) - ((A[0][1]) * (A[1][0]));
	
	//������������ Ҳ���Ǵ�������ʽ
	B[0][0] = A[1][1];
	B[1][1] = A[0][0];
	B[0][1] = A[1][0] * (-1);
	B[1][0] = A[0][1] * (-1);
	
//��� ������յ������
	B[0][0] = A[1][1] / res ;
	B[1][1] = A[0][0] / res;
	B[0][1] = A[1][0] / res* (-1);
	B[1][0] = A[0][1] / res* (-1);



}



	
//��ӡ����
void  printMatrix(double A[][2] , int k , int z)      // �������������������  
{
	int i = 0 , j = 0;
	for( i = 0; i < k ; i++)
	{
		for(j  = 0; j < z; j++)
		{
//			printf("A[%d][%d] = %lf\r\n" , i , j , A[i][j]);
		
		}
	
	
	}
}

//��ӡ����2
void  printMatrix2(double A[][1] , int k )      // �������������������  
{
	int i = 0 , j = 0;
	for( i = 0; i < k ; i++)
	{
//		printf("A[%d][%d] = %lf\r\n" , i , j , A[i][0]);
	}
}
	
	

int main1(void)
{ 
	
	
	float  curHeight = 0;      // ��ǰҺλ�߶�
    float  tarHeight = 100;     //  Ŀ��Һλ�߶�
	
	sPID  s = { 1 , 0.5 , 0.2, 0 ,0 ,0 ,0};
	sPID  dPID = {0 , 0 , 0, 0 ,0 ,0 ,0};
	int a =0;
		
 	u16 adcx;
	float temp;
	float  pid_out;
	float u  ;    //�ջ�������ϵͳ�����u
	float  deviation; // c - u   Ŀ��ֵ - ��ǰֵ
	int loop_n = 0  ;    //  while ѭ���Ĵ���
     

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	pwm_realize();
	
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();			//��ʼ��LED 

	
 	LCD_Init();         //��ʼ��LCD�ӿ�
	Adc_Init();         //��ʼ��ADC
	POINT_COLOR=BLUE; 
	

	
	while(1)
	{  


		
		
//********************************************************	
		printf("%d , %lf\r\n",loop_n ,curHeight);
		
		pValue[loop_n] =  s.Kp + dPID.Kp;
		printf("%d , %lf\r\n",loop_n , pValue[loop_n]);
		
		iValue[loop_n] =  s.Ki + dPID.Ki;
		printf("%d , %lf\r\n",loop_n , iValue[loop_n]);
		
		dValue[loop_n] =  s.Kd + dPID.Kd;
        printf("%d , %lf\r\n",loop_n , dValue[loop_n]);

		
  	    dPID  =   pidController( tarHeight ,curHeight , &s);	     //Ŀ��߶Ⱥ͵�ǰ�߶�
		pid_out = (s.Kp+dPID.Kp)*s.e + (s.Kd+dPID.Kd)*s.ec + (s.Ki+dPID.Ki)*s.sumE;
	
		 
	
//    ��Ӧ���߲���
		curData[loop_n]  = curHeight;                            //��ǰ�߶����鱻��ʼ�����
//		curHeight = inertia_delay_element(pid_out , 1 , 0.3);   //ʱ�䳣����Ϊ1 ���ӳ�ʱ��Ҳ��Ϊ1
        curHeight = second_element(pid_out, 1 , 1 , 1);
		loop_n ++;

        if(loop_n == 300)  
		{			
			break;
			
		}
//	    delay_ms(10);
		
		
	}
	

	showCur(curData , 300 , tarHeight);
		
	
	
	POINT_COLOR = RED; 
//	showParameterCur(pValue  ,300 , s.Kp );
//    LCD_ShowString(400 , 400 , 50 , 16 , 16 ,"p-1.0" ); 

	POINT_COLOR = BLUE; 
//	showParameterCur(iValue  ,300 , s.Ki);
//    LCD_ShowString(400 , 500 , 50 , 16 , 16 ,"i-0.5" ); 
	
	POINT_COLOR = BLACK; 
//	showParameterCur(dValue  ,300 , s.Kd);
//	LCD_ShowString(400 , 550 , 50 , 16 , 16 ,"d-0.3" ); 
	
	
	
	
}        



int main()
{
	double A[M][N] =  {1 , 2 , 3   ,   4 , 5 , 6};
	double B[N][M] =  { 1 , 2 ,   3 , 4,    5, 6};
	double AB[M][M] =  { 0 ,0,   0,0};
	
	double A2[2][1] =  {1 , 2 };
	double B2[1][2] =  { 4 , 5};
	double AB2[M][M] =  { 0 ,0,   0,0};
	
	double C[2][2] =  {1 , 2 , 3 ,4};
	double D[2][2] =  {   3 , 4 , 5 , 6};
	double E[2][2] =  { 0 ,0,   0,0};
	
	//ǰ�涼�Ǿ�����ԣ� ��Щ������Ŀ�������
	double s[2][2] = { 1 , 0 , 1 , 0};
	double matrixA[2][2] = { 0 , -1 , 1 , 2};
	double matrixB[2][1] = { 0 , 1};
	double tmpMatrix[2][2] = { 0 , 0 , 0 ,0};
	double k = 0 , k2 = 0;
	double tmp2[2][2] = { 0 , 0 , 0 ,0};
//	double matrixK[1][2] = { k , k2};
	double tmp3[2][2] = { 0 , 0, 0 , 0};
	
	double src[2][2] = { 1 , 1 , 1, 2};
	double dst[2][2] = { 0, 0 ,0 ,0 };
	
	double right[2][1] = { 2 , 3 };
	double matrixK[2][1] = { 0  , 0 };
	double u = 0 ;
	
	
	//����ϵͳ��״̬�����õ���
	float  curSpeed = 0;   
	float  lastHeight = 0;
	
	int serial_i = 0;   //����ѭ����ӡ�õ�
	
	u8 key;           //�����ֵ
	
	
	u16 adcx;
	float temp;

	int loop_n = 0  ;    //  while ѭ���Ĵ���
	
	float  curHeight = 0;      // ��ǰҺλ�߶�
    float  tarHeight = 100;     //  Ŀ��Һλ�߶�
	float  roll_output = 0;     //�����Ż����
	int i  = 0;
     

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();			//��ʼ��LED 

	
// 	LCD_Init();         //��ʼ��LCD�ӿ�
	Adc_Init();         //��ʼ��ADC
	POINT_COLOR=BLUE; 

   //��ʼ���ο��켣
   for(i = 0; i < 300; i++)
   {
	   refer_point[i] = i;
	   
   }

//���������   
//   printMatrix( A , M , N);
//    printMatrix( B , N , M );
//   matrixTimesVec(A , B , AB);
//    printMatrix( B , N , M );
 //  printMatrix( AB , M , M );
   
//   matrixTimesVec(A2 , B2 , AB2);
//   printMatrix(AB2 , M , M);
   
   
//   vecPlus(s , matrixA , tmpMatrix);      //��������ӽ��������ʱ��������
//	matrixTimesVec��matrixB , matrixK , tmp3);
	
   
   
//���������   
//   vecPlus(C ,D , E);
 //  printMatrix(E , M  ,  M);
   
//   transpose(src, dst);
	inverseMatrix(src ,dst);
////	printMatrix(dst , 2 , 2);
	
	matrixTimesVec3(dst , right , matrixK);
////	printMatrix2(matrixK , 2 );
 

   
   
   
 #if 0  
	while(1)    //����һ�׹���ϵͳ��MPC�㷨
	{  
		
		curData[loop_n]  = curHeight;   
//		tarHeight = refer_point[loop_n];

		//����Ԥ��ģ�͵õ����ֿ����� �����룺1.��һʱ�̵�����߶� �� 2.��ǰ��Ԥ������   �����
		roll_output =  get_control_height(tarHeight  , curHeight , 2);
					 
		curHeight = inertia_delay_element(roll_output , 2 , 0.3);   //ʱ�䳣����Ϊ1 ���ӳ�ʱ��Ҳ��Ϊ1
			
		
			
		delay_ms(10);
			
		     	
		
		
//		printf("%d , �����Ż����:%lf , ��ǰ�߶�%lf\r\n",loop_n , roll_output ,curHeight);
		loop_n++;
		
		 if(loop_n == 300)  
		{			
			break;
			
		}
		
		
	}
	
//	showCur(refer_point,300 , tarHeight);
	
	POINT_COLOR = RED; 
//	showCur(curData , 300 , tarHeight);

 #else  
	while(1)                 //�Զ���ϵͳ ��״̬�����㷨
	{
		 
		
	
		
		
		curData[loop_n]  = curHeight;  
		//��ÿ�����u
		u = (matrixK[0][0] * curHeight  + matrixK[0][0] * curSpeed ) * ( -1) + tarHeight; 
		
		lastHeight = curHeight;
		curHeight = second_element(u, 1 , 1 , 1);
		
		curSpeed = (curHeight - lastHeight) / 1;
		
		
//		printf("%d , �����Ż����:%lf , ��ǰ�߶�%lf\r\n",loop_n , u ,curHeight);
		loop_n++;
		
		 if(loop_n == 300)  
		{			
			break;
			
		}
	
	}
	
//	delay_ms(5000);
//	for( serial_i = 0; serial_i < 300; serial_i++){
//		printf("%lf\r\n",curData[serial_i]);
//	}
	
//	showCur(curData , 300 , tarHeight);
	


 
  
	
	LED_Init();				//��ʼ��LED�˿� 

	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED0=0;				  	//�ȵ������
	while(1)
	{
		key=KEY_Scan(0);		//�õ���ֵ
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//���Ʒ�����
					printf("%d\r\n",4);
				
//					BEEP=!BEEP;
					break;
				case KEY0_PRES:	//����LED0��ת
					LED0=!LED0;
				
				 for( serial_i = 0; serial_i < 300; serial_i++){
					printf("%lf\r\n",curData[serial_i]);
				}
				
//				 for( serial_i = 0; serial_i < 10; serial_i++){
//					printf("%d\r\n",1);
//				}
				printf("%d\r\n",1);
//				 showCur(curData , 300 , tarHeight);
				
				
					break;
				case KEY1_PRES:	//����LED1��ת	 
					LED1=!LED1;
				printf("%d\r\n",2);
				 
					break;
				case KEY2_PRES:	//ͬʱ����LED0,LED1��ת 
					printf("%d\r\n",3);
				
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}



	
	
	
	
	
	
	
	
#endif
	
	
}       




