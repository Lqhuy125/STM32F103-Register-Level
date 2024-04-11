#include "rcc.h"

void rcc_HSE_config(){
  //HSE config
  RCC->CR &= ~(1UL << 16);
  RCC->CR |= 1UL << 16;
  while( (RCC->CR & (1UL << 17)) == 0);
  //HSE is source
  RCC->CFGR &= ~(1UL << 16);
  RCC->CFGR |= (1UL << 16);
  //PLL config
  RCC->CFGR &= ~(0xFUL << 18);
  RCC->CFGR |= (7UL << 18);
  //PLL enable
  RCC->CR &= ~(1UL << 24);
  RCC->CR |= 1UL << 24;
  while( (RCC->CR & (1UL << 25)) == 0);

  //Select FLASH
  FLASH->ACR &= ~(7UL << 0);
  FLASH->ACR |= (2UL << 0);
  FLASH->ACR |= (1UL << 4);
  while( (FLASH -> ACR & (1ul << 5)) == 0 );
  //PLL is source SW
  RCC->CFGR &= ~(3UL << 0);
  RCC->CFGR |= (2UL << 0);
  while( (RCC->CFGR & (2UL << 2)) == 0 );
  //AHB prescaler
  RCC->CFGR &= ~(0xFUL << 4);
  //APB1 prescaler
  RCC->CFGR &= ~(7UL << 8);
  RCC->CFGR |= (4UL << 8);
  //APB2 prescaler
  RCC->CFGR &= ~(7UL << 11);
}
