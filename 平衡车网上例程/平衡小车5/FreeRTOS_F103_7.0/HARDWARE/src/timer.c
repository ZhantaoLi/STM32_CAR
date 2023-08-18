#include "timer.h"


//��ʱ��2�жϷ������	 
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{
		    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{
		    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
//TIM1_PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��    
	GPIOA->CRH&=0XFFFF0FF0;	//PA8���֮ǰ������
	GPIOA->CRH|=0X0000B00B;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM1->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<0;   	//OC1 ���ʹ��	   
   
	TIM1->CCMR2|=6<<12;  	//CH4 PWM1ģʽ		 
	TIM1->CCMR2|=1<<11; 	//CH4Ԥװ��ʹ��	   
	TIM1->CCER|=1<<12;   	//OC4 ���ʹ��
	
	TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	
	
	TIM1->CR1=0x0080;   	//ARPEʹ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 										  
} 
//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<1; 	//TIM3ʱ��ʹ��    
	RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��	
	GPIOA->CRL&=0X00FFFFFF;	//PA6\7���
	GPIOA->CRL|=0XBB000000;	//���ù������ 
	GPIOB->CRL&=0XFFFFFF00;	//PB0\1���
	GPIOB->CRL|=0X000000BB;	//���ù������ 	  	 
	   
//	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
//	AFIO->MAPR&=0XFFFFF3FF; //���MAPR��[11:10]
//	AFIO->MAPR|=2<<10;      //������ӳ��,TIM3_CH1->PB4,TIM3_CH2->PB5

	TIM3->ARR=arr;			//�趨�������Զ���װֵ 
	TIM3->PSC=psc;			//Ԥ��Ƶ������Ƶ

	TIM3->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM3->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	   
	TIM3->CCER|=1<<0;   	//OC1 ���ʹ��
	
	TIM3->CCMR1|=6<<12;  	//CH2 PWM1ģʽ		 
	TIM3->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��	   
	TIM3->CCER|=1<<4;   	//OC2 ���ʹ��

	TIM3->CCMR2|=6<<4;  	//CH3 PWM1ģʽ		 
	TIM3->CCMR2|=1<<3; 		//CH3Ԥװ��ʹ��	   
	TIM3->CCER|=1<<8;   	//OC3 ���ʹ��
	
	TIM3->CCMR2|=6<<12;  	//CH4 PWM1ģʽ		 
	TIM3->CCMR2|=1<<11; 	//CH4Ԥװ��ʹ��	   
	TIM3->CCER|=1<<12;   	//OC4 ���ʹ��
	
	TIM3->BDTR|=1<<15;   	//MOE �����ʹ��	
	
	TIM3->CR1=0x0080;   	//ARPEʹ�� 
	TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��3 											  
}
//ͨ�ö�ʱ��2�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��2!
void TIM2_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;				//TIM3ʱ��ʹ��    
 	TIM2->ARR=arr;					//�趨�������Զ���װֵ//�պ�1ms    
	TIM2->PSC=psc;					//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM2->DIER|=1<<0;				//��������ж�	  
	TIM2->CR1|=0x01;				//ʹ�ܶ�ʱ��2
  	MY_NVIC_Init(8,0,TIM2_IRQn,4);	//��ռ1�������ȼ�3����2									 
}
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;				//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;					//�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;					//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM3->DIER|=1<<0;				//��������ж�	  
	TIM3->CR1|=0x01;				//ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(8,0,TIM3_IRQn,4);	//��ռ1�������ȼ�3����2									 
}
//ͨ�ö�ʱ��4�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��4!
void TIM4_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;				//TIM3ʱ��ʹ��    
 	TIM4->ARR=arr;					//�趨�������Զ���װֵ//�պ�1ms    
	TIM4->PSC=psc;					//Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��		  
	TIM4->DIER|=1<<0;				//��������ж�	  
	TIM4->CR1|=0x01;				//ʹ�ܶ�ʱ��4
  	MY_NVIC_Init(8,0,TIM4_IRQn,4);	//��ռ1�������ȼ�3����2									 
}


void TIM2_Coder_Init(void)
{
	RCC->APB1ENR|=1<<0;					//TIM2ʱ��ʹ��
	RCC->APB2ENR|=1<<2;					//ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<0;					//��������ʱ�ӣ�AFIO����ʱ��ʹ��

	GPIOA->CRL&=0XFFFFFF00;				//PA0/PA1,��Ϊ��������AB�������
	GPIOA->CRL|=0X00000088;				//��������

	TIM2->DIER|=1<<0;					//��������ж�				
	TIM2->DIER|=1<<6;					//�������ж�
	MY_NVIC_Init(7,0,TIM2_IRQn,4);

 	//���ñ�����ģʽ
	TIM2->PSC = 0x00;					//Ԥ��Ƶ��
	TIM2->ARR = (u16)65535;				//�趨�������Զ���װֵ 
	TIM2->CR1 &=~(0<<5);				//ѡ�����ģʽ:���ض���ģʽ
		
	TIM2->CCMR1 |= 1<<0;				//CC1S='01' IC1FP1ӳ�䵽TI1
	TIM2->CCMR1 |= 1<<8;				//CC2S='01' IC2FP2ӳ�䵽TI2
	TIM2->CCMR1 |= 3<<4;				//IC1F='1000' ���벶��1�˲���	 
	TIM2->CCER &= ~(1<<1);				//CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM2->CCER &= ~(1<<5);				//CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2

	TIM2->SMCR |= 3<<0;					//������ģʽ3��SMS='011' ���е�������������غ��½�����Ч
	TIM2->CNT = 0;						//������ֵΪ32767
	TIM2->CR1 |= 0x01;					//CEN=1��ʹ�ܶ�ʱ��
}
void TIM3_Coder_Init(void)
{	
	RCC->APB1ENR|=1<<1;					//TIM3ʱ��ʹ��
	RCC->APB2ENR|=1<<2;					//ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<0;					//��������ʱ�ӣ�AFIO����ʱ��ʹ��

	GPIOA->CRL&=0X00FFFFFF;				//PA6/PA7,��Ϊ��������AB�������
	GPIOA->CRL|=0X88000000;				//��������

	TIM3->DIER|=1<<0;					//			
	TIM3->DIER|=1<<6;					//�������ж�
	MY_NVIC_Init(7,0,TIM3_IRQn,4);
	
	//���ñ�����ģʽ
	TIM3->PSC = 0x00;					//Ԥ��Ƶ��
	TIM3->ARR = (u16)65535;				//�趨�������Զ���װֵ 
	TIM3->CR1 &=~(0<<5);				//ѡ�����ģʽ:���ض���ģʽ
		
	TIM3->CCMR1 |= 1<<0;				//CC1S='01' IC1FP1ӳ�䵽TI1
	TIM3->CCMR1 |= 1<<8;				//CC2S='01' IC2FP2ӳ�䵽TI2
	TIM3->CCMR1 |= 3<<4;				//IC1F='1000' ���벶��1�˲���	 
	TIM3->CCER &= ~(1<<1);				//CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);				//CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2

	TIM3->SMCR |= 3<<0;					//������ģʽ3��SMS='011' ���е�������������غ��½�����Ч
	TIM3->CNT = 0;						//������ֵΪ32767
	TIM3->CR1 |= 0x01;    				//CEN=1��ʹ�ܶ�ʱ��
}

void TIM4_Coder_Init(void)
{	
	RCC->APB1ENR|=1<<2;					//TIM4ʱ��ʹ��
	RCC->APB2ENR|=1<<3;					//ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<0;					//��������ʱ�ӣ�AFIO����ʱ��ʹ��

	GPIOB->CRL&=0X00FFFFFF;				//PB6/PB7,��Ϊ��������AB�������
	GPIOB->CRL|=0X88000000;				//��������

//	TIM4->DIER|=1<<0;					//			
//	TIM4->DIER|=1<<6;					//�������ж�
//	MY_NVIC_Init(11,0,TIM4_IRQChannel,4);
	
	//���ñ�����ģʽ
	TIM4->PSC = 0x00;					//Ԥ��Ƶ��
	TIM4->ARR = (u16)65535;				//�趨�������Զ���װֵ 
	TIM4->CR1 &=~(0<<5);				//ѡ�����ģʽ:���ض���ģʽ
		
	TIM4->CCMR1 |= 1<<0;				//CC1S='01' IC1FP1ӳ�䵽TI1
	TIM4->CCMR1 |= 1<<8;				//CC2S='01' IC2FP2ӳ�䵽TI2
	TIM4->CCMR1 |= 3<<4;				//IC1F='1000' ���벶��1�˲���	 
	TIM4->CCER &= ~(1<<1);				//CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	TIM4->CCER &= ~(1<<5);				//CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2

	TIM4->SMCR |= 3<<0;					//������ģʽ3��SMS='011' ���е�������������غ��½�����Ч
	TIM4->CNT = 0;						//������ֵΪ32767
	TIM4->CR1 |= 0x01;    				//CEN=1��ʹ�ܶ�ʱ��
}


//��������
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




