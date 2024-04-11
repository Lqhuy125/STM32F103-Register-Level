#include <main.h>

uint8_t i2c_Scan( uint8_t add);

int main(void)
{
  rcc_HSE_config();
  rcc_TIMER3_config();
  uart2_init();
  i2c_Init();
  uint8_t u8Address=0;
  uint8_t u8Check = 0;
	while(1){
//	    for(u8Address=0; u8Address<127; u8Address++){
//	      u8Check = i2c_Scan(u8Address);
//	      if(u8Check==0) {
//	        printf("Address: 0x%X\n\r", u8Address);
//
//	      }
//	    }
	    printf("a\n");

    delay_ms(1170); // 2s/1us * 1.17 = 2340000
	}
}

uint8_t i2c_Scan( uint8_t u8Address){
  i2c_Start();
  i2c_Send_Byte(u8Address | 0); //Ghi: 0 Read:1
  if(i2c_Wait_ACK()){
    i2c_Stop();
    return 1;
  }
  return 0;
}
