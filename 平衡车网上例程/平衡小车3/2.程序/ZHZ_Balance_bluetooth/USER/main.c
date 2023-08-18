#include "stm32f10x.h"
#include "sys.h" 

int PWM_MAX=7200,PWM_MIN=-7200;	// PWM�޷�����
int MOTO1,MOTO2;

float Pitch,Roll,Yaw;	          // Pitch�������ǣ�Roll������ǣ�Yaw��ƫ����
short gyrox,gyroy,gyroz;        // ���ٶ�
short aacx,aacy,aacz;           // ���ٶ�
int Encoder_Left,Encoder_Right; // ���������ݣ��ٶȣ�

int main(void)	
{
	delay_init();
	NVIC_Config();
	uart1_init(115200);
	uart3_init(9600);
  USART3_Send_String("AT+NAME hc_05_sxwl \r\n");
	OLED_Init();
	OLED_Clear();
	
	MPU_Init();
	mpu_dmp_init();
	MPU6050_EXTI_Init();
	
	Encoder_TIM2_Init();
	Encoder_TIM4_Init();
	Motor_Init();
	PWM_Init_TIM1(0,7199);
  while(1)	
	{
		OLED_Float(0,0,Roll,3);
	} 	
}



