/**
  *************************************************************************************************************************
  * @file    : motor.h
  * @author  : AMKL
  * @version : V1.0
  * @date    : 2022-XX-XX
  * @brief   : �������H�ļ�
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef _MOTOR_H
#define	_MOTOR_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "sys.h" 

/* define ---------------------------------------------------------------------------------------------------------------*/
#define Ain1  PBout(14)
#define Ain2  PBout(15)

#define Bin1  PBout(13)
#define Bin2  PBout(3)
/* function -------------------------------------------------------------------------------------------------------------*/
void Motor_Init(void);
void Limit(int *motoA,int *motoB);
int  abs(int p);
void Load(int moto1,int moto2);


#endif /* _MOTOR_H */

/*****************************************************END OF FILE*********************************************************/	


