/*
 * rcc.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Quang Huy
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

void rcc_HSE_config();
void rcc_SysTick_config(uint32_t arr);
/*
 *  Increment ms Ticks
 */
void rcc_msIncTicks(void);
/*
 *  Get ms Ticks
 */
uint32_t rcc_msGetTicks(void);
/*
 *   ms Delay
 */
void rcc_msDelay(uint32_t  ms);
#endif /* INC_RCC_H_ */
