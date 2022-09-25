/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CanProt.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CURR_A_Pin GPIO_PIN_2
#define CURR_A_GPIO_Port GPIOC
#define CURR_B_Pin GPIO_PIN_3
#define CURR_B_GPIO_Port GPIOC
#define ON_A_Pin GPIO_PIN_1
#define ON_A_GPIO_Port GPIOA
#define ON_B_Pin GPIO_PIN_2
#define ON_B_GPIO_Port GPIOA
#define ON_Pin GPIO_PIN_4
#define ON_GPIO_Port GPIOA
#define U_A_Pin GPIO_PIN_4
#define U_A_GPIO_Port GPIOC
#define U_B_Pin GPIO_PIN_5
#define U_B_GPIO_Port GPIOC
#define A7_1_Pin GPIO_PIN_7
#define A7_1_GPIO_Port GPIOC
#define A6_1_Pin GPIO_PIN_8
#define A6_1_GPIO_Port GPIOC
#define A5_1_Pin GPIO_PIN_9
#define A5_1_GPIO_Port GPIOC
#define A4_1_Pin GPIO_PIN_8
#define A4_1_GPIO_Port GPIOA
#define A3_1_Pin GPIO_PIN_9
#define A3_1_GPIO_Port GPIOA
#define A2_1_Pin GPIO_PIN_10
#define A2_1_GPIO_Port GPIOA
#define A1_1_Pin GPIO_PIN_11
#define A1_1_GPIO_Port GPIOA
#define A0_1_Pin GPIO_PIN_12
#define A0_1_GPIO_Port GPIOA
#define C1_1_Pin GPIO_PIN_10
#define C1_1_GPIO_Port GPIOC
#define C1_2_Pin GPIO_PIN_11
#define C1_2_GPIO_Port GPIOC
#define C1_3_Pin GPIO_PIN_12
#define C1_3_GPIO_Port GPIOC
#define SINC_B_Pin GPIO_PIN_5
#define SINC_B_GPIO_Port GPIOB
#define SINC_A_Pin GPIO_PIN_6
#define SINC_A_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define LED_OUT_2_GREEN_ON  HAL_GPIO_WritePin(A0_1_GPIO_Port,A0_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A1_1_GPIO_Port,A1_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_2_GREEN_OFF HAL_GPIO_WritePin(A0_1_GPIO_Port,A0_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A1_1_GPIO_Port,A1_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_2_RED_ON HAL_GPIO_WritePin(A1_1_GPIO_Port,A1_1_Pin,GPIO_PIN_SET);(A0_1_GPIO_Port,A0_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_2_RED_OFF HAL_GPIO_WritePin(A1_1_GPIO_Port,A1_1_Pin,GPIO_PIN_RESET);(A0_1_GPIO_Port,A0_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_2_YELLOW_ON HAL_GPIO_WritePin(A1_1_GPIO_Port,A1_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A0_1_GPIO_Port,A0_1_Pin,GPIO_PIN_SET);
#define LED_OUT_2_ALL_OFF HAL_GPIO_WritePin(A1_1_GPIO_Port,A1_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A0_1_GPIO_Port,A0_1_Pin,GPIO_PIN_RESET);

#define LED_OUT_1_GREEN_ON  HAL_GPIO_WritePin(A2_1_GPIO_Port,A2_1_Pin,GPIO_PIN_SET);(A3_1_GPIO_Port,A3_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_1_GREEN_OFF HAL_GPIO_WritePin(A2_1_GPIO_Port,A2_1_Pin,GPIO_PIN_RESET);(A3_1_GPIO_Port,A3_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_1_RED_ON HAL_GPIO_WritePin(A3_1_GPIO_Port,A3_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A2_1_GPIO_Port,A2_1_Pin,GPIO_PIN_RESET);
#define LED_OUT_1_RED_OFF HAL_GPIO_WritePin(A3_1_GPIO_Port,A3_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A2_1_GPIO_Port,A2_1_Pin,GPIO_PIN_RESET)
#define LED_OUT_1_YELLOW_ON HAL_GPIO_WritePin(A2_1_GPIO_Port,A2_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A3_1_GPIO_Port,A3_1_Pin,GPIO_PIN_SET);
#define LED_OUT_1_ALL_OFF HAL_GPIO_WritePin(A2_1_GPIO_Port,A2_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A3_1_GPIO_Port,A3_1_Pin,GPIO_PIN_RESET);

#define LED_CAN_GREEN_ON  HAL_GPIO_WritePin(A4_1_GPIO_Port,A4_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A5_1_GPIO_Port,A5_1_Pin,GPIO_PIN_RESET);
#define LED_CAN_GREEN_OFF HAL_GPIO_WritePin(A4_1_GPIO_Port,A4_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A5_1_GPIO_Port,A5_1_Pin,GPIO_PIN_RESET);
#define LED_CAN_RED_ON HAL_GPIO_WritePin(A5_1_GPIO_Port,A5_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A4_1_GPIO_Port,A4_1_Pin,GPIO_PIN_RESET);
#define LED_CAN_RED_OFF HAL_GPIO_WritePin(A5_1_GPIO_Port,A5_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A4_1_GPIO_Port,A4_1_Pin,GPIO_PIN_RESET);
#define LED_CAN_YELLOW_ON HAL_GPIO_WritePin(A4_1_GPIO_Port,A4_1_Pin,GPIO_PIN_SET);HAL_GPIO_WritePin(A5_1_GPIO_Port,A5_1_Pin,GPIO_PIN_SET);
#define LED_CAN_YELLOW_OFF HAL_GPIO_WritePin(A4_1_GPIO_Port,A4_1_Pin,GPIO_PIN_RESET);HAL_GPIO_WritePin(A5_1_GPIO_Port,A5_1_Pin,GPIO_PIN_RESET);

#define CHANNEL_A_ON HAL_GPIO_WritePin(ON_A_GPIO_Port,ON_A_Pin,GPIO_PIN_RESET);
#define CHANNEL_A_OFF HAL_GPIO_WritePin(ON_A_GPIO_Port,ON_A_Pin,GPIO_PIN_SET);

#define CHANNEL_B_ON HAL_GPIO_WritePin(ON_B_GPIO_Port,ON_B_Pin,GPIO_PIN_RESET);
#define CHANNEL_B_OFF HAL_GPIO_WritePin(ON_B_GPIO_Port,ON_B_Pin,GPIO_PIN_SET);

#define CAN_ENABLE_ALL_CH 0x03
#define CAN_DISABLE_ALL_CH 0x00

#define MIN_OUT_CURRENT 500 // ток нагрузки при котором светодиод горит зеленым, мА
#define MIN_OUT_VOLTAGE 10000// напряжение нагрузки на выходе при котором устройство понимает что на выходе есть напряжение, мВ
#define MAX_OUT_CURRENT 5000//ток перегрузки

#define MIN_ADC_CUR_VAL 720 //значение на АЦП при котором ток выхода равен нулю

typedef enum{
	DisableSw = 0,
	EnableSw
} Switch;
typedef enum{
	OffChannel = 0,
	OnChannel,
	OverCurrent,
	PreOverCurrent,
	BreakChannel
} ModeCh;

struct InsideData{

	uint8_t RxHeaderID; //ID приянятого  кадра

	uint8_t CanEnableLoad; //Команда на включение каналов

	uint8_t CodMesta; //побитово 1 - M0, 2 - M1, 4 - M2
	/*-----------------
	 * 0 - группа фар 1 0x05
	 * 4 - омыватель 0x06
	 * 2 - Группа фар 2 0x07
	 *
	 * --------------------*/

	uint8_t Mode;
	ModeCh ModeChannelA,ModeChannelB;


	Switch ObrChannelA:1;
	Switch ObrChannelB:1;
	Switch KzChannelA:1;
	Switch KzChannelB:1;
	Switch CanError:1;

	uint32_t ADCCurrentChA,ADCCurrentChB,ADCTempCore,ADCVoltageChA,ADCVoltageChB;

	Switch ButtonSwitchOn:1;//команда на включение подана с помощью тумблера
	Switch CanSwitchOn:1;//команда на включение подана с помощью CAN
	Switch ButtonSwitchOnOldVal:1;//команда на включение подана с помощью тумблера предидущее значение
	Switch CanSwitchOnOldVal:1;//команда на включение подана с помощью CAN предидущее значение

	uint32_t CurrentChAOld;
	uint32_t CurrentChA;//текущее значение тока
	uint16_t CurrentChABuff[10];//буфер последних 10ти значений
	uint16_t CurrentChASred;// среднее значение тока на канале
	uint32_t CurrentChBOld;
	uint32_t CurrentChB;//текущее значение тока
	uint16_t CurrentChBBuff[10];//буфер последних 10ти значений
	uint16_t CurrentChBSred;// среднее значение тока на канале

	uint32_t VoltageChA;
	uint16_t VoltageChABuff[10];
	uint32_t VoltageChASred;

	uint32_t VoltageChB;
	uint16_t VoltageChBBuff[10];
	uint32_t VoltageChBSred;

};

struct InsideData DevData;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
