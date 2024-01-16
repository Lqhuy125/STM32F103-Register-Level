#include "uart.h"

#define Perpher_CLK 36000000
#define Baudrate  115200

void uart_UART2_putc(char ch)
{
  /*Make sure the transmit data register is empty*/
  while(!(USART2->SR & USART_SR_TXE)){}

  /*Write to transmit data register*/
  USART2->DR  =  (ch & 0xFF);
}

void uart_UART2_puts(char *str){
  while(*str != '\0'){
    uart_UART2_putc(*str);
    str++;
  }
}

void uart2_write_integer(int value)
{
    char buffer[12];  // Assuming a 32-bit integer can have at most 11 digits
    int i = 0;

    // Handle negative numbers
    if (value < 0) {
      uart_UART2_putc('-');
        value = -value;
    }

    // Convert digits to characters
    do {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    // Reverse the string
    while (i > 0) {
      uart_UART2_putc(buffer[--i]);
    }
}
void uart_UART2_GPIO_config(){
  /*
   *  A2 - TX2: output
   *  A3 - RX3: input
   */

  //Enable PORT_A clock
  RCC->APB2ENR |= (1UL << 2);
  //ENABLE CLOCK as alternate function
  RCC->APB2ENR |= (1UL << 0);

  /*
   *  @brief Config PA2 as output 50mhz
   *         and alternate output function push - pull
   */
  GPIOA->CRL &= ~(3UL << 8); //CLEAR MODE
  GPIOA->CRL |= (3UL << 8); //SET MODE 11
  GPIOA->CRL &= ~(3UL << 10); //CLEAR CNF
  GPIOA->CRL |= (2UL << 10); //SET CNF OUTPUT AS AF

  /* DONT REMAP PA2 FOR USART2 */
  AFIO->MAPR &= ~(1UL << 3);
}
/* USART1 configuration*/
void uart_UART2_config(){
  //ENABLE USART2 CLOCK
  RCC->APB1ENR |= 1UL << 17;

  //Transmit Enable
  USART2->CR1 |= USART_CR1_TE;

  //SETUP BAUDRATE
  float usart_div = 0;
  uint32_t div_Ma = 0, div_Fra = 0;
  usart_div = Perpher_CLK / (16.0 * Baudrate);
  div_Ma = usart_div;
  div_Fra = (usart_div - div_Ma)*16;
  USART2->BRR = 0;
  USART2->BRR |= (div_Ma << 4);
  USART2->BRR |= (div_Fra << 0);

  //OR CÓ THỂ SET BRR
//  USART2->BRR =  ((Perpher_CLK + (Baudrate/2U))/Baudrate);

  //ENABLE USART2
  USART2->CR1 |= USART_CR1_UE;

}
