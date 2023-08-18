

#define TIM8_Period  5000   //5000--14.4KHz
/***************************************************************************/
void TIM8_PWM_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef         TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8|RCC_APB2Periph_GPIOC,ENABLE); //ʹ��TIM8ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;   //TIM8���ĸ�PWM���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_DeInit(TIM8);
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_Period=TIM8_Period-1;  //14.4KHz
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);
	TIM_OC2Init(TIM8,&TIM_OCInitStructure);
	TIM_OC3Init(TIM8,&TIM_OCInitStructure);
	TIM_OC4Init(TIM8,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8,ENABLE);
  TIM_Cmd(TIM8,ENABLE);
	//TIM_CCPreloadControl(TIM8,DISABLE);  //ENABLE
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
}
/***************************************************************************/
void TIM2_Encoder_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
	              |RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	//ʹ��TIM2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 
	//TIM2��TIM3������ӳ��
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2|GPIO_PartialRemap_TIM3,ENABLE); 
	//��ֹJTAG���ܣ���PB3��PB4��Ϊ��ͨIO��ʹ��
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure); //GPIO�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);//GPIO�˿�����
	
	TIM_DeInit(TIM2);//TIM2�Ĵ�����λ
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_Period = 0xffff; 
	//��ʼֵ����Ϊ0xffff������ͨ������ֵ�����жϳ����������ת
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//
	//���ñ������ӿڹ���ģʽTIM2Ϊ�������ģʽ���ٶȺͷ������������ؼ���ģʽ
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, 
	                   TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);//����ȽϽṹ�������ʼ��
	TIM_ICInitStructure.TIM_ICFilter =6; //�˲�
	TIM_ICInit(TIM2, &TIM_ICInitStructure);//��ʼ��PWM���벶��ģʽ
	
	//TIM_ClearFlag(TIM2, TIM_FLAG_Update);  
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM2,0);  
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ����ʼ����
}
/***************************************************************************/
void TIM3_Encoder_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //ʹ��TIM3ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;     //TIM3_1/TIM3_2 Remap
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0; // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 0xffff; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//���ñ������ӿڹ���ģʽTIM3Ϊ�������ģʽ���ٶȺͷ��򣩷��������ؼ���ģʽ
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
	                           TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter =6;   //;TIM_ICFilter_Mask  6
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	//TIM_ClearFlag(TIM3, TIM_FLAG_Update);  // Clear all pending interrupts
	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM3,0);  //�ٶ�ģʽ  //TIM3->CNT = 10000;  //λ��ģʽ
	TIM_Cmd(TIM3, ENABLE); 
}
/***************************************************************************/



