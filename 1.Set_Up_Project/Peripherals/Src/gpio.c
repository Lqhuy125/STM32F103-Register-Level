/*
 * gpio.c
 *
 *  Created on: Jan 4, 2024
 *      Author: Quang Huy
 */
#include "gpio.h"

//#ifdef USE_GPIOA
//  #define GPIO_PORT       GPIOA
//#elif defined(USE_GPIOB)
//    #define GPIO_PORT     GPIOB
//#else
//    #define GPIO_PORT     GPIOC
//#endif

void gpio_LED_config(){
  //Enable port clock
  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPCEN); //clear
  RCC->APB2ENR |= 1UL << 4; // set 1
  //select mode
  GPIOC->CRH &= ~(3UL << 20); //PC13
  GPIOC->CRH |= (1UL << 21); // 10: Output mode, max speed 2 MHz.
  //CNF pull up
  GPIOC->CRH &= ~(3UL << 22); //00: General purpose output push-pull
}
void gpio_digitalWrite(uint8_t pin ,bool state){
  if(state){
    GPIOC->ODR |= (1UL << pin);
  }
  else{
    GPIOC->ODR &= ~(1UL << pin);
  }

}
void gpio_LED_toggle(uint8_t pin){
  GPIOC->ODR ^= (1UL << pin);
  rcc_msDelay(1000);
}

void gpio_BUTTON_config(){
  //PCA0
  //Enable port clock
  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN); //clear
  RCC->APB2ENR |= 1UL << 2; // set 1
  //select mode
  GPIOA->CRL &= ~(3UL << 0); //PA0 00 INPUT
  //CNF floating
  GPIOA->CRL &= ~(3UL << 2); // clear
  GPIOA->CRL |= (1UL << 2);

  GPIOA->ODR |= GPIO_IDR_IDR0;


  //PCB0
    //Enable port clock
    RCC->APB2ENR &= ~(RCC_APB2ENR_IOPBEN); //clear
    RCC->APB2ENR |= 1UL << 2; // set 1
    //select mode
    GPIOB->CRL &= ~(3UL << 0); //PA0 00 INPUT
    //CNF pullup pull down
    GPIOB->CRL &= ~(3UL << 2); // clear
    GPIOB->CRL |= (2UL << 2);

    GPIOB->ODR |= (1UL << 0);


}
bool gpio_digitalRead(){
  return (bool)(GPIOA->IDR & GPIO_IDR_IDR0);
}
bool gpio_digitalRead_PCB0(){
  return (bool)(GPIOB->IDR & GPIO_IDR_IDR0);
}


