#include "usart3.h"	 

void uart3_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   // ʱ��GPIOB��USART3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
  //USART3_TX   PB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//USART3_RX	  PB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
}

/*
0x00:ɲ��
0x01:ǰ��
0x02:����
0x03:��ת
0x07:��ת
*/
u8 Fore,Back,Left,Right;
void USART3_IRQHandler(void)                	    // ����1�жϷ������
{
  int Bluetooth_data;
  if(USART_GetITStatus(USART3,USART_IT_RXNE)!=0)  // �����жϱ�־λ����
  {
    Bluetooth_data=USART_ReceiveData(USART3);     // ������յ���ָ��
    if(Bluetooth_data==0x00)Fore=0,Back=0,Left=0,Right=0; // ɲ��
    if(Bluetooth_data==0x01)Fore=1,Back=0,Left=0,Right=0; // ǰ��
    if(Bluetooth_data==0x05)Fore=0,Back=1,Left=0,Right=0; // ����
    if(Bluetooth_data==0x03)Fore=0,Back=0,Left=1,Right=0; // ��ת
    if(Bluetooth_data==0x07)Fore=0,Back=0,Left=0,Right=1; // ��ת
    else                    Fore=0,Back=0,Left=0,Right=0;
  }
}
  
