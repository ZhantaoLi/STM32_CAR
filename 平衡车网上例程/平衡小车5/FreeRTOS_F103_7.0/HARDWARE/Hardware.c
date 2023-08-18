#include "Hardware.h"

void _HARDWARE_INT(void)
{

	LED_Init();						//初始化与LED连接的硬件接口
	uart1_init(72,19200);
	uart2_init(36,19200);
	TIM1_PWM_Init(7200-1,0);
	
//	TIM1_PWM_Init(50-1,7199);
//	PWM1 = 25;
//	PWM2 = 25;
	
	TIM2_Coder_Init();
	TIM3_Coder_Init();
	Adc_Init();
	
	while(MPU_Init())				//初始化MPU6050
	{
		printf("mpu6050 err!\r\n");
		delay_xms(500);
	}
	while(mpu_dmp_init())			//初始化MPU6050的DMP模式
	{
		printf("mpu_dmp err!\r\n");
		delay_xms(500);
	}
	EXTIX_Init();
}







