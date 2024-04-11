/*
 * uart.h
 *
 *  Created on: Apr 10, 2024
 *      Author: Quang Huy
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

#define UART_MODE_MASTER      (1<<3) //TE bit
#define UART_MODE_SLAVE       (1<<2) //TE bit

void uart_Init();

void uart_SendData(uint8_t *TXBuffer, uint32_t Len);

void uart_ReceiveData(uint8_t *RXBuffer, uint32_t Len);

void uart_enableRXNEIE(void);

#endif /* INC_UART_H_ */
