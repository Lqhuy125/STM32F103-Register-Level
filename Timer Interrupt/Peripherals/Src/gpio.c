#include "gpio.h"

void gpio_led_config(){
  //Enable port clock
  RCC->APB2ENR &= ~(1ul << 4); //clear
  RCC->APB2ENR |= 1UL << 4; // set 1
  //select mode
  GPIOC->CRH &= ~(3UL << 20); //PC13
  GPIOC->CRH |= (1UL << 21); // 10: Output mode, max speed 2 MHz.

  GPIOC->CRH &= ~(3UL << 24); //PC14
  GPIOC->CRH |= (1UL << 25);
  //CNF pull up
  GPIOC->CRH &= ~(3UL << 22); //00: General purpose output push-pull
  GPIOC->CRH &= ~(3UL << 26); //00: General purpose output push-pull

  //PA10
  RCC->APB2ENR &= ~(1ul << 2); //clear
  RCC->APB2ENR |= 1UL << 2; // set 1
  GPIOA->CRH &= ~(3UL << 8);
  GPIOA->CRH |= (2UL << 8);
  GPIOA->CRH &= ~(3UL << 10);
}

void gpio_button_config(){
  //enable clock port c
  RCC->APB2ENR &= ~(1ul << 4);
  RCC->APB2ENR |= 1UL << 4; // set 1
  //mode
  GPIOC->CRH &= ~(3ul << 28);
  //cnf
  GPIOC->CRH &= ~(3ul << 30);
  GPIOC->CRH |= (1UL << 30);
}

bool gpio_digitalRead(){
  return (bool)(GPIOC->IDR & (1ul << 15));
}
