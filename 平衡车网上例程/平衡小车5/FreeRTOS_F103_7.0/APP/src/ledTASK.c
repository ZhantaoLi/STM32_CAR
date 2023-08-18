#include "ledTASK.h"
#include "hardware.h"

//任务句柄
TaskHandle_t  ledTask_Handler;

LED_MODE LED_GREEN = BREATH;

void BRIGHT_mode(void);
void DARK_mode(void);
void BREATH_mode(void);
void BLINK_mode(void);

//task1任务函数
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

	//调用函数创建任务
void ledTASK_Create(u8 TASK_PRIO,u16 SIZE)
{
	xTaskCreate((TaskFunction_t )led_task,           //任务函数     
				(const char*    )"led_task",         //任务名   
				(uint16_t       )SIZE,               //任务堆栈大小	     
				(void*          )NULL,                  
				(UBaseType_t    )TASK_PRIO,          //任务优先级      
				(TaskHandle_t*  )&ledTask_Handler);  //任务句柄
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









