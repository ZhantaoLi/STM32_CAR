#include "exti.h"

void MPU6050_EXTI_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
  // ����ʱ��
  // �ⲿ�жϣ���Ҫʹ��AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;          // PB5����Ϊ��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);  // �ⲿ�жϺ�GPIOӳ������
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line5;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;    // �жϴ���
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;// MPU6050�����ж�ʱ����һ���½���
	EXTI_Init(&EXTI_InitStruct);
}



