#include <main.h>
#include "rcc.h"
#include "gpio.h"

//void EXTI0_IRQHandler();

int main(void)
{
  rcc_HSE_config();
  gpio_config();
  exti_config();

  while(1){

  }
}


