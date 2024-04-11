

#include <main.h>

uint32_t __IO countled = 0;
void TIM3_IRQHandler(void){
  if( (TIM3->SR & (1UL << 0)) == 1 ){
    countled++;
    if(countled < 1000){
      GPIOC->BSRR |= GPIO_BSRR_BS13;
    }
    if(countled >=  1000 && countled < 2000){
      GPIOC->BSRR |= GPIO_BSRR_BR13;
    }
    if(countled >= 2000) countled = 0;

    TIM3->SR &= ~(1UL << 0);
  }

}

#define arr 1000
#define arr_adc 4095
uint16_t value = 0;
int main(void)
{
  rcc_HSE_config();
  pwm_single_config(72, arr_adc); //tao ra xung 1KHZ
  rcc_SysTick_config(72000);
  gpio_config_PortC();
  timer3_config_interupt();
  adc_gpio_config();
  adc_config();

	while(1){
	  adc_start();
	  value = adc_readValue()/40;
	  pwm_SetDuty(value, arr_adc);
	  rcc_msDelay(100);
	}
}
