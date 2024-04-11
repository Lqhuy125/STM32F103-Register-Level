/*
 * rcc.h
 *
 *  Created on: Jan 11, 2024
 *      Author: Quang Huy
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

void rcc_HSE_config(void);

void rcc_SysTick_config(uint32_t arr);

void rcc_msIncTicks(void);

uint32_t rcc_msGetTicks(void);

void rcc_msDelay(uint32_t ms);

#endif /* INC_RCC_H_ */
