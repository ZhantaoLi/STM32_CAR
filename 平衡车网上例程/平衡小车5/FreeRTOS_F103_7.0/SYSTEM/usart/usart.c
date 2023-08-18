#include "usart.h"	  
#include "FreeRTOS.h"  
#include "timers.h"
  
//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������ 
void uart1_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬���� 
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART1_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(14,0,USART1_IRQn,4);//��2��������ȼ� 
#endif
}
//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������ 
void uart2_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRL&=0XFFFF00FF;//IO״̬����
	GPIOA->CRL|=0X00008B00;//IO״̬���� 
	
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
	//����������
 	USART2->BRR=mantissa; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART2_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(14,0,USART2_IRQn,4);//��2��������ȼ� 
#endif
}

//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������ 
void uart3_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
	RCC->APB1ENR|=1<<18;  //ʹ�ܴ���ʱ�� 
	GPIOB->CRH&=0XFFFF00FF;//IO״̬����
	GPIOB->CRH|=0X00008B00;//IO״̬���� 
	RCC->APB1RSTR|=1<<18;   //��λ����1
	RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	   	   
	//����������
 	USART3->BRR=mantissa; // ����������	 
	USART3->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART3_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(14,0,USART3_IRQn,4);//��2��������ȼ� 
#endif
}



//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART1->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////



#if EN_USART1_RX  //���ʹ���˽���
//����1�жϷ������ 	
u8 USART1_RX_BUF[USART_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.
u16 USART1_RX_STA=0;				//����״̬���,bit15:������ɱ�־,bit14~0:���յ�����Ч�ֽ���	  
extern xTimerHandle	Usart1RX_Timer_Handle;
void Usart1RX_vTimerCallback(xTimerHandle xTimer){USART1_RX_STA |= 0x8000;} 
void USART1_IRQHandler(void)
{
	u8 ucTemp;	
	if(USART1->SR&(1<<5))//���յ�����
	{	 
		ucTemp=USART1->DR; 
		if((USART1_RX_STA&0x8000)==0)//����δ���
		{		
			USART1_RX_BUF[USART1_RX_STA&0X7FFF]=ucTemp;
			USART1_RX_STA++;
			xTimerResetFromISR(Usart1RX_Timer_Handle,0);
		}	
	} 
} 
#endif	



#if EN_USART2_RX	//���ʹ���˽���
//����2�жϷ������ 	
u8 USART2_RX_BUF[USART_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.
u16 USART2_RX_STA=0;				//����״̬���,bit15:������ɱ�־,bit14~0:���յ�����Ч�ֽ���
extern xTimerHandle	Usart2RX_Timer_Handle;
void Usart2RX_vTimerCallback(xTimerHandle xTimer){USART2_RX_STA |= 0x8000;}
void USART2_IRQHandler(void)
{
	u8 ucTemp;	
	if(USART2->SR&(1<<5))//���յ�����
	{	 
		ucTemp=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{		
			USART2_RX_BUF[USART2_RX_STA&0X7FFF]=ucTemp;
			USART2_RX_STA++;
			xTimerResetFromISR(Usart2RX_Timer_Handle,0);
		}	
	} 
} 
#endif	




#if EN_USART3_RX   //���ʹ���˽���
//����3�жϷ������  	
u8 USART3_RX_BUF[USART_REC_LEN];	//���ջ���,���USART_REC_LEN���ֽ�.
u16 USART3_RX_STA=0;				//����״̬���,bit15:������ɱ�־,bit14~0:���յ�����Ч�ֽ���	  
extern xTimerHandle	Usart3RX_Timer_Handle;
void Usart3RX_vTimerCallback(xTimerHandle xTimer){USART3_RX_STA |= 0x8000;}
void USART3_IRQHandler(void)
{
	u8 ucTemp;	
	if(USART3->SR&(1<<5))//���յ�����
	{	 
		ucTemp=USART3->DR; 
		if((USART3_RX_STA&0x8000)==0)//����δ���
		{		
			USART3_RX_BUF[USART3_RX_STA&0X7FFF]=ucTemp;
			USART3_RX_STA++;
			xTimerResetFromISR(Usart3RX_Timer_Handle,0);
		}	
	} 
} 
#endif	


#include "stdarg.h"
#include "string.h"
u8 uart2_temp_buff[200];
void uart2_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)uart2_temp_buff,fmt,ap);
	va_end(ap);
	i=strlen((const char*)uart2_temp_buff);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while((USART2->SR&0X40)==0);			//�ȴ���һ�δ������ݷ������  
		USART2->DR = (u8) uart2_temp_buff[j];	//дDR,����2����������
	}
}




