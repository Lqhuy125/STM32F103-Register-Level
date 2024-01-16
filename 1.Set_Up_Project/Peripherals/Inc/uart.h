/*
 * uart.h
 *
 *  Created on: Jan 15, 2024
 *      Author: Quang Huy
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

void uart2_write(char ch);
void uart2_write_string(char *str);
void uart2_write_integer(int value);
void setup();
#endif /* INC_UART_H_ */
