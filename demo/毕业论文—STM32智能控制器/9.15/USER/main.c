#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "pwm.h"
#include "algorithms.h"

#include "key.h"
//为了读取文件
#include "stdio.h"    
#include <stdlib.h>
#include <string.h>



//矩阵的相关头文件
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

//	打开字库文件hzk16*/
//	if ((HZK = fopen("hzk16", "rb")) == NULL )
//	{
//		printf("Can't open haz16 字库文件\n");
//		//exit(0);
//	}
//	HZK = fopen("hzk16", "rb");
//	/*区码=内码(高字节)-160??位码=内码(低字节)-160*/
//	qh = *(hz)-160;	  //从1开始编号
//	wh = *(hz + 1) - 160; //从1开始编号
//	offset = (94 * (qh - 1) + (wh - 1)) * 32; //每个汉字32字节，16*16=512位，512/8=32 
//	fseek(HZK, offset, SEEK_SET);	/*将文件指针移动到偏移量的位置*/
//	fread(buff, 32, 1, HZK);	/*从偏移量的位置读取32个字节*/
//	fclose(HZK);   */





//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本  
//技术支持：www.openedv.com
//淘宝店铺：
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

 //从ad获取的电压代表相应得液面高度信号
float  adc_voltage2height(float voltage)
{
	return voltage;
}

/*一阶惯性环节 + 延迟环节  函数实现  */
float  inertia_delay_element(float giveValue , float T , float time)  // 给定输入值，时间常数T , 延迟时间time
{
	
	  float result;
	static  float ResultValueBack = 0;
	delay_ms(10);


	result = (T*ResultValueBack + giveValue)/(1+T);  //c(t)=(r(t)+Tc(t-1))/(T+1);

	ResultValueBack = result;

	return result;
	
}

/*二阶惯性环节 + 延迟环节  函数实现  */
float  second_element(float giveValue , float T1 ,float T2, float k )  // 给定输入值，时间常数T
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



	float refer_point[300] = {0}; //参考轨迹
    float curData[300] =  {0};   //曲线上的点
	float pValue[300]  =  {0};
	float  iValue[300] =  {0};
	float  dValue[300] =  {0};

//********************矩阵的相关实现*****************************************	
	
	/*
	矩阵A和向量b，相乘结果存在Ab里
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

//求矩阵的转置矩阵
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

//求已知矩阵的逆矩阵
void   inverseMatrix (  double A[2][2], double B[2][2])
{
	//先求出矩阵的行列式
	double res = 0;
	res = ((A[0][0]) * (A[1][1])) - ((A[0][1]) * (A[1][0]));
	
	//再求出伴随矩阵， 也就是代数余子式
	B[0][0] = A[1][1];
	B[1][1] = A[0][0];
	B[0][1] = A[1][0] * (-1);
	B[1][0] = A[0][1] * (-1);
	
//最后， 求出最终的逆矩阵
	B[0][0] = A[1][1] / res ;
	B[1][1] = A[0][0] / res;
	B[0][1] = A[1][0] / res* (-1);
	B[1][0] = A[0][1] / res* (-1);



}



	
//打印矩阵
void  printMatrix(double A[][2] , int k , int z)      // 传递数组和行数和列数  
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

//打印矩阵2
void  printMatrix2(double A[][1] , int k )      // 传递数组和行数和列数  
{
	int i = 0 , j = 0;
	for( i = 0; i < k ; i++)
	{
//		printf("A[%d][%d] = %lf\r\n" , i , j , A[i][0]);
	}
}
	
	

int main1(void)    //使用模糊PID控制一阶、二阶系统
{ 
	
	
	float  curHeight = 0;      // 当前液位高度
    float  tarHeight = 100;     //  目标液位高度
	
	sPID  s = { 1 , 0.5 , 0.2, 0 ,0 ,0 ,0};
	sPID  dPID = {0 , 0 , 0, 0 ,0 ,0 ,0};
	int a =0;
		
 	u16 adcx;
	float temp;
	float  pid_out;
	float u  ;    //闭环负反馈系统的输出u
	float  deviation; // c - u   目标值 - 当前值
	int loop_n = 0  ;    //  while 循环的次数
     

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	pwm_realize();
	
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();			//初始化LED 

	
 	LCD_Init();         //初始化LCD接口
	Adc_Init();         //初始化ADC
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

		
  	    dPID  =   pidController( tarHeight ,curHeight , &s);	     //目标高度和当前高度
		pid_out = (s.Kp+dPID.Kp)*s.e + (s.Kd+dPID.Kd)*s.ec + (s.Ki+dPID.Ki)*s.sumE;
	
		 
	
//    响应曲线测试
		curData[loop_n]  = curHeight;                            //当前高度数组被初始化完毕
//		curHeight = inertia_delay_element(pid_out , 1 , 0.3);   //时间常数设为1 ，延迟时间也设为1
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
	
	//前面都是矩阵测试， 这些才是项目所需矩阵
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
	
	
	//二阶系统的状态反馈用的上
	float  curSpeed = 0;   
	float  lastHeight = 0;
	
	int serial_i = 0;   //串口循环打印用的
	
	u8 key;           //保存键值
	
	
	u16 adcx;
	float temp;

	int loop_n = 0  ;    //  while 循环的次数
	
	float  curHeight = 0;      // 当前液位高度
    float  tarHeight = 100;     //  目标液位高度
	float  roll_output = 0;     //滚动优化输出
	int i  = 0;
     

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();			//初始化LED 

	
// 	LCD_Init();         //初始化LCD接口
	Adc_Init();         //初始化ADC
	POINT_COLOR=BLUE; 

   //初始化参考轨迹
   for(i = 0; i < 300; i++)
   {
	   refer_point[i] = i;
	   
   }

//两矩阵相乘   
//   printMatrix( A , M , N);
//    printMatrix( B , N , M );
//   matrixTimesVec(A , B , AB);
//    printMatrix( B , N , M );
 //  printMatrix( AB , M , M );
   
//   matrixTimesVec(A2 , B2 , AB2);
//   printMatrix(AB2 , M , M);
   
   
//   vecPlus(s , matrixA , tmpMatrix);      //两矩阵相加结果放在临时矩阵那里
//	matrixTimesVec（matrixB , matrixK , tmp3);
	
   
   
//两矩阵相加   
//   vecPlus(C ,D , E);
 //  printMatrix(E , M  ,  M);
   
//   transpose(src, dst);
	inverseMatrix(src ,dst);
////	printMatrix(dst , 2 , 2);
	
	matrixTimesVec3(dst , right , matrixK);
////	printMatrix2(matrixK , 2 );
 

   
   
   
 #if 0  
	while(1)    //对于一阶惯性系统用MPC算法
	{  
		
		curData[loop_n]  = curHeight;   
//		tarHeight = refer_point[loop_n];

		//根据预测模型得到本轮控制量 （输入：1.上一时刻的输出高度 ， 2.当前的预测输入   输出）
		roll_output =  get_control_height(tarHeight  , curHeight , 2);
					 
		curHeight = inertia_delay_element(roll_output , 2 , 0.3);   //时间常数设为1 ，延迟时间也设为1
			
		
			
		delay_ms(10);
			
		     	
		
		
//		printf("%d , 滚动优化输出:%lf , 当前高度%lf\r\n",loop_n , roll_output ,curHeight);
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
	while(1)                 //对二阶系统 用状态反馈算法
	{
		 
		
	
		
		
		curData[loop_n]  = curHeight;  
		//求得控制量u
		u = (matrixK[0][0] * curHeight  + matrixK[0][0] * curSpeed ) * ( -1) + tarHeight; 
		
		lastHeight = curHeight;
		curHeight = second_element(u, 1 , 1 , 1);
		
		curSpeed = (curHeight - lastHeight) / 1;
		
		
//		printf("%d , 滚动优化输出:%lf , 当前高度%lf\r\n",loop_n , u ,curHeight);
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
	


 
  
	
	LED_Init();				//初始化LED端口 

	KEY_Init();       //初始化与按键连接的硬件接口
	LED0=0;				  	//先点亮红灯
	while(1)
	{
		key=KEY_Scan(0);		//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
					printf("%d\r\n",4);
				
//					BEEP=!BEEP;
					break;
				case KEY0_PRES:	//控制LED0翻转
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
				case KEY1_PRES:	//控制LED1翻转	 
					LED1=!LED1;
				printf("%d\r\n",2);
				 
					break;
				case KEY2_PRES:	//同时控制LED0,LED1翻转 
					printf("%d\r\n",3);
				
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}



	
	
	
	
	
	
	
	
#endif
	
	
}       




