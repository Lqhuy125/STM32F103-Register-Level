#include "rcc.h"

void rcc_HSE_config(){
  //hse on
  RCC->CR |= (RCC_CR_HSEON);
  while(RCC->CR & (RCC_CR_HSERDY));
  //PLL config
  RCC->CFGR |= RCC_CFGR_PLLSRC; //HSE is source of PLL
  RCC->CFGR |= RCC_CFGR_PLLMULL9; //PLLMUL = 9
  //PLL enable
  RCC->CR |= (RCC_CR_PLLON);
  while(RCC->CR & (RCC_CR_PLLRDY));
  //Flash config
  FLASH->ACR &= ~(FLASH_ACR_LATENCY);
  FLASH->ACR |= FLASH_ACR_LATENCY_2;
  FLASH -> ACR |= FLASH_ACR_PRFTBE;
  while(!(FLASH -> ACR & FLASH_ACR_PRFTBS));
  //pll is sw source
  RCC -> CFGR |= RCC_CFGR_SW_PLL;
  while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));
  /* Preipherals clock setup */
  //AHB prescaler
  RCC->CFGR &= ~(RCC_CFGR_HPRE); // clear and 0xxx: SYSCLK not divided
  //APB1 prescaler /2
  RCC->CFGR &= ~(RCC_CFGR_PPRE1);
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
  //APB2 prescaler /1
  RCC->CFGR &= ~(RCC_CFGR_PPRE2);
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
  //ADC prescaler
  RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
  RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // => 12MHZ
}
