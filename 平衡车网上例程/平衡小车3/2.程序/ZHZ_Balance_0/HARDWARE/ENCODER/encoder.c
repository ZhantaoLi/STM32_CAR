#include "encoder.h"
#include "sys.h"

// ������1��ʼ������
void Encoder_TIM2_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);  // ������ʱ��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE); // ����GPIOʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // ��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   // ������1:PA0/PA1
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStruct);	
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        // ����Ƶ
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    // ���ϼ���
  TIM_TimeBaseInitStruct.TIM_Period = 65535;                      // ��װ��ֵ65535
  TIM_TimeBaseInitStruct.TIM_Prescaler =0;                        // ��Ƶϵ��0
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
  
  // ���������ú���: ��ʱ��2��ģʽ3��������
  TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);  
  
  TIM_ICStructInit(&TIM_ICInitStruct);
  TIM_ICInitStruct.TIM_ICFilter = 10;       // �˲�������Ϊ10
  TIM_ICInit(TIM2,&TIM_ICInitStruct);
  
  TIM_ClearFlag(TIM2,TIM_FLAG_Update);      // �����ʱ����־λ
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  // ��ʱ��2��������£�ʹ��
  TIM_SetCounter(TIM2,0);                   // ��ʱ��������
  TIM_Cmd(TIM2,ENABLE);                     // ��ʱ��2ʹ��
}

// ������2��ʼ������
void Encoder_TIM4_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);  // ������ʱ��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); // ����GPIOʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // ��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   // ������2:PB6/PB7
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_InitStruct);	
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // ����Ƶ
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���
  TIM_TimeBaseInitStruct.TIM_Period = 65535;                    // ��װ��ֵ65535
  TIM_TimeBaseInitStruct.TIM_Prescaler = 0;                     // ��Ƶϵ��0
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
  
  // ���������ú�������ʱ��4��ģʽ3��������
  TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);  
  
  TIM_ICStructInit(&TIM_ICInitStruct);
  TIM_ICInitStruct.TIM_ICFilter = 10;       // �˲�������Ϊ10
  TIM_ICInit(TIM4,&TIM_ICInitStruct);
  
  TIM_ClearFlag(TIM4,TIM_FLAG_Update);      // �����ʱ��������±�־λ
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  // ��ʱ��4��������£�ʹ��
  TIM_SetCounter(TIM4,0);                   // ��ʱ��������
  TIM_Cmd(TIM4,ENABLE);                     // ��ʱ��2ʹ��
}

// �������ٶȶ�ȡ����
// ��ڲ�������ʱ��
int Read_Speed(int TIMx)
{
  int value_1;
  switch(TIMx)
  {
    case 2:
      value_1 = (short)TIM_GetCounter(TIM2);  // �ɼ��������ļ���ֵ������
      TIM_SetCounter(TIM2,0);   // ����ʱ���ļ���ֵ����
      break;
    case 4:
      value_1 = (short)TIM_GetCounter(TIM4);  // �ɼ��������ļ���ֵ������
      TIM_SetCounter(TIM4,0);   // ����ʱ���ļ���ֵ����
      break; 
    default: value_1 = 0;
  }
  return value_1;
}

// ��ʱ��2�жϷ�����
void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)  // �жϱ�־λ��1
  {
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  // ����жϱ�־λ
  }
}

// ��ʱ��4�жϷ�����
void TIM4_IRQHandler()
{
  if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)  // �жϱ�־λ��1
  {
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  // ����жϱ�־λ
  }
}





