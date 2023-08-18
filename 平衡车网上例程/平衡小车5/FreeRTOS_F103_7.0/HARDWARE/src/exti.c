#include "exti.h"
#include "control.h"
#include "inv_mpu.h"
#include "mpu6050.h"
#include "timer.h"
#include "led.h"
#include "adc.h"


#define Batter_Low  (10.8)


float	Mechanical_angle=3.8;				//��е��ֵ
int		Balance_Pwm,Velocity_Pwm,Turn_Pwm;

int		Moto1=0,Moto2=0;					//������������ո��������PWM
float	Volatage;							//��ص�ѹ������صı���
u8		flag_fall=0;						//ˤ����־λ
u8		LowVol_Flag = 0;


void Exti_Process(void);
void Turn_Off(float angle, float voltage);
void Xianfu_Pwm(void);
void Set_Pwm(int moto1,int moto2);
void Voltage_get(void);
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��
	
	GPIOB->CRH&=0XFF0FFFFF;	//PB13���ó�����	  
	GPIOB->CRH|=0X00800000; 				   
	GPIOB->ODR|=1<<13;	   	//PB13 ����
	
 	Ex_NVIC_Config(GPIO_B,13,FTIR); 	//�½��ش���   
	MY_NVIC_Init(7,0,EXTI15_10_IRQn,4);	//��ռ2�������ȼ�0����2	   
}

void EXTI15_10_IRQHandler(void) 
{    
	if(PBin(13)==0)		
		{
		EXTI->PR=1<<13; 
		LEDTest = 0;		
		Exti_Process();
		LEDTest = 1;
		}
}

void Exti_Process(void)
{
		mpu_dmp_get_data(&pitch,&roll,&yaw);					//===�õ�ŷ���ǣ���̬�ǣ�������
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);				//===�õ�����������
		
		Encoder_Left=Read_Encoder(2);							//===��ȡ��������ֵ����Ϊ�����������ת��180�ȵģ����Զ�����һ��ȡ������֤�������һ��
		Encoder_Right=Read_Encoder(3);							//===��ȡ��������ֵ
		
//		Voltage_get();
	
		Balance_Pwm =balance_UP(roll,Mechanical_angle,gyrox);	//===ƽ�⻷PID����	
		Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);		//===�ٶȻ�PID����
		
		if(1==Flag_Left||1==Flag_Right)   
		Turn_Pwm =turn(Encoder_Left,Encoder_Right,gyroz);		//===ת��PID����
		else Turn_Pwm=(0)*gyroz;
		
		Moto1=Balance_Pwm-Velocity_Pwm-Turn_Pwm;				//===�������ֵ������PWM
		Moto2=Balance_Pwm-Velocity_Pwm+Turn_Pwm;				//===�������ֵ������PWM
		Xianfu_Pwm();											//===PWM�޷�
//		Turn_Off(roll,Volatage);								//===���Ƕ��Լ���ѹ�Ƿ�����
		Turn_Off(roll,11);								//===���Ƕ��Լ���ѹ�Ƿ�����	
		Set_Pwm(Moto1,Moto2);									//===��ֵ��PWM�Ĵ��� 
}


void Turn_Off(float angle, float volatage)
{
	static u8 vol_t = 0;
	if(volatage<Batter_Low)
		{
		vol_t++;
		if(vol_t>200)
			vol_t = 200,LowVol_Flag = 1;
		}
	else 
		vol_t = 0,LowVol_Flag = 0;
	
	
	if((angle<-40)||(angle>40)||(LowVol_Flag==1))	 
		{	                                   																		 
		Moto1=0;
		Moto2=0;
		flag_fall=1;
		}		
	else 				
		flag_fall=0;
}


void Xianfu_Pwm(void)
{
    if(Moto1<-7000 ) Moto1=-7000 ;//MAX 7200
	if(Moto1>7000 )  Moto1=7000 ;
	if(Moto2<-7000 ) Moto2=-7000 ;
	if(Moto2>7000 )  Moto2=7000 ;
}


void Set_Pwm(int moto1,int moto2)
{
	if(moto1<0)	AIN2=1,	AIN1=0;
	else		AIN2=0,	AIN1=1;
	
	if(moto2<0)	BIN1=0,	BIN2=1;
	else		BIN1=1,	BIN2=0;
	
	PWM1=myabs(moto1);
	PWM2=myabs(moto2);	
}

void Voltage_get(void)
{
	u16 temp = 0;
	float vol = 0;
	temp = Get_Adc(5);
	vol = (temp*3.3/4095*4);
	Volatage = Volatage*0.8;
	Volatage = Volatage+vol*0.2;
}









