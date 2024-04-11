#include "rcc.h"

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
    //RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
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
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
    //APB2 prescaler /1
    RCC->CFGR &= ~(RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;

}
void rcc_TIMER3_config(){
  RCC->APB1ENR |= 1UL << 1;

    /*
     *  Clock APB1 = 36Mhz
     *  T_mong_muon = 1us => f = 1MHz
     * */
    TIM3 -> PSC = 0;

    /*Theo tính toán thì ARR = 71 nhưng do time sai
     * => căn chỉnh xuống 61
     * => 1us tương đương giá trị nạp vào là 1.17 */
    TIM3 -> ARR = 61/2; //Chia 2 vì đã chuyển clock xuống 36MHz

    TIM3->CR1 = (1 << 0);
}

void delay_us(uint32_t us){
  uint32_t i;
  for( i = 0; i <= us; i++ )
  {
    /* Clear the count */
    TIM3->CNT = 0;

    /* Wait UIF to be set */
    while((TIM3->SR & TIM_SR_UIF) == 0);    /* This will generate 1us delay */

    /* Reset UIF */
    TIM3->SR &= ~TIM_SR_UIF;
  }
}

void delay_ms(uint32_t ms){
  uint32_t i;
  for( i = 0; i <= 1000; i++ ){
    delay_us(ms);
  }
}
