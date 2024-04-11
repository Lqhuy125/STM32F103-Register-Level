
#include <main.h>

uint32_t __IO count = 0, count1 = 0;
//void TIM3_IRQHandler(void){
//  /* Check bit UIF in Status Register */
//  if( TIM3->SR & (1UL << 0) ){
//    count++;
//    count1++;
//    if(count < 1000){
//      GPIOC->BSRR |= GPIO_BSRR_BS13;
//    }
//    if(count >=  1000 && count < 2000){
//      GPIOC->BSRR |= GPIO_BSRR_BR13;
//    }
//    if(count >= 2000) count = 0;
//
//    if(count1 < 500){
//      GPIOC->BSRR |= GPIO_BSRR_BS14;
//    }
//    if(count1 >=  500 && count1 < 1000){
//      GPIOC->BSRR |= GPIO_BSRR_BR14;
//    }
//    if(count1 >= 1000) count1 = 0;
//
//    TIM3->SR &= ~(1UL << 0);
//  }
//
//}
static void delay_ms(uint32_t ms){
  for(volatile uint32_t i=0; i<ms; i++){
     TIM3 -> CNT = 0;
     while((TIM3->SR & (1UL << 0)) == 0);
     TIM3 -> SR &= ~(1UL << 0);
  }
}

int main(void)
{
  rcc_HSE_config();
  timer3_config();
//    timer3_config_interupt();
    gpio_led_config();
    gpio_button_config();
  while(1)
  {
//    if(gpio_digitalRead() == true){
//      GPIOA->BSRR |= GPIO_BSRR_BR10;
//    }
//    else {
//      GPIOA->BSRR |= GPIO_BSRR_BS10;
//
//    }

    /* Turn ON the LED of PC13 */
    GPIOC->BSRR |= GPIO_BSRR_BS13;
    delay_ms(1000);
    /* Turn OFF the LED of PC13 */
    GPIOC->BSRR |= GPIO_BSRR_BR13;
    delay_ms(1000);
  }
}
