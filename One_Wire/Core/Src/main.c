#include <main.h>

uint8_t u8Check=0;
uint8_t Rh_byte1=0, Rh_byte2=0, Temp_byte1=0, Temp_byte2=0;
uint8_t SUM=0;
uint8_t u16Temp, u16Humi;
float fTemp=0, fHumi=0;

int main(void)
{
  rcc_HSE_config();
  rcc_TIMER3_config();
  uart2_init();
	while(1){
	  dht_Start();
	  u8Check = dht_Check_Response();
//	  Rh_byte1 = dht_Read_Data();
//	  Rh_byte2 = dht_Read_Data();
//	  Temp_byte1 = dht_Read_Data();
//    Temp_byte2 = dht_Read_Data();
//    SUM = dht_Read_Data();
//    if(SUM != (Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2) )
//      printf("error\n");
//    value = dht_Read_Data();
//    u16Temp = value.temp;
//    u16Humi = value.humi;


	  DHT11_Read(&u16Temp, &u16Humi);

    fTemp = (float)u16Temp;
    fHumi = (float)u16Humi;
    printf("Temp = %.2f\t", fTemp);
    printf("Humi = %.2f\n", fHumi);
//	  printf("a\n");
    delay_ms(1170);
	}
}
//    sensor_data = dht_Read_Data();
//    printf("Temp = %d\t", sensor_data.temp);
//    printf("Humi = %d\n", sensor_data.humi);
/* DHT22 */
//    fTemp= (float)((Temp_byte1<<8)|Temp_byte2)/10.0;
//    fHumi= (float)((Rh_byte1<<8)|Rh_byte2)/10.0;
