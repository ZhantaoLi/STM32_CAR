#include "motor.h"
#include "tim.h"
/*
TB6612
A/BIN1	A/BIN2	模式状态
H		H		制动
H		L		正转
L		H		反转
L		L		制动
当加入了PWM后，便可以通过占空比调节速度
一种是IN1和IN2固定，PWM脚输入PWM，此时是配合慢衰减调速
    例如：IN1为1，IN2为0，PWM为PWM，则正转和慢衰减相互切换；
另外一种是PWM脚为高电平，IN1、IN2中的一个固定另一个为PWM输入，此时是配合快衰减调速
	例如，IN1为1，IN2为PWM输入，PWM为1，则正转与快衰减相互切换


A4950
AIN1		AIN2		直流电机状态（AO1和AO2）
任意		任意		停止
0		0		停止
0		1		正转
1		0		反转
1		1		刹车
A4950驱动板的四种驱动方式：
标号 1:芯片 IN1 端口输入一定的占空比 PWM，IN2 为低电平，此时芯片的输出端口会出去一个正电流。为电机正转。
标号 2:芯片IN1 端口输入低电平，IN2 端口输入一定的占空比 PWM，此时芯片的输出端口会出去一个负电流。为电机反转。
标号 3:芯片IN1 端口输入高电平，IN2 端口输入一定的占空比 PWM，此时芯片的输出端口会出去一个正电流。为电机正转。
标号 4:芯片IN1 端口输入一定的占空比 PWM，IN2 为高电平，此时芯片的输出端口会出去一个负电流。为电机反转。
我们可以选择标号 1和标号 4，只需要在一个 IN1 输入 pwm.另一个IN2 输入高电平或者低电平就可以实现控制电机的速度和正反转。

当xIN中有一个恒为低电平，另一个为PWM时:采取正反转与滑动/快衰减，占空比越大，转速越快。
当xIN中有一个恒为高电平，另一个为PWM时:采取正反转与制动/慢衰减，占空比越小，转速越快。（重点看一下，区别于TB6612）
*/
void Motor_Set(int Motor1, int Motor2)
{
	//取反更适合控制习惯，大于0小车向前运动
	Motor1 =-Motor1;
	Motor2 =-Motor2;
    // 1.先根据正负设置方向GPIO 高低电平
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

    // 2.然后设置占空比
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
