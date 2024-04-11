#include "main.h"

bool adcEOC = false;
uint16_t value = 0;

int main(void)
{
  rcc_HSE_config();
  rcc_SysTick_config(72000); // T=1ms -> f=1/T=1KHz -> 72 000 000 / 72 000 = 1000

  uart_UART2_config();
  uart_UART2_GPIO_config();

  adc_GPIO_config();
  adc_single_config(Potemtionmeter);

  gpioC_config();

  adc_enableEOC();
  adc_Start();
  while(1){

    /* Viết chương trình hiển thị giá trị triết áp thông qua USART2
       Polling */
//    adc_Start();
//    if(adc_poll_For_End_of_Conservation(2)){
//       value = adc_readValue();
//       uart_UART2_puts("ADC value = ");
//       uart2_write_integer((int)value);
//       uart_UART2_puts("\n");
//    }
//    else {
//      uart_UART2_puts("Failed\n");
//    }


    /* ADC Interrupt */
    if(adcEOC)
    {
      adcEOC = false;
      uart_UART2_puts("ADC value = ");
      uart2_write_integer((int)value);
      uart_UART2_puts("\n");
      adc_Start();
    }

    if(value > 2000)
      gpioC_WritePin(13, 1);
    else
      gpioC_WritePin(13, 0);

    rcc_msDelay(500);
  }
}

void ADC1_2_IRQHandler()
{
  if(ADC1->SR & ADC_SR_EOC)
  {
    adcEOC = true;
    value = adc_readValue();
    NVIC_ClearPendingIRQ(ADC1_IRQn);
//    gpioC_toggle(13);
  }
}
