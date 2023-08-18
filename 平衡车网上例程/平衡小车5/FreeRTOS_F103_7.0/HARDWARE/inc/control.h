#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

#define PI 3.14159265

int myabs(int a);
int balance_UP(float Angle,float Mechanical_balance,float Gyro);
int velocity(int encoder_left,int encoder_right);
int turn(int encoder_left,int encoder_right,float gyro);

extern int 	 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right;		//����ң����صı���
extern float pitch,roll,yaw;								//ŷ����
extern short aacx,aacy,aacz;								//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;								//������ԭʼ����
extern int   Encoder_Left,Encoder_Right;					//���ұ��������������

#endif
