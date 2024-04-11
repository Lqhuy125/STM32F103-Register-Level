/*
 * gpio.c
 *
 *  Created on: Jan 11, 2024
 *      Author: Quang Huy
 */


#include "gpio.h"

/*
 *    @brief PORT C
 */
void gpioC_config(){
  /* Enable port clock */
  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPCEN); //clear
  RCC->APB2ENR |= 1UL << 4; // set 1

  /* Select Mode */
  GPIOC->CRH &= ~(3UL << 20); //PC13
  GPIOC->CRH |= (2UL << 20); // 10: Output mode, max speed 2 MHz.

  /* Select CNF */ //pull up
  GPIOC->CRH &= ~(3UL << 22); //00: General purpose output push-pull
}

void gpioC_WritePin(uint16_t pin, GPIO_PinState PinState){
  if(PinState){
    GPIOC->ODR |= (1UL << pin);
  }
  else{
    GPIOC->ODR &= ~(1UL << pin);
  }
}

void gpioC_toggle(uint16_t pin)
{
  GPIOC->ODR ^= (1UL << pin);
}


GPIO_PinState gpioC_ReadPin(uint16_t pin){
  return (bool)(GPIOC->IDR & (1UL << pin));
}

/*
 *    @brief PORT A
 */

void gpioA_config(){
  //Enable port clock
  RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN); //clear
  RCC->APB2ENR |= 1UL << 2; // set 1
  //select mode
  GPIOA->CRL &= ~(3UL << 0); //PA0 00 INPUT
  //CNF floating
  GPIOA->CRL &= ~(3UL << 2); // clear
  GPIOA->CRL |= (1UL << 2);
}

void gpioA_WritePin(uint16_t pin, GPIO_PinState PinState){
  if(PinState){
      GPIOA->ODR |= (1UL << pin);
    }
    else{
      GPIOA->ODR &= ~(1UL << pin);
    }
}

GPIO_PinState gpioA_ReadPin(uint16_t pin){
  return (bool)(GPIOA->IDR & (1UL << pin));
}

/*
 *    @brief PORT B
 */
