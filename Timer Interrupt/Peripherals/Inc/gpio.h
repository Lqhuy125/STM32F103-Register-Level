/*
 * gpio.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Quang Huy
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

void gpio_led_config();

void gpio_button_config();

bool gpio_digitalRead();

#endif /* INC_GPIO_H_ */
