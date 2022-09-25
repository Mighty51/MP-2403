/*
 * CanProt.h
 *
 *  Created on: 19 авг. 2022 г.
 *      Author: kto23
 */

#ifndef INC_CANPROT_H_
#define INC_CANPROT_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal_def.h"
#include "main.h"
#include "can.h"

#define CAN_PROT_ID 0x1AE
#define CAN_PROT_TD_TO_PROG 0x144

void InterputDataCanProt(uint32_t RxIdHeader, uint8_t *RxDataBuff,struct InsideData *DevData);
void ConvertDataTOProt(uint32_t RxIdHeader, uint8_t *TxDataBuff,struct InsideData *DevData);
void CanSendStdMessage(uint32_t RxIdHeader,uint8_t *TxDataBuff);



#endif /* INC_CANPROT_H_ */
