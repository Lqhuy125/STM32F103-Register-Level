/*
 * gpio.h
 *
 *  Created on: Jan 11, 2024
 *      Author: Quang Huy
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

typedef enum{
  reset = 0,
  set
} GPIO_PinState;

void gpioC_config();

void gpioC_WritePin(uint16_t pin, GPIO_PinState PinState);

void gpioC_toggle(uint16_t pin);

GPIO_PinState gpioC_ReadPin(uint16_t pin);

void gpioA_config();

void gpioA_WritePin(uint16_t pin, GPIO_PinState PinState);

GPIO_PinState gpioA_ReadPin(uint16_t pin);

#endif /* INC_GPIO_H_ */
