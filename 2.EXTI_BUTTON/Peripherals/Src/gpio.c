/*
 * gpio.c
 *
 *  Created on: Jan 6, 2024
 *      Author: Quang Huy
 */

#include "gpio.h"

void gpio_config(){
  /* GPIOC 13 OUTPUT */
  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPCEN); //clear
  RCC->APB2ENR |= 1UL << 4;   // set 1
  GPIOC->CRH &= ~(3UL << 20); //PC13
  GPIOC->CRH |= (1UL << 21);  // 10: Output mode, max speed 2 MHz.
  GPIOC->CRH &= ~(3UL << 22); //00: General purpose output push-pull
  GPIOC->BSRR |= (1UL << 29); //set status init

  /* GPIOA 0 INPUT */
  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN);
  RCC->APB2ENR |= 1UL << 2;
  GPIOA->CRL &= ~(3UL << 0);    //PA0 00 INPUT
  GPIOA->CRL &= ~(3UL << 2);    // clear
  GPIOA->CRL |= (1UL << 2);
  GPIOA->ODR |= GPIO_IDR_IDR0;  //PA0 INPUT
}
void exti_config(){
  /* AFIO FOR EXTI LINE 0 IN PA0*/
  RCC->APB2ENR &= ~(RCC_APB2ENR_AFIOEN);
  RCC->APB2ENR |= (1UL << 0);
  AFIO->EXTICR[0] &=~ (0xFUL << 0);
  EXTI->IMR |= (1UL << 0);
  EXTI->RTSR &=~ (1UL << 0);
  EXTI->FTSR |= (1UL << 0);

  NVIC_SetPriority(EXTI0_IRQn, 5);
  NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(){

  NVIC_ClearPendingIRQ(EXTI0_IRQn);
  EXTI->PR |= (1UL << 0); //CLEAR AFTER USE
//  EXTI->IMR &=~ (1UL << 0);
  GPIOC->ODR ^= (1UL << 13);
//  EXTI->IMR |= (1UL << 0);
}



