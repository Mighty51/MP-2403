/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "can.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//extern TIM_HandleTypeDef htim3;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/*extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim2;
*/
/*extern ADC_HandleTypeDef hadc1;
extern CAN_HandleTypeDef hcan2;
*/


uint8_t ActivSINC2 = 0x00;
uint16_t ADCResultBuff[6] = {0,};
uint16_t ADCResultBuff2[4] = {0,};
uint8_t index;
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;


uint8_t CanRxBuff[8] = {0,};
uint8_t ADCflag = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Button */
osThreadId_t ButtonHandle;
const osThreadAttr_t Button_attributes = {
  .name = "Button",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Output */
osThreadId_t OutputHandle;
const osThreadAttr_t Output_attributes = {
  .name = "Output",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SwitchMode */
osThreadId_t SwitchModeHandle;
const osThreadAttr_t SwitchMode_attributes = {
  .name = "SwitchMode",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Can */
osThreadId_t CanHandle;
const osThreadAttr_t Can_attributes = {
  .name = "Can",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Adc */
osThreadId_t AdcHandle;
const osThreadAttr_t Adc_attributes = {
  .name = "Adc",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Led */
osThreadId_t LedHandle;
const osThreadAttr_t Led_attributes = {
  .name = "Led",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void ButtonTask(void *argument);
void OutputTask(void *argument);
void SwitchModeTask(void *argument);
void CanTask(void *argument);
void AdcTask(void *argument);
void LedTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Button */
  ButtonHandle = osThreadNew(ButtonTask, NULL, &Button_attributes);

  /* creation of Output */
  OutputHandle = osThreadNew(OutputTask, NULL, &Output_attributes);

  /* creation of SwitchMode */
  SwitchModeHandle = osThreadNew(SwitchModeTask, NULL, &SwitchMode_attributes);

  /* creation of Can */
  CanHandle = osThreadNew(CanTask, NULL, &Can_attributes);

  /* creation of Adc */
  AdcHandle = osThreadNew(AdcTask, NULL, &Adc_attributes);

  /* creation of Led */
  LedHandle = osThreadNew(LedTask, NULL, &Led_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	uint16_t buff[] = {48};

	CHANNEL_A_OFF
	CHANNEL_B_OFF
	//LED_CAN_GREEN_ON
	LED_CAN_RED_ON
	  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, (uint32_t*)buff, 1);//channel 1
	 HAL_TIM_OC_Start_IT(&htim5, TIM_CHANNEL_1);
	osDelay(100);
	DevData.CanError = EnableSw;
	 // HAL_TIM_Base_Start_IT(&htim6);

  /* Infinite loop */
  for(;;)
  {
	  if(DevData.CanError == EnableSw)
	  {
		  LED_CAN_RED_ON
	  }
		  else{
			  LED_CAN_GREEN_ON
			  DevData.CanError = EnableSw;
			  osDelay(5000);
		  }
	  	 osDelay(50);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_ButtonTask */
/**
* @brief Function implementing the Button thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonTask */
void ButtonTask(void *argument)
{
  /* USER CODE BEGIN ButtonTask */
	LED_CAN_GREEN_ON
	DevData.ButtonSwitchOn = DisableSw;
  /* Infinite loop */
  for(;;)
  {
	  if(DevData.ButtonSwitchOn == DisableSw)
	  		{
	  			if(HAL_GPIO_ReadPin(ON_GPIO_Port,ON_Pin)==GPIO_PIN_RESET)
	  			{
	  				osDelay(10);
	  				if(HAL_GPIO_ReadPin(ON_GPIO_Port,ON_Pin)==GPIO_PIN_RESET)
	  				{
	  					DevData.ButtonSwitchOn = EnableSw;
	  				}
	  			}
	  		}
	  		else
	  		{
	  			if(HAL_GPIO_ReadPin(ON_GPIO_Port,ON_Pin)==GPIO_PIN_SET)
	  			{
	  				osDelay(10);
	  				if(HAL_GPIO_ReadPin(ON_GPIO_Port,ON_Pin)==GPIO_PIN_SET)
	  				{
	  					DevData.ButtonSwitchOn = DisableSw;
	  				}
	  			}
	  		}


	      osDelay(1);
  }
  /* USER CODE END ButtonTask */
}

/* USER CODE BEGIN Header_OutputTask */
/**
* @brief Function implementing the Output thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OutputTask */
void OutputTask(void *argument)
{
  /* USER CODE BEGIN OutputTask */
  /* Infinite loop */
  for(;;)
  {
/*
	  if(DevData.ButtonSwitchOn & (DevData.CanEnableLoad == CAN_DISABLE_ALL_CH))
	  {
		  CHANNEL_A_ON
	  	  CHANNEL_B_ON
	  	  LED_OUT_1_GREEN_ON
	  	  LED_OUT_2_GREEN_ON
	 }
	  if((DevData.ButtonSwitchOn = 0) & (DevData.CanEnableLoad == CAN_DISABLE_ALL_CH))
	  {
		 CHANNEL_A_OFF
		 CHANNEL_B_OFF
		 LED_OUT_1_GREEN_OFF
		 LED_OUT_2_GREEN_OFF
	  }
	  if(DevData.CanEnableLoad == CAN_ENABLE_ALL_CH)
	  {
		  CHANNEL_A_ON
		  CHANNEL_B_ON
		  LED_OUT_1_GREEN_ON
		  LED_OUT_2_GREEN_ON
	  }
	  if(DevData.CanEnableLoad == CAN_DISABLE_ALL_CH)
	  {
		  CHANNEL_A_OFF
		  CHANNEL_B_OFF
		  LED_OUT_1_GREEN_OFF
		  LED_OUT_2_GREEN_OFF
	  }
*/
	      osDelay(10);
  }
  /* USER CODE END OutputTask */
}

/* USER CODE BEGIN Header_SwitchModeTask */
/**
* @brief Function implementing the SwitchMode thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SwitchModeTask */
void SwitchModeTask(void *argument)
{
  /* USER CODE BEGIN SwitchModeTask */
	DevData.ModeChannelA = OffChannel;
	DevData.ModeChannelB = OffChannel;
	osDelay(300);
  /* Infinite loop */
  for(;;)
  {
	  ChangeModes(&DevData);

    osDelay(10);
  }
  /* USER CODE END SwitchModeTask */
}

/* USER CODE BEGIN Header_CanTask */
/**
* @brief Function implementing the Can thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CanTask */
void CanTask(void *argument)
{
  /* USER CODE BEGIN CanTask */
	uint8_t TxCanBuff[8];
	//uint16_t TxID = CAN_PROT_TD_TO_PROG;
  /* Infinite loop */
  for(;;)
  {

	  	ConvertDataTOProt(CAN_PROT_TD_TO_PROG, TxCanBuff, &DevData);
	  	CanSendStdMessage(CAN_PROT_TD_TO_PROG, TxCanBuff);
	  	osDelay(800);
  }
  /* USER CODE END CanTask */
}

/* USER CODE BEGIN Header_AdcTask */
/**
* @brief Function implementing the Adc thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AdcTask */
void AdcTask(void *argument)
{
  /* USER CODE BEGIN AdcTask */
	//HAL_ADCEx_MultiModeStart_DMA(&hadc1, ADCResultBuff, 5);
	 //HAL_ADCEx_MultiModeConfigChannel(&hadc1, Mode);
	//HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
	//HAL_ADC_Start(&hadc1);
  /* Infinite loop */
  for(;;)
  {
	  HAL_ADC_Start_DMA(&hadc1, ADCResultBuff, 5);
	  HAL_ADC_Start_DMA(&hadc2, ADCResultBuff2, 4);

	  if(ADCflag)
	  {
		  ADCflag = 0;
		  InterputDataFromAdc(&DevData,ADCResultBuff2);
		  AverDataFromAdc(&DevData);

	  }
	  osDelay(50);
  }

  /* USER CODE END AdcTask */
}

/* USER CODE BEGIN Header_LedTask */
/**
* @brief Function implementing the Led thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LedTask */
void LedTask(void *argument)
{
  /* USER CODE BEGIN LedTask */
  /* Infinite loop */
  for(;;)
  {
	  switch (DevData.ModeChannelA){
	  case OffChannel:
		  LED_OUT_1_ALL_OFF
		  LED_OUT_1_ALL_OFF
		  osDelay(10);
		break;
	  case OnChannel:
		  LED_OUT_1_ALL_OFF
		  LED_OUT_1_GREEN_ON
		  osDelay(10);
	  	break;
	  case OverCurrent:
		  LED_OUT_1_ALL_OFF
	  	  	LED_OUT_1_RED_ON
			osDelay(10);
	  	  	break;
	  case BreakChannel:
		  LED_OUT_1_ALL_OFF
	  	  		LED_OUT_1_YELLOW_ON
				osDelay(10);
	  	  	break;
	  }
	  switch (DevData.ModeChannelB){
		  case OffChannel:
			  LED_OUT_2_ALL_OFF
			  osDelay(10);
			break;
		  case OnChannel:
			  LED_OUT_2_ALL_OFF
			  LED_OUT_2_GREEN_ON
			  osDelay(10);
	  	  	break;
	  	  case OverCurrent:
	  		LED_OUT_2_ALL_OFF
	  		LED_OUT_2_RED_ON
			osDelay(10);
	  	  	  	break;
	  	  case BreakChannel:
	  		LED_OUT_2_ALL_OFF
	  		LED_OUT_2_YELLOW_ON
			osDelay(10);
	  	  	  	break;
	  	  }

    osDelay(10);
  }
  /* USER CODE END LedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
        if(htim->Instance == TIM5)
        {/*
        	if(ActivSINC2)
        	{
        		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
        		HAL_TIM_OC_Stop_IT(&htim5, TIM_CHANNEL_1);
        	}

            ActivSINC2 = 0xFF;
*/
        	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
        	HAL_TIM_OC_Stop_IT(&htim5, TIM_CHANNEL_1);
        }CAN_RxHeaderTypeDef RxHeader;


        uint8_t CanRxBuff[8] = {0,};
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance == ADC1)
	{
		HAL_ADC_Stop_DMA(&hadc1);

	}
	if(hadc->Instance == ADC2)
	{
		HAL_ADC_Stop_DMA(&hadc2);
		ADCflag = 1;


	}
}

/* USER CODE END Application */

