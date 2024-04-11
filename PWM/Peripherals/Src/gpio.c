#include "gpio.h"

void gpio_config_PortC(){

  RCC->APB2ENR |= 1ul << 4;

  GPIOC -> CRH &= ~(0xFul << 22);
  GPIOC->CRH |= 2ul << 20;
}
