/*
 * ModeDes.h
 *
 *  Created on: 26 авг. 2022 г.
 *      Author: kto23
 */

#ifndef INC_MODEDES_H_
#define INC_MODEDES_H_

#include "main.h"

#define ITERATION_ADC 100 //максимальное значение на которое может прирасти ADC по току

void GetInfo (struct InsideData *DevData);
void InterputDataFromAdc(struct InsideData *DevData, uint16_t *ADCBuff);
void AverDataFromAdc(struct InsideData *DevData);

void ChangeModes(struct InsideData *DevData);//изменение режимов

#endif /* INC_MODEDES_H_ */
