#ifdef  _ENCODER_H
#define _ENCODER_H

void Encoder_TIM2_Init(void);   // ������1��ʼ������
void Encoder_TIM4_Init(void);   // ������2��ʼ������
int Read_Speed(int TIMx);       // �������ٶȶ�ȡ����
void TIM2_IRQHandler(void);     // ��ʱ��2�жϷ�����
void TIM4_IRQHandler(void);     // ��ʱ��4�жϷ�����
#endif

