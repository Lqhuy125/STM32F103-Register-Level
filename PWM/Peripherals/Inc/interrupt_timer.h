/*
 * interrupt_timer.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Quang Huy
 */

#ifndef INC_INTERRUPT_TIMER_H_
#define INC_INTERRUPT_TIMER_H_

#include "main.h"

void timer3_config();

void delay_ms(uint32_t ms);

void timer3_config_interupt();

#endif /* INC_INTERRUPT_TIMER_H_ */
