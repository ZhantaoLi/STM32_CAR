#include "uartTASK.h"
#include "usart.h"
#include "stmflash.h"
#include <stdio.h>
#include "led.h"

//381    0.44   206  0.25  
//


float PID_buffer[4] = {280,0.8,90,0.45};
u8 OutFlg = 0;

extern float Get_Temperature(void);
//任务句柄
TaskHandle_t  uartTask_Handler;


extern float balance_UP_KP;
extern float balance_UP_KD;
extern float velocity_KP;
extern float velocity_KI;

void CtrlParametersSAVE(void)
{
	STMFLASH_Write(SAVE_ADDRESS,(void*)PID_buffer,sizeof(PID_buffer)/2);
}
void CtrlParametersREAD(void)
{
	STMFLASH_Read(SAVE_ADDRESS,(void*)PID_buffer,sizeof(PID_buffer)/2);
	balance_UP_KP	= PID_buffer[0];
	balance_UP_KD	= PID_buffer[1];
	velocity_KP		= PID_buffer[2];
	velocity_KI		= PID_buffer[3];
}
void OutCtrlParameters(void)
{
	printf("CtrlParameters= %0.2f,%0.2f,%0.2f,%0.2f\r\n",PID_buffer[0],PID_buffer[1],PID_buffer[2],PID_buffer[3]);
}



void uart_process(void);
static void uart_task(void *pvParameters)
{
	vTaskDelay(11);
#if EN_USART1_RX   //如果使能了接收
	USART1_RX_STA = 0;
#endif
#if EN_USART2_RX  
	USART2_RX_STA = 0;
#endif
#if EN_USART3_RX  
	USART3_RX_STA = 0;
#endif
	vTaskDelay(100);
	
	CtrlParametersREAD();
	OutCtrlParameters();

	while(1)
	{
		uart_process();
		vTaskDelay(10);
	}
}
//
//调用函数创建任务
void uartTASK_Create(u8 TASK_PRIO,u16 SIZE)
{
	xTaskCreate((TaskFunction_t )uart_task,				//任务函数     
				(const char*    )"uart_task",			//任务名   
				(uint16_t       )SIZE,					//任务堆栈大小	     
				(void*          )NULL,                  
				(UBaseType_t    )TASK_PRIO,				//任务优先级      
				(TaskHandle_t*  )&uartTask_Handler);	//任务句柄
}



extern float pitch,roll,yaw;								//欧拉角
extern short gyrox,gyroy,gyroz;								//陀螺仪原始数据
extern int   Encoder_Left,Encoder_Right;					//左右编码器的脉冲计数
extern float Volatage;
void uart_process(void)
{
	static u8 tim = 0;
	
	if(USART1_RX_STA&0x8000)
	{
		if((USART1_RX_BUF[0]=='A')&&(USART1_RX_BUF[1]=='T')&&(USART1_RX_BUF[2]=='+'))
		{
			switch(USART1_RX_BUF[3]-'0')
			{
				case 1:CtrlParametersREAD();break;
				case 2:CtrlParametersSAVE();break;
				case 3:OutCtrlParameters();break;
				case 4:OutFlg = USART1_RX_BUF[4]-'0';break;
				case 5:printf("%s\r\n",USART1_RX_BUF);;break;
				default:break;
			}
			printf("%d is OK!\r\n",USART1_RX_BUF[3]-'0');
		}
			
		USART1_RX_STA = 0;
	}
	
	
	if(USART2_RX_STA&0x8000)
	{
			
		if((USART2_RX_BUF[0]==0xA5)&&(USART2_RX_BUF[1]==0x5A)&&((USART2_RX_STA&0x7fff)==10))
		{
			LED1_Pin = 0;
			PID_buffer[0] = (float)((USART2_RX_BUF[2]<<8) + USART2_RX_BUF[3]);
			PID_buffer[1] = (float)((USART2_RX_BUF[4]<<8) + USART2_RX_BUF[5])/100;
			PID_buffer[2] = (float)((USART2_RX_BUF[6]<<8) + USART2_RX_BUF[7]);
			PID_buffer[3] = (float)((USART2_RX_BUF[8]<<8) + USART2_RX_BUF[9])/100;
			
			balance_UP_KP	= PID_buffer[0];
			balance_UP_KD	= PID_buffer[1];
			velocity_KP		= PID_buffer[2];
			velocity_KI		= PID_buffer[3];
			LED1_Pin = 1;
		}
		else if((USART2_RX_BUF[0]==0x96)&&(USART2_RX_BUF[1]==0x69)&&((USART2_RX_STA&0x7fff)==10))
		{
			LED1_Pin = 0;
			CtrlParametersSAVE();
			LED1_Pin = 1;
		}
		else 
		{
			uart2_printf("err!");
//			for(i=0;i<6;i++)
//			uart2_printf("USART2_RX_BUF[%d]=%x;\r\n",i,USART2_RX_BUF[i]);
//			uart2_printf("Len= %d;\r\n",USART2_RX_STA&0x7fff);
		}
		
		USART2_RX_STA = 0;
	}
		
	//printf(parameter);
	if(tim<50)tim++;
	else
	{
		tim = 0;
		if(OutFlg == 1)		printf("R=%0.2f,",roll),printf("GX=%d,\r\n",gyrox);
		else if(OutFlg == 2)printf("L=%d,	R=%d,\r\n",Encoder_Left,Encoder_Right);
		else if(OutFlg == 3)printf("VOL= %0.2f,\r\n",Volatage);
	}
}








