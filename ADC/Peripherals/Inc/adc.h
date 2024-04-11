/*
 * adc.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Quang Huy
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

void adc_GPIO_config();
void adc_single_config(uint8_t channel);
void adc_Start();
void adc_Stop();
uint16_t adc_readValue();

#endif /* INC_ADC_H_ */
