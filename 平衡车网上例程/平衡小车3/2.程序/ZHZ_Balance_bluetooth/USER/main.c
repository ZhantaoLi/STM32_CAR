#include "stm32f10x.h"
#include "sys.h" 

int PWM_MAX=7200,PWM_MIN=-7200;	// PWM限幅变量
int MOTO1,MOTO2;

float Pitch,Roll,Yaw;	          // Pitch：俯仰角，Roll：横滚角，Yaw：偏航角
short gyrox,gyroy,gyroz;        // 角速度
short aacx,aacy,aacz;           // 加速度
int Encoder_Left,Encoder_Right; // 编码器数据（速度）

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



