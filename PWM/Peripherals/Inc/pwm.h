/*
 * pwm.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Quang Huy
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "main.h"

void pwm_single_config(uint16_t psc, uint16_t arr);

void pwm_SetDuty(uint16_t duty, uint16_t arr);

#endif /* INC_PWM_H_ */
