/*
 * dht.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Quang Huy
 */

#include "dht.h"

/* 1. Xung đầu tiên là mức cao */
void dht_Init(){
  RCC->APB2ENR |= 1 << 2;

  DHT_IO_OUT();

  DHT_OUT_1;

  dht_Reset();
}

/* 2. MCU kéo xuống thấp ít nhất 18ms để báo sensor sẽ gửi dữ liệu*/
void dht_Reset(){
  DHT_IO_OUT(); // Cần set lại OUTPUT vì sau 1 quá trình đọc nó sẽ
                // yêu cầu chân này ở INPUT để đọc data từ sensor
  DHT_OUT_0;
  rcc_msDelay(20); // >18ms
  DHT_OUT_1;
  rcc_usDelay(3); //20us - 40us
}

/*3. Đến bước tiếp theo set chân signal là input*/
uint8_t dht_Check(){
  DHT_IO_IN();

  uint8_t u8TimeOut=0;
  bool check_response = false;
  /* Chờ xuống */
  while(DHT_IN==1 && u8TimeOut<10){
    u8TimeOut++;
    rcc_usDelay(1); //10us
  }
  if(u8TimeOut >= 10)
    check_response = 1; //fail
  else
    check_response = 0;

  return check_response;

  u8TimeOut=0;
  /* Chờ lên */
  while(DHT_IN==0 && u8TimeOut<10){
    u8TimeOut++;
    rcc_usDelay(1);
  }
  if(u8TimeOut>10)
    check_response = 1; //fail
  else
    check_response = 0; //ok

  return check_response;
}

uint8_t dht_Read_Bit(){
  uint8_t u8Time=0;

  /* Đang mức cao và chờ xuống, đến Tín hiệu thấp đủ 50us */
  while(DHT_IN==1 && u8Time<5){
    u8Time++;
    rcc_usDelay(1); //10us
  }

  /* Chờ lên
   * Bit 0: 26-28us
   * Bit 1: 70us
   */
  u8Time=0;
  while(DHT_IN==0 && u8Time<5){
    u8Time++;
    rcc_usDelay(1);
  }
  rcc_usDelay(4);
  if(DHT_IN)
     return 1;
  else
    return 0;
}

uint8_t dht_Read_Byte(void){
  uint8_t i=0;
  uint8_t data=0;//00000001

  for(i=0;i<8;i++){

    data<<=1;
    data|=dht_Read_Bit();

  }
  return data;
}

DHT_Data dht_Read_Data(){
  uint8_t i;
  uint8_t data[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
  DHT_Data result;
  dht_Reset();

  if(dht_Check() == 0){

    for(i = 0; i<5; i++){

      data[i] = dht_Read_Byte();

      if(data[0]+data[1]+data[2]+data[3]==data[4])
      {
        result.humi=data[0];
        result.temp=data[2];
      }
      else
        printf("Data failed\n");
    }
  }
  else{
   printf("Check falied\n");
  }

  return result; //ok

}

/*Cách khác*/
void dht_Start(){
  RCC->APB2ENR |= 1 << 2;
  DHT_IO_OUT();
  DHT_OUT_0;
  delay_ms(22); //>18ms
  DHT_OUT_1;
  delay_us(20); //20us
  DHT_IO_IN();
}

uint8_t dht_Check_Response()
{
  int Response = 0;
  /*
   *  Bắt đầu DHT signal
   *  Đầu tiên delay ~40us đến khoảng giữa Start LO
   */
  delay_us(40); //40us
  /* Bắt đầu kiểm tra xem nó là mức thấp hay không
   * Nếu có là mức thấp, sẽ cho delay ~80us đến giữa khoảng Start HI
   */
  if (!DHT_IN)
  {
    delay_us(80); //80us
    if (DHT_IN)
      Response = 1;
    else
      Response = -1;
  }
  /* Sau khi đến đoạn giữa Start HI thì
     sẽ đợi tín hiệu xuống thấp bằng while */
//  while (DHT_IN);   // wait for the pin to go low

  return Response;
}

void DHT11_Read(uint8_t *t, uint8_t *h)
{
//  uint8_t i,j;
//  for (j=0;j<8;j++)
//  {
//    while (!DHT_IN);   // wait for the pin to go high
//    /* đợi 40 us bắt đầu kiểm tra xem nó là mức cao hay thấp
//       Nếu là bit 0: 26-28us
//       Nếu là bit 1: 70us
//       => sẽ lấyt time giữa để check */
//    rcc_usDelay(4);
//
//    if (!DHT_IN)   // if the pin is low
//    {
//      /* Viết bit 0 vào vị trí đó
//         Sử dụng toán tử & để clear */
//      i&= ~(1<<(7-j));
//    }
//    else i|= (1<<(7-j));  // if the pin is high, write 1
//    while (DHT_IN);  // after done will wait for the pin to go low
//  }
//
//  return i;

  uint8_t i, j = 0;
  uint8_t DHT11_DATA[5] = {0, 0, 0, 0, 0};
  for(i = 0; i < 5; i++)
  {
     for(j = 0; j < 8; j++)
     {

       while(!DHT_IN); //wait here while pin is low
       delay_us(40);
       if(!DHT_IN)
         DHT11_DATA[i] &= ~(1<<(7-j));   //write 0 to bit
       else
         DHT11_DATA[i] |= (1<<(7-j)); //write 1 to bit

       while(DHT_IN);   //while pin is HIGH, hold here
     }
   }
  *t = DHT11_DATA[2];
  *h = DHT11_DATA[0];
}
