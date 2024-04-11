#include <main.h>

uint8_t RxBuffer[8];
uint8_t TxBuffer[8] = "Hello!\n";

uint8_t bat[2] = "bat";
uint8_t tat[3] = "tat";

bool flagRx = false;
int main(void)
{

  rcc_HSE_config();
  rcc_TIMER3_config();
  uart_Init();
  uart_enableRXNEIE(); //Khoi tao ngat

  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPCEN); //clear
  RCC->APB2ENR |= 1UL << 4;   // set 1
  GPIOC->CRH &= ~(3UL << 20); //PC13
  GPIOC->CRH |= (1UL << 21);  // 10: Output mode, max speed 2 MHz.
  GPIOC->CRH &= ~(3UL << 22); //00: General purpose output push-pull
  GPIOC->BSRR |= (1UL << 29); //set status init

	while(1){

	  if(!flagRx)
	  {
	    uart_SendData(&TxBuffer, 8);
	  }
	  else{
	    flagRx = false;
	    uart_SendData(&RxBuffer, 3);
	  }

	  if (strncmp((char*) RxBuffer, tat,strlen(tat) ) == 0)
	  {
      GPIOC->ODR ^= (1UL << 13);
	  }
	      //DoSomething();
	  else if ((strncmp((char*) RxBuffer, bat,strlen(bat) ) == 0))
	  {
	    GPIOC->ODR &= ~(1UL << 13);
	  }
	      //DoSomethingElse();
	  delay_ms(1170);
	}
}

/*Ham xu ly ngat*/
void USART2_IRQHandler(void){
  if(USART2->SR & USART_SR_RXNE)
  {
    flagRx = true;
    uart_ReceiveData(&RxBuffer, 3);
    NVIC_ClearPendingIRQ(USART2_IRQn);
  }

  USART2->SR &= ~USART_SR_RXNE;
}
