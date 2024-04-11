#include "adc.h"

void adc_GPIO_config(){
  //Enable PORTA clock
  RCC->APB2ENR |= 1UL << 2; // set 1
  //PA5: MODE-INPUT, CNF-ANALOG_MODE
  GPIOA->CRL &= ~(3UL << 20);
  GPIOA->CRL &= ~(3UL << 22);
  //PA4
  GPIOA->CRL &= ~(3UL << 16);
  GPIOA->CRL &= ~(3UL << 18);
  //PA3
  GPIOA->CRL &= ~(3UL << 12);
  GPIOA->CRL &= ~(3UL << 14);
}

void adc_single_config(ADC_SingleSelect channel){
  //ENABLE ADC1 CLOCK
  RCC->APB2ENR |= 1UL << 9;
  //RIGHT ALINGN
  ADC1->CR2 &= ~(1UL << 11);
  /* select Data alignment and Continuous conversion
   *
   * Tại thanh ghi CR2 có giá trị reset là 0
   * Vì vậy tự động là right align and continous  */
  //SINGLE CONSERVATION
  ADC1->CR2 &= ~(1UL << 1);
  //SOFTWARE TRIGGER
  ADC1->CR2 |= (7UL << 17);
  //SAMPLE TIME: CHOOSE 28 CYCLE <=> (12 + 28)/ 12 = 3.3us
  //PA5, PA4, PA3
  ADC1->SMPR2 |= (3UL << 15);
  ADC1->SMPR2 |= (3UL << 12);
  ADC1->SMPR2 |= (3UL << 9);
  //Xác định số lượng chuyển đổi: No of conservation = 1
//  ADC1->SQR1 &= ~(15UL << 20);
  //RANK1 CHANNEL5,4,3
  ADC1->SQR3 = channel;

  //POWER UP ADC
  ADC1->CR2 |= (1UL << 0);
  //WAIT FOR ADC STABILIZE
  for(uint16_t i=0; i<36; i++);

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
/* polling chờ cho chuyển đổi hoàn tất với thời gian timeout.*/
bool adc_poll_For_End_of_Conservation(uint32_t timeOut ){
  uint32_t startTicks = rcc_msGetTicks();
  while( (ADC1->SR & (1UL << 1)) == 0){
    if( (rcc_msGetTicks() - startTicks) > timeOut ){
      return false;
    }
  }
  return true;
}

uint16_t adc_readValue(){
  return (ADC1->DR);
}


void adc_enableEOC()
{
  ADC1->CR1 |= ADC_CR1_EOCIE;
  NVIC_EnableIRQ(ADC1_IRQn);

}
void adc_disableEOC()
{
  ADC1->CR1 &= ~ADC_CR1_EOCIE;
  NVIC_DisableIRQ(ADC1_IRQn);
}

