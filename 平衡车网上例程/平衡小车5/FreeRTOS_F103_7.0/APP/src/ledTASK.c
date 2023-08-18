#include "ledTASK.h"
#include "hardware.h"

//������
TaskHandle_t  ledTask_Handler;

LED_MODE LED_GREEN = BREATH;

void BRIGHT_mode(void);
void DARK_mode(void);
void BREATH_mode(void);
void BLINK_mode(void);

//task1������
static void led_task(void *pvParameters)
{
	while(1)
	{
		switch(LED_GREEN)
		{
			case BRIGHT:BRIGHT_mode();	break;
			case DARK:	DARK_mode();	break;
			case BREATH:BREATH_mode();	break;
			case BLINK:	BLINK_mode();	break;		
		}
		
		vTaskDelay(10);
	}
}

	//���ú�����������
void ledTASK_Create(u8 TASK_PRIO,u16 SIZE)
{
	xTaskCreate((TaskFunction_t )led_task,           //������     
				(const char*    )"led_task",         //������   
				(uint16_t       )SIZE,               //�����ջ��С	     
				(void*          )NULL,                  
				(UBaseType_t    )TASK_PRIO,          //�������ȼ�      
				(TaskHandle_t*  )&ledTask_Handler);  //������
}

void BRIGHT_mode(void)
{
	LED(ON);
}
void DARK_mode(void)
{
	LED(OFF);
}
void BREATH_mode(void)
{
	static u8 time;
	if(time<200)time++;
	else	time = 0;
	if((time<10)||((time>20)&&(time<30)))	LED(ON);
	else	LED(OFF);
}
void BLINK_mode(void)
{
	static u8 time;
	if(time<50)time++;
	else	time = 0;
	if(time<10)	LED(ON);
	else		LED(OFF);
}









