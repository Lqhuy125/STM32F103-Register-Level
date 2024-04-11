/*
 * timer3.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Quang Huy
 */


#include "timer3.h"

void timer3_config(){
  RCC->APB1ENR |= 1UL << 1;

  /*
   *  Clock APB1 = 72Mhz
   *  T_mong_muon = 1ms => f = 1000Hz
   * */
  TIM3 -> PSC = 7;

  TIM3 -> ARR = 8999;

  TIM3->CR1 = (1 << 0);
}

/* Sử dụng static để khi gọi đến hàm này chỉ gọi duy nhất lần đầu */
static void delay_ms(uint32_t ms){
  for(volatile uint32_t i=0; i<ms; i++){
     TIM3 -> CNT = 0;
     while((TIM3->SR & (1UL << 0)) == 0);
     TIM3 -> SR &= ~(1UL << 0);
  }
}

void timer3_config_interupt(){
  RCC->APB1ENR |= 1UL << 1;
  TIM3 -> PSC = 7;
  TIM3 -> ARR = 9000;
  //Enable interrupt
  TIM3 -> DIER |= 1UL << 0;
  //clear interrupt flag
  TIM3 -> SR &= ~(1UL << 0);
  //Enable NVIC Interrupt for timer3
  NVIC_EnableIRQ(TIM3_IRQn);
  //enable timer3 module
  TIM3->CR1 = (1 << 0);
}
