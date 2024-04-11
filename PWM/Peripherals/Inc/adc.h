/*
 * adc.h
 *
 *  Created on: Apr 2, 2024
 *      Author: Quang Huy
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

void adc_gpio_config();
void adc_config();
void adc_start();
void adc_stop();
uint16_t adc_readValue();

#endif /* INC_ADC_H_ */
