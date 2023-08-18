#ifndef __USART_H
#define __USART_H
#include "sys.h" 

void uart3_init(u32 bound);
void USART3_IRQHandler(void);  
void USART_Send_Data(char data);
void USART_Send_String(char *String);
#endif


