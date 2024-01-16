#include "rcc.h"

void rcc_HSE_config(){

  /* PLLMUX = 9*/
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL); //clear bit PLLMULL
  RCC->CFGR |= (7UL << 18); //0111 << 18  PLLMULL[21:18]

  //USB prescalar
  RCC->CFGR &= ~(RCC_CFGR_USBPRE); // ~(1UL << 22) clear bit
  RCC->CFGR |= (1UL << 22);

  //HSE config
  RCC->CR |= (1UL << 16);
  while( (RCC->CR & RCC_CR_HSERDY) == 0);

  //HSE is PLL source
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
  RCC->CFGR |= (1UL << 16);

  //PLL enable and wait
  RCC->CR |= (1UL << 24);
  while( (RCC->CR & RCC_CR_PLLRDY) == 0);

  //Chọn tốc độ phù hợp hệ thống
  FLASH->ACR &= ~(FLASH_ACR_LATENCY); //clear
  FLASH->ACR |= (2UL << 0); //set
  //Prefetch buffer enable
  FLASH->ACR |= (1UL << 4); //set

  //select system clock switch
  RCC->CFGR &= ~(RCC_CFGR_SW); //clear
  RCC->CFGR |= (2UL << 0); //set
  while( (RCC->CFGR & RCC_CFGR_SWS_PLL) == 0); //wait

  //Preipherals clock setup
  //AHB prescaler
  RCC->CFGR &= ~(RCC_CFGR_HPRE); // clear and 0xxx: SYSCLK not divided
  //APB1 prescaler /2
  RCC->CFGR &= ~(RCC_CFGR_PPRE1);
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
  //APB2 prescaler /1
  RCC->CFGR &= ~(RCC_CFGR_PPRE2);
  //ADC prescaler
  RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
  RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

}
