#include "rcc.h"


static __IO uint32_t msTicks = 0;

void rcc_HSE_config(void){

    /*  HSE = 8 MHZ
     *  AHB prescaler = 1
     *  PLLMUX = 9
     *  --> 72 MHz System Clock
    */
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL); //clear bit PLLMULL
    RCC->CFGR |= (7UL << 18); //0111 << 18  PLLMULL[21:18]

    /* HSE configuration */
    RCC->CR |= (1UL << 16);
    while( (RCC->CR & RCC_CR_HSERDY) == 0);

    /* HSE is PLL source */
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
    RCC->CFGR |= (1UL << 16);

    /* PLL enable and wait */
    RCC->CR |= (1UL << 24);
    while( (RCC->CR & RCC_CR_PLLRDY) == 0);

    //Chọn tốc độ phù hợp hệ thống vì code sẽ nạp vào FLASH
    FLASH->ACR &= ~(FLASH_ACR_LATENCY); //clear
    FLASH->ACR |= (2UL << 0); //set
    //Prefetch buffer enable
    FLASH->ACR |= (1UL << 4); //set

    /* select system clock switch */
    RCC->CFGR &= ~(RCC_CFGR_SW); //clear
    RCC->CFGR |= (2UL << 0); //set
    while( (RCC->CFGR & RCC_CFGR_SWS_PLL) == 0); //wait

    /* Preipherals clock setup */
    //AHB prescaler
    RCC->CFGR &= ~(RCC_CFGR_HPRE); // clear and 0xxx: SYSCLK not divided
    //APB1 prescaler /2
    RCC->CFGR &= ~(RCC_CFGR_PPRE1);
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; //clk = 72 MHz, timer clock = 36 MHz
    //APB2 prescaler /1
    RCC->CFGR &= ~(RCC_CFGR_PPRE2); //72MHz
    //ADC prescaler
    RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // => 12MHZ
}

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
