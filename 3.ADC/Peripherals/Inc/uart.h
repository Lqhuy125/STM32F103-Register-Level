///*
// * uart.h
// *
// *  Created on: Jan 11, 2024
// *      Author: Quang Huy
// */
//
//#ifndef INC_UART_H_
//#define INC_UART_H_
//
//#include "main.h"
//
///* UART1 pin configuration*/
//void uart_UART2_GPIO_config();
//
///* USART1 configuration*/
//void uart_UART2_config();
//
//void uart_UART2_putc(char ch);
//
//void uart_UART2_puts(char *str);
//
//
//#endif /* INC_UART_H_ */

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
