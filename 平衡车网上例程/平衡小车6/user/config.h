

/**************************************************/
#define USART1_BUFF_SIZE 64
#define LED_Shan      GPIOA->ODR^=(1<<8)
#define Read_Touch   (GPIOB->IDR&GPIO_Pin_6)
/**************************************************/
u32 time_cntr1;
u32 time_cntr2;
u32 key_cntr;

u8  key_step;
u8  key_value;

u8  rcv1_cntr;
u8  rcv1_flag;
u8  rcv1_buff[USART1_BUFF_SIZE];
u8  send_buf[USART1_BUFF_SIZE];

float pitch,roll,yaw; 		//ŷ����

/**************************************************/


long speedL_set,speedR_set;     //�ٶ�ʽ�趨Ŀ���ٶ�
long speedL_e1,speedR_e1;       //�ٶ�ʽ�ϴ����
long tim8L_ccr,tim8R_ccr;

