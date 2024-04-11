#include "adc.h"

void adc_gpio_config(){
  //enable portA clock
  RCC->APB2ENR |= 1UL << 2; // set 1
  //select mode and cnf
  GPIOA->CRL &= ~(3UL << 16);
  GPIOA->CRL &= ~(3UL << 18);
}
void adc_config(){
  //enable ADC clock
  RCC->APB2ENR |= 1UL << 9; //adc1

  //set sample time
  ADC1->SMPR2 |= (3UL << 12); //Kênh 4
  //select mode and aligh bit right or left

  //set trigger
  ADC1->CR2 |= (7UL << 17);

  //select channel
  ADC1->SQR3 = 4;

  //turn on ADC
  ADC1->CR2 |= (1UL << 0);
}
void adc_start(){
  ADC1->SR = 0;
  ADC1->CR2 |= (1UL << 22);
  ADC1->CR2 |= (1UL << 0);
}
void adc_stop(){
  ADC1->SR = 0;
  ADC1->CR2 &= ~(1UL << 22);
}
uint16_t adc_readValue(){
  return (ADC1->DR);
}
