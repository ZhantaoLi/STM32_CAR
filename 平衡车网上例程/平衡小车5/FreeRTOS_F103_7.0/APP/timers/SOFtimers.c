#include "SOFtimers.h"

#if EN_USART1_RX   //如果使能了接收
//串口用软件定时器
xTimerHandle			Usart1RX_Timer_Handle;
extern void Usart1RX_vTimerCallback(xTimerHandle xTimer);
#endif
#if EN_USART2_RX   //如果使能了接收
xTimerHandle			Usart2RX_Timer_Handle;
extern void Usart2RX_vTimerCallback(xTimerHandle xTimer);
#endif
#if EN_USART3_RX   //如果使能了接收
xTimerHandle			Usart3RX_Timer_Handle;
extern void Usart3RX_vTimerCallback(xTimerHandle xTimer);
#endif

void TimersCreate(void)
{

#if EN_USART1_RX   //如果使能了接收
	/* USART1 Timer */
	Usart1RX_Timer_Handle = xTimerCreate ((const char*)"Usart1RX_Timer", 10, pdFALSE, ( void * ) 2, Usart1RX_vTimerCallback );

	if( Usart1RX_Timer_Handle != NULL )
	{
		if( xTimerStart( Usart1RX_Timer_Handle, 0 ) != pdPASS )
		{
			/* The timer could not be set into the Active state. */
			printf("Usart1RX_Timer Create error! \r\n");
			while(1);
		}
	}
#endif
#if EN_USART2_RX   //如果使能了接收
	/* USART2 Timer */
	Usart2RX_Timer_Handle = xTimerCreate ((const char*)"Usart2RX_Timer", 10, pdFALSE, ( void * ) 2, Usart2RX_vTimerCallback );

	if( Usart2RX_Timer_Handle != NULL )
	{
		if( xTimerStart( Usart2RX_Timer_Handle, 0 ) != pdPASS )
		{
			/* The timer could not be set into the Active state. */
			printf("Usart2RX_Timer Create error! \r\n");
			while(1);
		}
	}
#endif
#if EN_USART3_RX   //如果使能了接收
	/* USART3 Timer */
//	Usart3RX_Timer_Handle = xTimerCreate ((const char*)"Usart3RX_Timer", 10, pdFALSE, ( void * ) 2, Usart3RX_vTimerCallback );

//	if( Usart3RX_Timer_Handle != NULL )
//	{
//		if( xTimerStart( Usart3RX_Timer_Handle, 0 ) != pdPASS )
//		{
//			/* The timer could not be set into the Active state. */
//			printf("Usart3RX_Timer Create error! \r\n");
//			while(1);
//		}
//	}
#endif
}






