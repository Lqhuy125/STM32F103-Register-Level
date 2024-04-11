#include "rcc.h"

void rcc_HSE_config(){
  //HSE config
  RCC -> CR &= ~(1ul << 16);
  RCC -> CR |= (1ul << 16);
  while( (RCC->CR & (1ul << 17)) == 0);
  //HSE is source
  RCC -> CFGR &= ~(1ul << 16);
  RCC -> CFGR |= (1ul << 16);
  //PLL config
  RCC -> CFGR &= ~(0xful << 18);
  RCC -> CFGR |= (7ul << 18);
  //PLL enable
  RCC->CR &= ~(1ul << 24);
  RCC -> CR |= (1ul << 24);
  while( (RCC->CR & (1ul << 25)) == 0);
  //FLASH
  FLASH -> ACR &= ~(7ul << 0);
  FLASH -> ACR |= (2ul << 0);
  FLASH -> ACR |= (1ul << 4);
  while( (FLASH -> ACR & (1ul << 5)) == 0 );
  //PLL is source SW
  RCC -> CFGR &= ~(3ul << 0);
  RCC -> CFGR |= (2ul << 0);
  while ( (RCC->CFGR & (2ul << 2)) == 0 );
  //AHB
  RCC -> CFGR &= ~(0xful << 4);
  //APB1
  RCC -> CFGR &= ~(0x7ul << 8);
  RCC -> CFGR |= (0x4ul << 8);
  //APB2
  RCC -> CFGR &= ~(0x7ul << 11);

  //config adc prescale
  RCC->CFGR &= ~(3ul << 14);
  RCC->CFGR |= (2ul << 14); //tần số chia 6 => 72/6 = 12MHZ
}
static __IO uint32_t msTicks = 0;

void rcc_SysTick_config(uint32_t arr){
  //Reset Control register
  SysTick->CTRL = 0;
  //Set the Reload value
  SysTick->LOAD = arr;
  //Set priority SysTick interrupt (NVIC)
  NVIC_SetPriority(SysTick_IRQn, 0);
  //Reset Stick value to 0
  SysTick->VAL = 0;
  //Enable SysTick from control register
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // Enable SysTick
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //Enable SysTick Exceptions
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; //Use CPU Clock
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

void SysTick_Handler(void){
  NVIC_ClearPendingIRQ(SysTick_IRQn); // Clear Flag
  rcc_msIncTicks();
}
