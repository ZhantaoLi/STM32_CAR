/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "stdio.h"
#include "motor.h"
#include "niming.h"
#include "pid.h"

#include "cJSON.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern float Motor1Speed ;
extern float Motor2Speed ;
int Motor1Pwm;
int Motor2Pwm;

extern tPid pidMotor1Speed;
extern tPid pidMotor2Speed;
extern uint8_t Usart1_ReadBuf[255];	//串口1 缓冲数组
float p,i,d,a,b;
uint8_t OledString[20];
extern float Mileage;//里程数
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();			//初始化OLED  
  OLED_Clear()  	; 
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//开启定时器1 通道1 PWM输出
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);//开启定时器1 通道4 PWM输出
  HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);//开启定时器2
  HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//开启定时器4
  HAL_TIM_Base_Start_IT(&htim2);				//开启定时器2 中断
  HAL_TIM_Base_Start_IT(&htim4);                //开启定时器4 中断
  
  HAL_TIM_Base_Start_IT(&htim1);                //开启定时器1 中断
  __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);	//开启串口1接收中断
  PID_init();
  cJSON *cJsonData ,*cJsonVlaue;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	OLED_ShowCHinese(0,0,0);//中
//	OLED_ShowCHinese(18,0,1);//景
//	OLED_ShowCHinese(36,0,2);//园
//	OLED_ShowCHinese(54,0,3);//电
//	OLED_ShowCHinese(72,0,4);//子
//	OLED_ShowCHinese(90,0,5);//科
//	OLED_ShowCHinese(108,0,6);//技
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 90);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 90);	
//	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	
	
//	if(Motor1Speed <2.9) Motor1Pwm++;
//	if(Motor1Speed >3.1) Motor1Pwm--;
//	if(Motor2Speed <2.9) Motor2Pwm++;
//	if(Motor2Speed >3.1) Motor2Pwm--;


	
	
//	printf("Motor1Speed:%.2f Motor1Pwm:%d\r\n",Motor1Speed,Motor1Pwm);
//	printf("Motor2Speed:%.2f Motor2Pwm:%d\r\n",Motor2Speed,Motor2Pwm);
//	HAL_Delay(10);
//	motorPidSetSpeed(1,2);//右边运动
//	motorPidSetSpeed(2,1);//左边运动
//	motorPidSetSpeed(1,1);//前运动
//	motorPidSetSpeed(-1,-1);//后运动
//    motorPidSetSpeed(-1,1); //向右原地旋转
//	motorPidSetSpeed(1,-1); //向左原地旋转
//    motorPidSpeedCut();
	
	sprintf((char*)OledString, "V1:%.2fV2:%.2f", Motor1Speed,Motor2Speed);//
	OLED_ShowString(0,0,OledString,12);//这个是oled驱动里面的，是显示位置的一个函数，
	
	sprintf((char*)OledString, "Mileage:%.2f", Mileage);//
	OLED_ShowString(0,1,OledString,12);//这个是oled驱动里面的，是显示位置的一个函数，
	
	sprintf((char*)OledString, "U:%.2fV", adcGetBatteryVoltage());//
	OLED_ShowString(0,2,OledString,12);//这个是oled驱动里面的，是显示位置的一个函数，

	if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 0 )
	{
		printf("应该前进\r\n");
		motorPidSetSpeed(1,1);//前运动
	}
	if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 1&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 0 )
	{
		printf("应该右转\r\n");
		motorPidSetSpeed(0.5,2);//右边运动
	}
	if(READ_HW_OUT_1 == 1&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 0 )
	{
		printf("快速右转\r\n");
		motorPidSetSpeed(0.5,2.5);//快速右转
	}
	if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 1&&READ_HW_OUT_4 == 0 )
	{
		printf("应该左转\r\n");
		motorPidSetSpeed(2,0.5);//左边运动
	}
	if(READ_HW_OUT_1 == 0&&READ_HW_OUT_2 == 0&&READ_HW_OUT_3 == 0&&READ_HW_OUT_4 == 1 )
	{
		printf("快速左转\r\n");
		motorPidSetSpeed(2.5,0.5);//快速左转
	}
	ANO_DT_Send_F2(Motor1Speed*100, 3.0*100,Motor2Speed*100,3.0*100);
	if(Usart_WaitReasFinish() == 0)//是否接收完毕
	{
		cJsonData  = cJSON_Parse((const char *)Usart1_ReadBuf);
		if(cJSON_GetObjectItem(cJsonData,"p") !=NULL)
		{
			cJsonVlaue = cJSON_GetObjectItem(cJsonData,"p");	
		    p = cJsonVlaue->valuedouble;
			pidMotor1Speed.Kp = p;
		}
		if(cJSON_GetObjectItem(cJsonData,"i") !=NULL)
		{
			cJsonVlaue = cJSON_GetObjectItem(cJsonData,"i");	
		    i = cJsonVlaue->valuedouble;
			pidMotor1Speed.Ki = i;
		}
		if(cJSON_GetObjectItem(cJsonData,"d") !=NULL)
		{
			cJsonVlaue = cJSON_GetObjectItem(cJsonData,"d");	
		    d = cJsonVlaue->valuedouble;
			pidMotor1Speed.Kd = d;
		}
		if(cJSON_GetObjectItem(cJsonData,"a") !=NULL)
		{
		
			cJsonVlaue = cJSON_GetObjectItem(cJsonData,"a");	
		    a = cJsonVlaue->valuedouble;
			pidMotor1Speed.target_val =a;
		}
		if(cJSON_GetObjectItem(cJsonData,"b") !=NULL)
		{
		
			cJsonVlaue = cJSON_GetObjectItem(cJsonData,"b");	
		    b = cJsonVlaue->valuedouble;
			pidMotor2Speed.target_val =b;
		}
		if(cJsonData != NULL){
		  cJSON_Delete(cJsonData);//释放空间、但是不能删除cJsonVlaue不然会 出现异常错误
		}
		memset(Usart1_ReadBuf,0,255);//清空接收buf，注意这里不能使用strlen	
	}
	printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n",p,i,d,a);
	
	
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 10);
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 10);
//	HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
	
	
//	uint8_t c_Data[] = "串口输出测试:好家伙VCC\r\n";
//	HAL_UART_Transmit(&huart1,c_Data,sizeof(c_Data),0xFFFF);
//	HAL_Delay(1000);
//	printf("printf:好家伙VCC测试\r\n");
//	HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
//	HAL_Delay(500);
	
	
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
