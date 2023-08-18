#include "control.h"	


float	balance_UP_KP=280; 	 //ֱ����PD
float	balance_UP_KD=0.8;

float	velocity_KP=90;		//�ٶȻ�PI
float	velocity_KI=0.45;

u8		UltrasonicWave_Voltage_Counter=0;

int		Flag_Qian,Flag_Hou,Flag_Left,Flag_Right;	//����ң����صı���
int		Encoder_Left,Encoder_Right;					//���ұ��������������
float	pitch,roll,yaw;								//ŷ����(��̬��)
short	aacx,aacy,aacz;								//���ٶȴ�����ԭʼ����
short	gyrox,gyroy,gyroz;							//������ԭʼ����
int		Encoder_Left,Encoder_Right;					//���ұ��������������


int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ���еƽ��Ƕȣ���е��ֵ�������ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int balance_UP(float Angle,float Mechanical_balance,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle-Mechanical_balance;    							 //===���ƽ��ĽǶ���ֵ�ͻ�е���
	 balance=balance_UP_KP*Bias+balance_UP_KD*Gyro;  //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	 return balance;
}

/**************************************************************************
�������ܣ��ٶ�PI����
��ڲ����������������ֵ
����  ֵ���ٶȿ���PWM
**************************************************************************/
int velocity(int encoder_left,int encoder_right)
{  
    static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Encoder_Integral;
		if(1==Flag_Qian)				
		{
			Movement=20;
		}
		else if(1==Flag_Hou)//���յ�����APPң������		
		{
			Movement=-20;//�趨�ٶ�
		}
		else//û�н��ܵ��κε�����
		{	
			Movement=0;
		}
   //=============�ٶ�PI������=======================//	
		Encoder_Least =(Encoder_Left+Encoder_Right)-0;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
		Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
		Encoder_Integral=Encoder_Integral-Movement;                       //===����ң�������ݣ�����ǰ������
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
		if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===�����޷�	
		Velocity=Encoder*velocity_KP+Encoder_Integral*velocity_KI;        //===�ٶȿ���	
	  if(pitch<-40||pitch>40) 			Encoder_Integral=0;     						//===����رպ��������
	  return Velocity;
}
/**************************************************************************
�������ܣ�ת��PD����
��ڲ����������������ֵ��Z����ٶ�
����  ֵ��ת�����PWM
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//ת�����
{
	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=44,Kp=20,Kd=0;     
	  //=============ң��������ת����=======================//
	  //��һ������Ҫ�Ǹ�����תǰ���ٶȵ����ٶȵ���ʼ�ٶȣ�����С������Ӧ��
  	if(1==Flag_Left||1==Flag_Right)                      
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(encoder_left+encoder_right);      
			Turn_Convert=55/Encoder_temp;
			if(Turn_Convert<0.6)Turn_Convert=0.6;
			if(Turn_Convert>3)Turn_Convert=3;
		}	
	  else
		{
			Turn_Convert=0.9;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
		else if(1==Flag_Right)	     Turn_Target+=Turn_Convert; 
		else Turn_Target=0;
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===ת��	�ٶ��޷�
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
		if(Flag_Qian==1||Flag_Hou==1)  Kd=0.5;        
		else Kd=0;   //ת���ʱ��ȡ�������ǵľ��� �е�ģ��PID��˼��
  	//=============ת��PD������=======================//
		Turn=-Turn_Target*Kp-gyro*Kd;                 //===���Z�������ǽ���PD����
	  return Turn;
}
