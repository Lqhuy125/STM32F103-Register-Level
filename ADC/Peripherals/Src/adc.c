/*
 * adc.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Quang Huy
 */
#include "adc.h"

void adc_GPIO_config(){
  /* enable clock for GPIO */
  RCC->APB2ENR |= 1UL << 2; // set 1
  /* config mode and cnf*/
  GPIOA->CRL &= ~(3UL << 20);
  GPIOA->CRL &= ~(3UL << 22);
}

void adc_single_config(uint8_t channel){
  /* enable ADC clock */
  RCC->APB2ENR |= 1UL << 9;
  /* set sample time for channel
   * CHOOSE 28 CYCLE <=> (12 + 28)/ 12 = 3.3us */
  ADC1->SMPR2 |= (3UL << 15); //Kênh 5

  /* select Data alignment and Continuous conversion
   *
   * Tại thanh ghi CR2 có giá trị reset là 0
   * Vì vậy th
   *
   * */
  /* Trigger SWSTART*/
  ADC1->CR2 |= (7UL << 17);

  /* Lựa chọn kênh */
  ADC1->SQR3 = channel;

  /*  turn on ADC
   *  Truyền lần đầu tiên */
  ADC1->CR2 |= (1UL << 0);
}

void adc_Start(){
  ADC1->SR = 0;
  ADC1->CR2 |= (1UL << 22);
  ADC1->CR2 |= (1UL << 0);
}

void adc_Stop(){
  ADC1->SR = 0;
  ADC1->CR2 &= ~(1UL << 22);
}

uint16_t adc_readValue(){
  return (ADC1->DR);
}



