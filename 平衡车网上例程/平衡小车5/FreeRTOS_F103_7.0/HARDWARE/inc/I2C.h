#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
  	
#define IIC1_EN	1	
#define IIC2_EN	0


#if IIC1_EN
//IO方向设置
#define IIC1_SDA_IN()  {GPIOB->CRH&=0X0FFFFFFF;GPIOB->CRH|=(u32)8<<28;}
#define IIC1_SDA_OUT() {GPIOB->CRH&=0X0FFFFFFF;GPIOB->CRH|=(u32)3<<28;}

//IO操作函数	 
#define IIC1_SCL		PBout(14)	//SCL
#define IIC1_SDA		PBout(15)	//SDA	 
#define IIC1_READ_SDA   PBin(15)		//输入SDA 

//IIC所有操作函数
void IIC1_Init(void);                	//初始化IIC的IO口				 
void IIC1_Start(void);					//发送IIC开始信号
void IIC1_Stop(void);	  				//发送IIC停止信号
void IIC1_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC1_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 IIC1_Wait_Ack(void); 				//IIC等待ACK信号
void IIC1_Ack(void);					//IIC发送ACK信号
void IIC1_NAck(void);					//IIC不发送ACK信号

void IIC1_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC1_Read_One_Byte(u8 daddr,u8 addr);
#endif

#if IIC2_EN
//IO方向设置
#define IIC2_SDA_IN()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)8<<20;}
#define IIC2_SDA_OUT() {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)3<<20;}

//IO操作函数	 
#define IIC2_SCL		PBout(6)	//SCL
#define IIC2_SDA		PBout(5)	//SDA	 
#define IIC2_READ_SDA   PBin(5)		//输入SDA 

//IIC所有操作函数
void IIC2_Init(void);                	//初始化IIC的IO口				 
void IIC2_Start(void);					//发送IIC开始信号
void IIC2_Stop(void);	  				//发送IIC停止信号
void IIC2_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC2_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 IIC2_Wait_Ack(void); 				//IIC等待ACK信号
void IIC2_Ack(void);					//IIC发送ACK信号
void IIC2_NAck(void);					//IIC不发送ACK信号

void IIC2_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC2_Read_One_Byte(u8 daddr,u8 addr);
int I2C2_WriteData(u8 ADD,u8 *buff,u32 len);
int I2C2_ReadData(u8 ADD,u8 *buff,u32 len);
#endif

#endif
















