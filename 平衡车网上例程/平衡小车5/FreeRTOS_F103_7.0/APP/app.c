#include "app.h"

void APP_INT(void)
{
	ledTASK_Create(3,64);
	uartTASK_Create(4,128);
}






