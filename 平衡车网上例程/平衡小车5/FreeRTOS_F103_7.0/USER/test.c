#include "sys.h"
#include "Hardware.h"		
#include "FreeRTOS.h"
#include "task.h"
#include "app.h"
#include "SOFtimers.h"


//开始任务句柄
TaskHandle_t StartTask_Handler;
//开始任务函数
void start_task(void *pvParameters);

int main(void)
{				  
	JTAG_Set(1);
	MY_NVIC_PriorityGroupConfig(4);
	Stm32_Clock_Init(9);//系统时钟设置
	Tick_init(72);	  	//延时初始化 
	_HARDWARE_INT();
	
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )64,                   //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,                     //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度	
	
	
	while(1); 
}


//开始任务任务函数
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区
	//创建软件定时器
	TimersCreate();
	//创建消息队列

	//创建任务 
	APP_INT();

	vTaskDelete(StartTask_Handler);   //删除开始任务
	taskEXIT_CRITICAL();              //退出临界区
}


// END 






