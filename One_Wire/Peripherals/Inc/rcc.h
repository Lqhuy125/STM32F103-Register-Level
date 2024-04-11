#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

void rcc_HSE_config();

void rcc_TIMER3_config();

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);

#endif /* INC_RCC_H_ */
