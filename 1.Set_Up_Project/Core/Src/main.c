#include "main.h"
#include "rcc.h"
#include "gpio.h"

bool button_status = false;

int main(void)
{
  rcc_HSE_config();
  rcc_SysTick_config(72000); // T=1ms -> f=1/T=1KHz -> 72 000 000 / 72 000 = 1000
  gpio_LED_config();
//  gpio_BUTTON_config();


  while(1){

//    gpio_LED_toggle(13);
    gpio_digitalWrite(13, 1);
    rcc_sDelay(1);
    gpio_digitalWrite(13, 0);
    rcc_sDelay(1);

  }
}





//if(gpio_digitalRead() == 0 && button_status == 0){
//  gpio_digitalWrite(13, 1);
//  button_status = 1;
//  while(gpio_digitalRead() == 0);
//  rcc_msDelay(20);
//}
//if(gpio_digitalRead() == 0 && button_status == 1){
//  gpio_digitalWrite(13, 0);
//  button_status = 0;
//  while(gpio_digitalRead() == 0);
//  rcc_msDelay(20);
//}
