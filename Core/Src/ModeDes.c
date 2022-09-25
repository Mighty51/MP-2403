/*
 * ModeDes.c
 *
 *  Created on: 26 авг. 2022 г.
 *      Author: kto23
 */

#include "ModeDes.h"

void GetInfo (struct InsideData *DevData){

	//считывание кода места
	if(HAL_GPIO_ReadPin(C1_1_GPIO_Port, C1_1_Pin)==GPIO_PIN_SET){
		DevData->CodMesta |= 0x01;
	}
	if(HAL_GPIO_ReadPin(C1_2_GPIO_Port, C1_2_Pin)==GPIO_PIN_SET){
		DevData->CodMesta |= 0x02;
	}
	if(HAL_GPIO_ReadPin(C1_3_GPIO_Port, C1_3_Pin)==GPIO_PIN_SET){
		DevData->CodMesta |= 0x04;
	}
}

void InterputDataFromAdc(struct InsideData *DevData, uint16_t *ADCBuff)
{
	if(ADCBuff[0] < MIN_ADC_CUR_VAL) ADCBuff[0] = MIN_ADC_CUR_VAL;
	if(ADCBuff[1] < MIN_ADC_CUR_VAL) ADCBuff[1] = MIN_ADC_CUR_VAL;

	DevData->ADCCurrentChA = ADCBuff[0]-MIN_ADC_CUR_VAL;
	DevData->ADCCurrentChB = ADCBuff[1]-MIN_ADC_CUR_VAL;

	//DevData->CurrentChA =  (DevData->ADCCurrentChA*1000) / 31;
	//DevData->CurrentChB =  (DevData->ADCCurrentChB*1000)/31;

	DevData->CurrentChA =  (abs(ADCBuff[0]-MIN_ADC_CUR_VAL)*1000)/31;
	DevData->CurrentChB =  (abs(ADCBuff[1]-MIN_ADC_CUR_VAL)*1000)/31;

	DevData->VoltageChA = (ADCBuff[2] * 1000)/104;
	DevData->VoltageChB = (ADCBuff[3] * 1000)/104;
	/*if(DevData->CurrentChA > 4000)
	{
		osDelay(1);
	}*/
}

void AverDataFromAdc(struct InsideData *DevData)
{
	 for(int i = 10; i >= 1; i--)
			  {
				  //
				  DevData->CurrentChABuff[i] = DevData->CurrentChABuff[i-1];
				  DevData->CurrentChBBuff[i] = DevData->CurrentChBBuff[i-1];
				  //
				  DevData->VoltageChABuff[i] = DevData->VoltageChABuff[i-1];
				  DevData->VoltageChBBuff[i] = DevData->VoltageChBBuff[i-1];
			  }
	 	 	 if(DevData->CurrentChAOld)
	 		 {
	 			if((DevData->CurrentChA - DevData->CurrentChAOld) < ITERATION_ADC)
	 			{
	 				DevData->CurrentChABuff[0] = DevData->CurrentChA;
	 			}
	 			DevData->CurrentChAOld = 0;
	 		 }
	 	 	if(DevData->CurrentChBOld)
	 	 	{
	 	 		if((DevData->CurrentChB - DevData->CurrentChBOld) < ITERATION_ADC)
	 	 		{
	 	 		 	DevData->CurrentChBBuff[0] = DevData->CurrentChB;
	 	 		}
	 	 		DevData->CurrentChBOld = 0;
	 	 	}
	 	 	 if(abs( DevData->CurrentChA - DevData->CurrentChABuff[1]) < ITERATION_ADC)
	 	 	 {
	 	 		DevData->CurrentChABuff[0] = DevData->CurrentChA;
	 	 		osDelay(20);
	 	 	 }
	 	 	 else
	 	 	 {
	 	 		DevData->CurrentChAOld = DevData->CurrentChA;
	 	 		osDelay(20);
	 	 	 }
	 	 	if(abs( DevData->CurrentChB - DevData->CurrentChBBuff[1]) < ITERATION_ADC)
	 	 	{
	 	 		DevData->CurrentChBBuff[0] = DevData->CurrentChB;
	 	 		osDelay(20);
	 	 	}
	 	 	else
	 	 	{
	 	 		DevData->CurrentChBOld = DevData->CurrentChB;
	 	 		osDelay(20);
	 	 	}


			  DevData->VoltageChABuff[0] = DevData->VoltageChA;
			  DevData->VoltageChBBuff[0] = DevData->VoltageChB;

			  DevData->CurrentChASred = 0;
			  DevData->CurrentChBSred = 0;

			  DevData->VoltageChASred = 0;
			  DevData->VoltageChBSred = 0;

			  for(int i = 0; i<10; i++)
			  {
				  DevData->CurrentChASred += DevData->CurrentChABuff[i];
				  DevData->CurrentChBSred += DevData->CurrentChBBuff[i];

				  DevData->VoltageChASred += DevData->VoltageChABuff[i];
				  DevData->VoltageChBSred += DevData->VoltageChBBuff[i];
			  }
			  	  DevData->CurrentChASred /=10;
			  	  DevData->CurrentChBSred /=10;

			  	  DevData->VoltageChASred /= 10;
			  	  DevData->VoltageChBSred /= 10;

}

void ChangeModes(struct InsideData *DevData)
{
	if((DevData->ButtonSwitchOn!=DevData->ButtonSwitchOnOldVal)||(DevData->CanSwitchOn!=DevData->CanSwitchOnOldVal))
	{
		DevData->ButtonSwitchOnOldVal = DevData->ButtonSwitchOn;
		DevData->CanSwitchOnOldVal = DevData->CanSwitchOn;
		if((DevData->ButtonSwitchOn == EnableSw)||(DevData->CanSwitchOn == EnableSw))
			{
				DevData->ModeChannelA = OnChannel;
				DevData->ModeChannelB = OnChannel;
				CHANNEL_A_ON
				CHANNEL_B_ON
				osDelay(200);
			}
			else
			{
				//DevData->ModeChannelA = OffChannel;
				//DevData->ModeChannelB = OffChannel;
				CHANNEL_A_OFF
				CHANNEL_B_OFF
				osDelay(10);
			}
	}
	if((DevData->ButtonSwitchOn == EnableSw) || (DevData->CanSwitchOn == EnableSw))
	{
		if((DevData->CurrentChASred > MIN_OUT_CURRENT)&&(DevData->VoltageChA > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelA != OverCurrent))
		{
		  DevData->ModeChannelA = OnChannel;
		}
		else if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelA != OverCurrent))
		{
			DevData->ModeChannelA = BreakChannel;
		}
		else if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA < MIN_OUT_VOLTAGE))
		{
			osDelay(10);
			if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA < MIN_OUT_VOLTAGE))
			{
				DevData->ModeChannelA = OverCurrent;
				CHANNEL_A_OFF
			}

		}

		if((DevData->CurrentChBSred > MIN_OUT_CURRENT)&&(DevData->VoltageChB > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelB != OverCurrent))
				{
				  DevData->ModeChannelB = OnChannel;
				}
				else if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelB != OverCurrent))
				{
					DevData->ModeChannelB = BreakChannel;
				}
				else if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB < MIN_OUT_VOLTAGE))
				{
					osDelay(10);
					 if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB < MIN_OUT_VOLTAGE))
					{
						 DevData->ModeChannelB = OverCurrent;
						 CHANNEL_B_OFF
					}

				}

	}
	else
	{
		if(DevData->ModeChannelA != OverCurrent)
				{
					if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA < MIN_OUT_VOLTAGE))
						DevData->ModeChannelA = OffChannel;
				}
				if(DevData->ModeChannelB != OverCurrent)
				{
					if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB < MIN_OUT_VOLTAGE))
						DevData->ModeChannelB = OffChannel;
				}

	}



	/*
	if((DevData->CurrentChASred > MIN_OUT_CURRENT)&&(DevData->VoltageChA > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelA != OverCurrent))
		 	  {
		 		  DevData->ModeChannelA = OnChannel;
		 	  }
		 	  else if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelA != OverCurrent))
		 	  {
		 		 if((DevData->ButtonSwitchOn == DisableSw) && (DevData->CanSwitchOn == DisableSw))
		 		  DevData->ModeChannelA = BreakChannel;
		 	  }
		 	  else if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA < MIN_OUT_VOLTAGE)&&(DevData->ModeChannelA != OverCurrent))
		 	  {
		 		 if((DevData->ButtonSwitchOn == DisableSw) && (DevData->CanSwitchOn == DisableSw))
		 		  DevData->ModeChannelA = OffChannel;
		 	  }
		 	  if((DevData->CurrentChASred < MIN_OUT_CURRENT)&&(DevData->VoltageChA < MIN_OUT_VOLTAGE))
				{
		 		  if((DevData->ButtonSwitchOn == EnableSw) || (DevData->CanSwitchOn == EnableSw))
					DevData->ModeChannelA = OverCurrent;
				}

		 	  //второй канал B
		 	  if((DevData->CurrentChBSred > MIN_OUT_CURRENT)&&(DevData->VoltageChB > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelB != OverCurrent))
		 	  {
		 		  DevData->ModeChannelB = OnChannel;
		 	  }
		 	  else if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB > MIN_OUT_VOLTAGE)&&(DevData->ModeChannelB != OverCurrent))
		 	  {
		 		 if((DevData->ButtonSwitchOn == DisableSw) && (DevData->CanSwitchOn == DisableSw))
		 		  DevData->ModeChannelB = BreakChannel;
		 	  }
		 	  else if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB < MIN_OUT_VOLTAGE)&&(DevData->ModeChannelB != OverCurrent))
		 	  {
		 		 if((DevData->ButtonSwitchOn == DisableSw) && (DevData->CanSwitchOn == DisableSw))
		 		  DevData->ModeChannelB = OffChannel;
		 	  }
		 	  if((DevData->CurrentChBSred < MIN_OUT_CURRENT)&&(DevData->VoltageChB < MIN_OUT_VOLTAGE))
		 	  {
		 		 if((DevData->ButtonSwitchOn == EnableSw) || (DevData->CanSwitchOn == EnableSw))
		 		  DevData->ModeChannelB = OverCurrent;
		 	  }
		 	  */
}

