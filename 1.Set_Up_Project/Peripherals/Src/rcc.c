/*
 * rcc.c
 *
 *  Created on: Jan 4, 2024
 *      Author: Quang Huy
 */

#include "rcc.h"

static __IO uint32_t msTicks = 0;

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

  /* select system clock switch
   * PLLCLK is source
   */
  RCC->CFGR &= ~(RCC_CFGR_SW); //clear
  RCC->CFGR |= (2UL << 0); //set
  while( (RCC->CFGR & RCC_CFGR_SWS_PLL) == 0); //wait

   /* Preipherals clock setup
    *
    *
    */
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

void rcc_SysTick_config(uint32_t arr){
  SysTick->CTRL = 0; //Reset Control register
  SysTick->LOAD = arr; //Set the Reload value
  NVIC_SetPriority(SysTick_IRQn, 0); //Set priority SysTick interrupt (NVIC)
  SysTick->VAL = 0; //Reset Stick value to 0
//  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // Enable SysTick
//  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //Enable SysTick Exceptions
//  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; //Use CPU Clock
  SysTick->CTRL |= (7UL << 0); //Enable SysTick from control register
}

void rcc_msIncTicks(void){
  msTicks++;
}
uint32_t rcc_msGetTicks(void){
  return msTicks;
}
void rcc_msDelay(uint32_t  ms){
  uint32_t startTicks = rcc_msGetTicks();
  while((rcc_msGetTicks() - startTicks) < ms);
}
void rcc_sDelay(uint32_t s){
  rcc_msDelay(s * 1000); // Chuyển đổi milliseconds thành microseconds
}
void SysTick_Handler(void){
  NVIC_ClearPendingIRQ(SysTick_IRQn); // Clear Flag
  rcc_msIncTicks();
}

