#include "usart.h"	  
#include "FreeRTOS.h"  
#include "timers.h"
  
//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率 
void uart1_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置 
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.
#if EN_USART1_RX		  //如果使能了接收
	//使能接收中断 
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(14,0,USART1_IRQn,4);//组2，最低优先级 
#endif
}
//初始化IO 串口2
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率 
void uart2_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	
	RCC->APB1ENR|=1<<17;  //使能串口时钟 
	GPIOA->CRL&=0XFFFF00FF;//IO状态设置
	GPIOA->CRL|=0X00008B00;//IO状态设置 
	
	RCC->APB1RSTR|=1<<17;   //复位串口1
	RCC->APB1RSTR&=~(1<<17);//停止复位	   	   
	//波特率设置
 	USART2->BRR=mantissa; // 波特率设置	 
	USART2->CR1|=0X200C;  //1位停止,无校验位.
#if EN_USART2_RX		  //如果使能了接收
	//使能接收中断 
	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(14,0,USART2_IRQn,4);//组2，最低优先级 
#endif
}

//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率 
void uart3_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  //使能串口时钟 
	GPIOB->CRH&=0XFFFF00FF;//IO状态设置
	GPIOB->CRH|=0X00008B00;//IO状态设置 
	RCC->APB1RSTR|=1<<18;   //复位串口1
	RCC->APB1RSTR&=~(1<<18);//停止复位	   	   
	//波特率设置
 	USART3->BRR=mantissa; // 波特率设置	 
	USART3->CR1|=0X200C;  //1位停止,无校验位.
#if EN_USART3_RX		  //如果使能了接收
	//使能接收中断 
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(14,0,USART3_IRQn,4);//组2，最低优先级 
#endif
}



//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定向fputc函数
//printf的输出，指向fputc，由fputc输出到串口
//这里使用串口1(USART1)输出printf信息
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART1->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////



#if EN_USART1_RX  //如果使能了接收
//串口1中断服务程序 	
u8 USART1_RX_BUF[USART_REC_LEN];	//接收缓冲,最大USART_REC_LEN个字节.
u16 USART1_RX_STA=0;				//接收状态标记,bit15:接收完成标志,bit14~0:接收到的有效字节数	  
extern xTimerHandle	Usart1RX_Timer_Handle;
void Usart1RX_vTimerCallback(xTimerHandle xTimer){USART1_RX_STA |= 0x8000;} 
void USART1_IRQHandler(void)
{
	u8 ucTemp;	
	if(USART1->SR&(1<<5))//接收到数据
	{	 
		ucTemp=USART1->DR; 
		if((USART1_RX_STA&0x8000)==0)//接收未完成
		{		
			USART1_RX_BUF[USART1_RX_STA&0X7FFF]=ucTemp;
			USART1_RX_STA++;
			xTimerResetFromISR(Usart1RX_Timer_Handle,0);
		}	
	} 
} 
#endif	



#if EN_USART2_RX	//如果使能了接收
//串口2中断服务程序 	
u8 USART2_RX_BUF[USART_REC_LEN];	//接收缓冲,最大USART_REC_LEN个字节.
u16 USART2_RX_STA=0;				//接收状态标记,bit15:接收完成标志,bit14~0:接收到的有效字节数
extern xTimerHandle	Usart2RX_Timer_Handle;
void Usart2RX_vTimerCallback(xTimerHandle xTimer){USART2_RX_STA |= 0x8000;}
void USART2_IRQHandler(void)
{
	u8 ucTemp;	
	if(USART2->SR&(1<<5))//接收到数据
	{	 
		ucTemp=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{		
			USART2_RX_BUF[USART2_RX_STA&0X7FFF]=ucTemp;
			USART2_RX_STA++;
			xTimerResetFromISR(Usart2RX_Timer_Handle,0);
		}	
	} 
} 
#endif	




#if EN_USART3_RX   //如果使能了接收
//串口3中断服务程序  	
u8 USART3_RX_BUF[USART_REC_LEN];	//接收缓冲,最大USART_REC_LEN个字节.
u16 USART3_RX_STA=0;				//接收状态标记,bit15:接收完成标志,bit14~0:接收到的有效字节数	  
extern xTimerHandle	Usart3RX_Timer_Handle;
void Usart3RX_vTimerCallback(xTimerHandle xTimer){USART3_RX_STA |= 0x8000;}
void USART3_IRQHandler(void)
{
	u8 ucTemp;	
	if(USART3->SR&(1<<5))//接收到数据
	{	 
		ucTemp=USART3->DR; 
		if((USART3_RX_STA&0x8000)==0)//接收未完成
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
	i=strlen((const char*)uart2_temp_buff);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
		while((USART2->SR&0X40)==0);			//等待上一次串口数据发送完成  
		USART2->DR = (u8) uart2_temp_buff[j];	//写DR,串口2将发送数据
	}
}




