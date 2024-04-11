#include <main.h>

int main(void)
{
  rcc_HSE_config();
  rcc_TIMER3_config();
  i2c_Init();
  uart2_init();

  lcd_init ();
  lcd_put_cur (1,5);
  lcd_send_string ("hello");

//  i2c_Start();
//  i2c_Address(0x4E);
//  i2c_Write(0x00);
//  i2c_Stop();
	while(1){
//	  i2c_Scanbus();
//	  for(uint8_t i=0; i<8; i++){
//	    i2c_Start();
//      i2c_Address(0x4E);
//      i2c_Write(1<<i);
//      i2c_Stop();
//      delay_ms(1170);
//	  }

	}
}
