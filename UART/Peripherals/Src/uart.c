#include "uart.h"


#define Perpher_CLK 36000000 //Tần số này sẽ phải dựa vào PCLK1=18MHz
#define Baudrate  9600

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
  return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
  USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}
void uart_Init()
{
  //Enable clock USART2, GPIOA. AFIO
  RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
  RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
  RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;

  /*Confgiure PA2 as output maximum speed to 50MHz
    and alternate output push-pull mode */
  GPIOA->CRL &= ~(0xFUL << 8);
  GPIOA->CRL |= 3<<8;
  GPIOA->CRL |= 2<<10;


  GPIOA->CRL &= ~(0xFUL << 12);
  GPIOA->CRL |= 0x2 << 14;

  /*Don't remap the pins*/
  AFIO->MAPR&=~AFIO_MAPR_USART2_REMAP;

  //Transmit Enable
  USART2->CR1 |= USART_CR1_TE;

  USART2->CR1 |= USART_CR1_RE; //Song công, vừa truyền vừa nhận

  /*Set baudrate */
  uart_set_baudrate(USART2,Perpher_CLK,Baudrate);
  //Enable UART
  USART2->CR1 |= USART_CR1_UE;
}
void uart_SendData(uint8_t *TXBuffer, uint32_t Len){
  uint32_t i;
  for(i=0; i<Len; i++){
    while(!(USART2->SR & USART_SR_TXE));
    USART2->DR = (uint8_t)(*TXBuffer & 0xFF); // & 0xFF đảm bảo dữ liệu là 8 bit
    TXBuffer++;
  }
  while(!(USART2->SR & USART_SR_TC));
}

void uart_ReceiveData(uint8_t *RXBuffer, uint32_t Len){
  uint32_t i;
  for(i=0; i<Len; i++)
  {
    while(!(USART2->SR & USART_SR_RXNE));
    *RXBuffer = (uint8_t)(USART2->DR & 0xFF);
    RXBuffer++;
  }
}

void uart_enableRXNEIE(void)
{
  USART2->CR1 |= USART_CR1_RXNEIE;
  NVIC_EnableIRQ(USART2_IRQn);
}
