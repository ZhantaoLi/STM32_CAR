#include "motor.h"
#include "tim.h"
/*
TB6612
A/BIN1	A/BIN2	ģʽ״̬
H		H		�ƶ�
H		L		��ת
L		H		��ת
L		L		�ƶ�
��������PWM�󣬱����ͨ��ռ�ձȵ����ٶ�
һ����IN1��IN2�̶���PWM������PWM����ʱ�������˥������
    ���磺IN1Ϊ1��IN2Ϊ0��PWMΪPWM������ת����˥���໥�л���
����һ����PWM��Ϊ�ߵ�ƽ��IN1��IN2�е�һ���̶���һ��ΪPWM���룬��ʱ����Ͽ�˥������
	���磬IN1Ϊ1��IN2ΪPWM���룬PWMΪ1������ת���˥���໥�л�


A4950
AIN1		AIN2		ֱ�����״̬��AO1��AO2��
����		����		ֹͣ
0		0		ֹͣ
0		1		��ת
1		0		��ת
1		1		ɲ��
A4950�����������������ʽ��
��� 1:оƬ IN1 �˿�����һ����ռ�ձ� PWM��IN2 Ϊ�͵�ƽ����ʱоƬ������˿ڻ��ȥһ����������Ϊ�����ת��
��� 2:оƬIN1 �˿�����͵�ƽ��IN2 �˿�����һ����ռ�ձ� PWM����ʱоƬ������˿ڻ��ȥһ����������Ϊ�����ת��
��� 3:оƬIN1 �˿�����ߵ�ƽ��IN2 �˿�����һ����ռ�ձ� PWM����ʱоƬ������˿ڻ��ȥһ����������Ϊ�����ת��
��� 4:оƬIN1 �˿�����һ����ռ�ձ� PWM��IN2 Ϊ�ߵ�ƽ����ʱоƬ������˿ڻ��ȥһ����������Ϊ�����ת��
���ǿ���ѡ���� 1�ͱ�� 4��ֻ��Ҫ��һ�� IN1 ���� pwm.��һ��IN2 ����ߵ�ƽ���ߵ͵�ƽ�Ϳ���ʵ�ֿ��Ƶ�����ٶȺ�����ת��

��xIN����һ����Ϊ�͵�ƽ����һ��ΪPWMʱ:��ȡ����ת�뻬��/��˥����ռ�ձ�Խ��ת��Խ�졣
��xIN����һ����Ϊ�ߵ�ƽ����һ��ΪPWMʱ:��ȡ����ת���ƶ�/��˥����ռ�ձ�ԽС��ת��Խ�졣���ص㿴һ�£�������TB6612��
*/
void Motor_Set(int Motor1, int Motor2)
{
	//ȡ�����ʺϿ���ϰ�ߣ�����0С����ǰ�˶�
	Motor1 =-Motor1;
	Motor2 =-Motor2;
    // 1.�ȸ����������÷���GPIO �ߵ͵�ƽ
    if (Motor1 < 0)
    {
//        BIN1_SET;
        BIN1_RESET;
        BIN2_SET;
    }
    else
    {
//        BIN1_RESET;
		BIN1_SET;
		BIN2_RESET;
    }

    if (Motor2 < 0)
    {
//        AIN1_SET;
        AIN1_RESET;
        AIN2_SET;
    }
    else
    {
//        AIN1_RESET;
		AIN1_SET;
		AIN2_RESET;
    }

    // 2.Ȼ������ռ�ձ�
    if (Motor1 < 0)
    {
        if (Motor1 < -99)
            Motor1 = -99;
//        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (100 + Motor1));
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (Motor1));
    }
    else
    {
        if (Motor1 > 99)
            Motor1 = 99;
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Motor1);
    }

    if (Motor2 < 0)
    {
        if (Motor2 < -99)
            Motor2 = -99;
//        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (100 + Motor2));
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (Motor2));
    }
    else
    {
        if (Motor2 > 99)
            Motor2 = 99;
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motor2);
    }
}
