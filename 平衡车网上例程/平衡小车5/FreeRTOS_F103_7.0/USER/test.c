#include "sys.h"
#include "Hardware.h"		
#include "FreeRTOS.h"
#include "task.h"
#include "app.h"
#include "SOFtimers.h"


//��ʼ������
TaskHandle_t StartTask_Handler;
//��ʼ������
void start_task(void *pvParameters);

int main(void)
{				  
	JTAG_Set(1);
	MY_NVIC_PriorityGroupConfig(4);
	Stm32_Clock_Init(9);//ϵͳʱ������
	Tick_init(72);	  	//��ʱ��ʼ�� 
	_HARDWARE_INT();
	
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )64,                   //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,                     //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������	
	
	
	while(1); 
}


//��ʼ����������
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ���
	//���������ʱ��
	TimersCreate();
	//������Ϣ����

	//�������� 
	APP_INT();

	vTaskDelete(StartTask_Handler);   //ɾ����ʼ����
	taskEXIT_CRITICAL();              //�˳��ٽ���
}


// END 






