#include "usart3.h"	 

void uart3_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   // 时钟GPIOB，USART3
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
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART3, ENABLE);                    //使能串口 
}

/*
0x00:刹车
0x01:前进
0x02:后退
0x03:左转
0x07:右转
*/
u8 Fore,Back,Left,Right;
void USART3_IRQHandler(void)                	    // 串口1中断服务程序
{
  int Bluetooth_data;
  if(USART_GetITStatus(USART3,USART_IT_RXNE)!=0)  // 接收中断标志位拉高
  {
    Bluetooth_data=USART_ReceiveData(USART3);     // 保存接收到的指令
    if(Bluetooth_data==0x00)Fore=0,Back=0,Left=0,Right=0; // 刹车
    else if(Bluetooth_data==0x01)Fore=1,Back=0,Left=0,Right=0; // 前进
    else if(Bluetooth_data==0x05)Fore=0,Back=1,Left=0,Right=0; // 后退
    else if(Bluetooth_data==0x03)Fore=0,Back=0,Left=1,Right=0; // 左转
    else if(Bluetooth_data==0x07)Fore=0,Back=0,Left=0,Right=1; // 右转
    else                    Fore=0,Back=0,Left=0,Right=0;
  }
}

// 发送一个
void USART3_Send_Data(char data)
{
  USART_SendData(USART3,data);
  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==0);  // 除非发送完成  
}

// 发送一串
void USART3_Send_String(char *String)
{
  u16 len,j;
  len=strlen(String);
  for(j=0;j<len;j++)
  {
    USART3_Send_Data(*String++);
  }
}

