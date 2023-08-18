#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

#define USART_REC_LEN  			200			//�����������ֽ��� 200
#define EN_USART1_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1			//ʹ�ܣ�1��/��ֹ��0������2����
#define EN_USART3_RX 			0			//ʹ�ܣ�1��/��ֹ��0������3����

extern u8  USART1_RX_BUF[USART_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART2_RX_BUF[USART_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART3_RX_BUF[USART_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;					//����״̬���	
extern u16 USART2_RX_STA;					//����״̬���
extern u16 USART3_RX_STA;					//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart1_init(u32 pclk2,u32 bound);
void uart2_init(u32 pclk2,u32 bound);
void uart3_init(u32 pclk2,u32 bound);

void uart2_printf(char* fmt,...);

#endif	   
















