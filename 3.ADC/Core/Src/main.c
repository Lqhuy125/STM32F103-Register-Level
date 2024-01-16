//#include "main.h"
//#include "rcc.h"
////#include "gpio.h"
////#include "adc.h"
//#include "uart.h"
//
//void delay(int x){
//  for(int i = 0; i < x; i++){}
//}
//int main(void)
//{
//  rcc_HSE_config();
//  rcc_SysTick_config(72000);
//  uart_UART2_config();
//  uart_UART2_GPIO_config();
//  while(1){
//
//    uart_UART2_putc("b");
//    delay(1000000);
////    rcc_msDelay(1000);
//  }
//}


#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"

bool button_status = false;
int main(void)
{
  rcc_HSE_config();
  rcc_SysTick_config(72000); // T=1ms -> f=1/T=1KHz -> 72 000 000 / 72 000 = 1000
  uart_UART2_config();
  uart_UART2_GPIO_config();
  gpioA_config();
  gpioC_config();

  while(1){
    if(gpioA_ReadPin(0) == 0 && button_status == 0){
      gpioC_WritePin(13, 1);
      button_status = 1;
      uart_UART2_puts("button pressed\n");
      while(gpioA_ReadPin(0) == 0);
      uart_UART2_puts("button unpressed\n");
      rcc_msDelay(20);
    }
    if(gpioA_ReadPin(0) == 0 && button_status == 1){
      gpioC_WritePin(13, 0);
      button_status = 0;
      uart_UART2_puts("button pressed\n");
      while(gpioA_ReadPin(0) == 0);
      uart_UART2_puts("button unpressed\n");
      rcc_msDelay(20);
    }
  }
}
