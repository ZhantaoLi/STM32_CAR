#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

typedef enum{
	ON  = 0,
	OFF = 1,
}LED_STA;



#define AIN1 PBout(1)
#define AIN2 PBout(0)
#define BIN1 PBout(10)
#define BIN2 PBout(11)

//LED端口定义
#define LED1_Pin PAout(15)	
#define LED2_Pin PBout(3)
#define LEDTest	 PCout(13)


#define LED(n) 	LED2_Pin = n

void LED_Init(void);	//初始化		

#endif

















