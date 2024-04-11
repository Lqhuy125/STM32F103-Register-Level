/*
 * pwm.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Quang Huy
 */

#include "pwm.h"

void pwm_single_config(uint16_t psc, uint16_t arr){
  /* pwm timer1 ch1 - pa8*/

  /* 1. enable rcc clock for gpio and tim*/
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  /* 2. alternate function gpio */
  GPIOA -> CRH &= ~(0xFUL << 0); // clear 4bit pa8
  GPIOA -> CRH |= (2UL << 0);
  GPIOA -> CRH |= (2UL << 2);

  /*  Main output enable
   *  Việc kích hoạt bit này đảm bảo sinh ra PWM
   *  Bit này nên được kích hoạt trước khi PWM hoạt động */
  TIM1->BDTR |= TIM_BDTR_MOE;

  /* 3. config TIM1 channel 1 and mode PWM*/
  TIM1 -> CCMR1 &= ~(TIM_CCMR1_CC1S); // 00: kênh 1 được config la output
  TIM1 -> CCMR1 |= (6UL << 4); //110: PWM mode 1

  /* 4. enable mode*/
  TIM1->CCER &= ~TIM_CCER_CC1P; // Set polarity to active high
  TIM1->CCER |= TIM_CCER_CC1E;

  /* 5. set duty cycle */
  TIM1->CCR1 = 1000;
  TIM1->PSC = psc - 1;
  TIM1->ARR = arr -  1;

  /* Bắt đầu đếm*/
  TIM1->CR1 |= TIM_CR1_CEN;
}

void pwm_SetDuty(uint16_t duty, uint16_t arr){
  TIM1->CCR1 = duty*arr/100;
}
