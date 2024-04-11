/*
 * rcc.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Quang Huy
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

void rcc_HSE_config(void);

void rcc_TIMER3_config();

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);
#endif /* INC_RCC_H_ */

