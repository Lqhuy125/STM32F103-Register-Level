/*
 * uart.c
 *
 *  Created on: Jan 15, 2024
 *      Author: Quang Huy
 */


#include "uart.h"

#define Perpher_CLK 36000000
#define Baudrate  115200



static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
  return ((PeriphClk + (BaudRate/2U))/BaudRate);
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
  USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

void uart2_write(char ch)
{
  /*Make sure the transmit data register is empty*/
  while(!(USART2->SR & USART_SR_TXE)){}

  /*Write to transmit data register*/
  USART2->DR  =  (ch & 0xFF);
}

void uart2_write_string(char *str){
  while(*str != '\0'){
    uart2_write(*str);
    str++;
  }
}

void uart2_write_integer(int value)
{
    char buffer[12];  // Assuming a 32-bit integer can have at most 11 digits
    int i = 0;

    // Handle negative numbers
    if (value < 0) {
        uart2_write('-');
        value = -value;
    }

    // Convert digits to characters
    do {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    // Reverse the string
    while (i > 0) {
        uart2_write(buffer[--i]);
    }
}
void setup(){
  //enable clock access to GPIOA
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
    //Enable clock access to alternate function
    RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;

    /*Confgiure PA2 as output maximum speed to 50MHz
     * and alternate output push-pull mode*/
    GPIOA->CRL|=GPIO_CRL_MODE2;

    GPIOA->CRL|=GPIO_CRL_CNF2_1;
    GPIOA->CRL&=~GPIO_CRL_CNF2_0;


    /*Don't remap the pins*/
    AFIO->MAPR&=~AFIO_MAPR_USART2_REMAP;


    /*USART2 configuration*/

    //enable clock access to USART2

    RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
  //  RCC->CFGR |= RCC_CFGR_PPRE1_DIV16;  // Assuming APB1 prescaler is 16

    //Transmit Enable
    USART2->CR1 |= USART_CR1_TE;

    /*Set baudrate */
    uart_set_baudrate(USART2,Perpher_CLK,Baudrate);
    //Enable UART
    USART2->CR1 |= USART_CR1_UE;
}
