#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

#define PI 3.14159265

int myabs(int a);
int balance_UP(float Angle,float Mechanical_balance,float Gyro);
int velocity(int encoder_left,int encoder_right);
int turn(int encoder_left,int encoder_right,float gyro);

extern int 	 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right;		//蓝牙遥控相关的变量
extern float pitch,roll,yaw;								//欧拉角
extern short aacx,aacy,aacz;								//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;								//陀螺仪原始数据
extern int   Encoder_Left,Encoder_Right;					//左右编码器的脉冲计数

#endif
