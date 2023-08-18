#include "timer.h"


//定时器2中断服务程序	 
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{
		    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//定时器4中断服务程序	 
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//溢出中断
	{
		    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}
//TIM1_PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能    
	GPIOA->CRH&=0XFFFF0FF0;	//PA8清除之前的设置
	GPIOA->CRH|=0X0000B00B;	//复用功能输出 
	
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器设置
  
	TIM1->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM1->CCMR1|=1<<3; 		//CH1预装载使能	 
 	TIM1->CCER|=1<<0;   	//OC1 输出使能	   
   
	TIM1->CCMR2|=6<<12;  	//CH4 PWM1模式		 
	TIM1->CCMR2|=1<<11; 	//CH4预装载使能	   
	TIM1->CCER|=1<<12;   	//OC4 输出使能
	
	TIM1->BDTR|=1<<15;   	//MOE 主输出使能	
	
	TIM1->CR1=0x0080;   	//ARPE使能 
	TIM1->CR1|=0x01;    	//使能定时器1 										  
} 
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<1; 	//TIM3时钟使能    
	RCC->APB2ENR|=1<<2;    	//使能PORTA时钟
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟	
	GPIOA->CRL&=0X00FFFFFF;	//PA6\7输出
	GPIOA->CRL|=0XBB000000;	//复用功能输出 
	GPIOB->CRL&=0XFFFFFF00;	//PB0\1输出
	GPIOB->CRL|=0X000000BB;	//复用功能输出 	  	 
	   
//	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
//	AFIO->MAPR&=0XFFFFF3FF; //清除MAPR的[11:10]
//	AFIO->MAPR|=2<<10;      //部分重映像,TIM3_CH1->PB4,TIM3_CH2->PB5

	TIM3->ARR=arr;			//设定计数器自动重装值 
	TIM3->PSC=psc;			//预分频器不分频

	TIM3->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM3->CCMR1|=1<<3; 		//CH1预装载使能	   
	TIM3->CCER|=1<<0;   	//OC1 输出使能
	
	TIM3->CCMR1|=6<<12;  	//CH2 PWM1模式		 
	TIM3->CCMR1|=1<<11; 	//CH2预装载使能	   
	TIM3->CCER|=1<<4;   	//OC2 输出使能

	TIM3->CCMR2|=6<<4;  	//CH3 PWM1模式		 
	TIM3->CCMR2|=1<<3; 		//CH3预装载使能	   
	TIM3->CCER|=1<<8;   	//OC3 输出使能
	
	TIM3->CCMR2|=6<<12;  	//CH4 PWM1模式		 
	TIM3->CCMR2|=1<<11; 	//CH4预装载使能	   
	TIM3->CCER|=1<<12;   	//OC4 输出使能
	
	TIM3->BDTR|=1<<15;   	//MOE 主输出使能	
	
	TIM3->CR1=0x0080;   	//ARPE使能 
	TIM3->CR1|=0x01;    	//使能定时器3 											  
}
//通用定时器2中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器2!
void TIM2_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;				//TIM3时钟使能    
 	TIM2->ARR=arr;					//设定计数器自动重装值//刚好1ms    
	TIM2->PSC=psc;					//预分频器7200,得到10Khz的计数时钟		  
	TIM2->DIER|=1<<0;				//允许更新中断	  
	TIM2->CR1|=0x01;				//使能定时器2
  	MY_NVIC_Init(8,0,TIM2_IRQn,4);	//抢占1，子优先级3，组2									 
}
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;				//TIM3时钟使能    
 	TIM3->ARR=arr;					//设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;					//预分频器7200,得到10Khz的计数时钟		  
	TIM3->DIER|=1<<0;				//允许更新中断	  
	TIM3->CR1|=0x01;				//使能定时器3
  	MY_NVIC_Init(8,0,TIM3_IRQn,4);	//抢占1，子优先级3，组2									 
}
//通用定时器4中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器4!
void TIM4_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;				//TIM3时钟使能    
 	TIM4->ARR=arr;					//设定计数器自动重装值//刚好1ms    
	TIM4->PSC=psc;					//预分频器7200,得到10Khz的计数时钟		  
	TIM4->DIER|=1<<0;				//允许更新中断	  
	TIM4->CR1|=0x01;				//使能定时器4
  	MY_NVIC_Init(8,0,TIM4_IRQn,4);	//抢占1，子优先级3，组2									 
}


void TIM2_Coder_Init(void)
{
	RCC->APB1ENR|=1<<0;					//TIM2时钟使能
	RCC->APB2ENR|=1<<2;					//使能PORTA时钟
	RCC->APB2ENR|=1<<0;					//开启辅助时钟，AFIO复用时钟使能

	GPIOA->CRL&=0XFFFFFF00;				//PA0/PA1,作为编码器的AB相输入端
	GPIOA->CRL|=0X00000088;				//浮空输入

	TIM2->DIER|=1<<0;					//允许更新中断				
	TIM2->DIER|=1<<6;					//允许触发中断
	MY_NVIC_Init(7,0,TIM2_IRQn,4);

 	//配置编码器模式
	TIM2->PSC = 0x00;					//预分频器
	TIM2->ARR = (u16)65535;				//设定计数器自动重装值 
	TIM2->CR1 &=~(0<<5);				//选择计数模式:边沿对齐模式
		
	TIM2->CCMR1 |= 1<<0;				//CC1S='01' IC1FP1映射到TI1
	TIM2->CCMR1 |= 1<<8;				//CC2S='01' IC2FP2映射到TI2
	TIM2->CCMR1 |= 3<<4;				//IC1F='1000' 输入捕获1滤波器	 
	TIM2->CCER &= ~(1<<1);				//CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM2->CCER &= ~(1<<5);				//CC2P='0'	 IC2FP2不反相，IC2FP2=TI2

	TIM2->SMCR |= 3<<0;					//编码器模式3，SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM2->CNT = 0;						//计数初值为32767
	TIM2->CR1 |= 0x01;					//CEN=1，使能定时器
}
void TIM3_Coder_Init(void)
{	
	RCC->APB1ENR|=1<<1;					//TIM3时钟使能
	RCC->APB2ENR|=1<<2;					//使能PORTA时钟
	RCC->APB2ENR|=1<<0;					//开启辅助时钟，AFIO复用时钟使能

	GPIOA->CRL&=0X00FFFFFF;				//PA6/PA7,作为编码器的AB相输入端
	GPIOA->CRL|=0X88000000;				//浮空输入

	TIM3->DIER|=1<<0;					//			
	TIM3->DIER|=1<<6;					//允许触发中断
	MY_NVIC_Init(7,0,TIM3_IRQn,4);
	
	//配置编码器模式
	TIM3->PSC = 0x00;					//预分频器
	TIM3->ARR = (u16)65535;				//设定计数器自动重装值 
	TIM3->CR1 &=~(0<<5);				//选择计数模式:边沿对齐模式
		
	TIM3->CCMR1 |= 1<<0;				//CC1S='01' IC1FP1映射到TI1
	TIM3->CCMR1 |= 1<<8;				//CC2S='01' IC2FP2映射到TI2
	TIM3->CCMR1 |= 3<<4;				//IC1F='1000' 输入捕获1滤波器	 
	TIM3->CCER &= ~(1<<1);				//CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);				//CC2P='0'	 IC2FP2不反相，IC2FP2=TI2

	TIM3->SMCR |= 3<<0;					//编码器模式3，SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM3->CNT = 0;						//计数初值为32767
	TIM3->CR1 |= 0x01;    				//CEN=1，使能定时器
}

void TIM4_Coder_Init(void)
{	
	RCC->APB1ENR|=1<<2;					//TIM4时钟使能
	RCC->APB2ENR|=1<<3;					//使能PORTB时钟
	RCC->APB2ENR|=1<<0;					//开启辅助时钟，AFIO复用时钟使能

	GPIOB->CRL&=0X00FFFFFF;				//PB6/PB7,作为编码器的AB相输入端
	GPIOB->CRL|=0X88000000;				//浮空输入

//	TIM4->DIER|=1<<0;					//			
//	TIM4->DIER|=1<<6;					//允许触发中断
//	MY_NVIC_Init(11,0,TIM4_IRQChannel,4);
	
	//配置编码器模式
	TIM4->PSC = 0x00;					//预分频器
	TIM4->ARR = (u16)65535;				//设定计数器自动重装值 
	TIM4->CR1 &=~(0<<5);				//选择计数模式:边沿对齐模式
		
	TIM4->CCMR1 |= 1<<0;				//CC1S='01' IC1FP1映射到TI1
	TIM4->CCMR1 |= 1<<8;				//CC2S='01' IC2FP2映射到TI2
	TIM4->CCMR1 |= 3<<4;				//IC1F='1000' 输入捕获1滤波器	 
	TIM4->CCER &= ~(1<<1);				//CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM4->CCER &= ~(1<<5);				//CC2P='0'	 IC2FP2不反相，IC2FP2=TI2

	TIM4->SMCR |= 3<<0;					//编码器模式3，SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM4->CNT = 0;						//计数初值为32767
	TIM4->CR1 |= 0x01;    				//CEN=1，使能定时器
}


//读编码器
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}




