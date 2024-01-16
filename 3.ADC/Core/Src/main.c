#include "main.h"

#include "adc.h"

bool button_status = false;
int main(void)
{
  rcc_HSE_config();
  rcc_SysTick_config(72000); // T=1ms -> f=1/T=1KHz -> 72 000 000 / 72 000 = 1000
  uart_UART2_config();
  uart_UART2_GPIO_config();
  adc_GPIO_config();
  adc_single_config(Potemtionmeter);

  uint16_t value = 0;
  while(1){
    
    /* Viết chương trình hiển thị giá trị triết áp thông qua USART2 */
    adc_Start();
    if(adc_poll_For_End_of_Conservation(5)){
       value = adc_readValue();
       uart2_write_integer((int)value);
       uart_UART2_puts("\n");
    }
    else {
      uart_UART2_puts("Failed\n");
    }

    rcc_msDelay(300);



  }
}
