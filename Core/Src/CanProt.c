/*
 * CanProt.c
 *
 *  Created on: 19 авг. 2022 г.
 *      Author: kto23
 */

#include "CanProt.h"


void InterputDataCanProt(uint32_t RxIdHeader, uint8_t *RxDataBuff,struct InsideData *DevData)
{
	DevData->CanError = DisableSw;
	switch(RxIdHeader){
	case CAN_PROT_ID:
		DevData->CanEnableLoad = RxDataBuff[7];
		if(RxDataBuff[7]==3){
			DevData->CanSwitchOn = 1;
		}
		else
			DevData->CanSwitchOn = 0;
		break;
	}

}
void ConvertDataTOProt(uint32_t RxIdHeader, uint8_t *RxDataBuff,struct InsideData *DevData)
{
	uint8_t Data;
	switch(RxIdHeader){
		case CAN_PROT_TD_TO_PROG:
			Data = 0x00;
			if(DevData->ModeChannelA == BreakChannel) Data |= (1<<6);
			else Data |= (0<<6);
			if(DevData->ModeChannelB == BreakChannel) Data |= (1<<7);
			else Data = (0<<7);
			if(DevData->ModeChannelA == OverCurrent) Data |= (1<<0);
			else Data |= (0<<0);
			if(DevData->ModeChannelB == OverCurrent) Data |= (1<<1);
			else Data |= (0<<1);
			RxDataBuff[0] = Data;
			Data = 0x00;
			if((DevData->ModeChannelA == OffChannel)||(DevData->ModeChannelA == OnChannel)) Data |= (1<<0);
			else Data |= (0<<0);
			if(DevData->ModeChannelB == OffChannel||(DevData->ModeChannelB == OnChannel)) Data |= (1<<1);
			else Data |= (0<<1);
			if(DevData->VoltageChASred > MIN_OUT_VOLTAGE) Data |= (1<<2);
			else Data |= (0<<2);
			if(DevData->VoltageChBSred > MIN_OUT_VOLTAGE) Data |= (1<<3);
			else Data |= (0<<3);

			RxDataBuff[1] = Data;
			RxDataBuff[2] = 0x00;
			RxDataBuff[3] = 0x00;
			RxDataBuff[4] = 0x00;
			RxDataBuff[5] = 0x00;
			RxDataBuff[6] = 0x65;
			RxDataBuff[7] = 0x00;

			break;
		}
}
void CanSendStdMessage(uint32_t RxIdHeader,uint8_t *TxDataBuff)
{
	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.StdId = RxIdHeader;
	TxHeader.DLC = 8;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;

	if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2))
	{
		if(HAL_CAN_AddTxMessage(&hcan2,&TxHeader,TxDataBuff,0) !=HAL_OK)
		{
		}
	}
}

