

//头文件
#include "stm32f10x.h"
#include "GPIOLIKE51.h"

//函数声明
void GPIO_Configuration(void);

//=============================================================================
//文件名称：Delay
//功能概要：延时
//参数说明：nCount：延时长短
//函数返回：无
//=============================================================================

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


//=============================================================================
//文件名称：main
//功能概要：主函数
//参数说明：无
//函数返回：int
//=============================================================================
int main(void)
{
	  GPIO_Configuration();
    while (1)
	{
		PCout(14)=1;
		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
		PCout(14)=0;
		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);		
    }
}

//=============================================================================
//文件名称：GPIO_Configuration
//功能概要：GPIO初始化
//参数说明：无
//函数返回：无
//=============================================================================
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 
//=============================================================================
//LED -> PC14
//=============================================================================			 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}



