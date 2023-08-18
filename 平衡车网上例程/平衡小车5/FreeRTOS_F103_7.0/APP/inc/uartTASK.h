#ifndef _UARTTASK_H
#define _UARTTASK_H
#include "FreeRTOS.h"
#include "task.h"






extern TaskHandle_t  uartTask_Handler;
void uartTASK_Create(u8 TASK_PRIO,u16 SIZE);

#endif





