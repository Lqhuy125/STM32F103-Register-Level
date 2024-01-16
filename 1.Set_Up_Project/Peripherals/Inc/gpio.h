/*
 * gpio.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Quang Huy
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

void gpio_LED_config();

void gpio_digitalWrite(uint8_t pin ,bool state);

void gpio_LED_toggle(uint8_t pin);

void gpio_BUTTON_config();

bool gpio_digitalRead();

bool gpio_digitalRead_PCB0();

#endif /* INC_GPIO_H_ */
