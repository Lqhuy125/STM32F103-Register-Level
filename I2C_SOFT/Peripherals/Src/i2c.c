/*
 * i2c.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Quang Huy
 */

#include "i2c.h"

void i2c_Init(){
  //Enable clock PORTB
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

  //Khai bao SCL SDA output open drain
  SDA_OUT();
  SCL_OUT();
  //Khoi tao gia tri ban dau = 1
  I2C_SCL_1;
  I2C_SDA_1;
}

void i2c_Start(){
  /* Do sẽ lặp lại liên tục nên cần khai báo */
  SDA_OUT();
  SCL_OUT();

  I2C_SCL_1;
  I2C_SDA_1;
  delay_us(4);
  I2C_SDA_0;
  delay_us(4);
  I2C_SCL_0;
}

void i2c_Stop(){
  /* Do sẽ lặp lại liên tục nên cần khai báo */
  SDA_OUT();
  SCL_OUT();

  I2C_SCL_0;
  I2C_SDA_0;
  delay_us(4);
  I2C_SCL_1;
  delay_us(4);
  I2C_SDA_1;
}


void i2c_Send_Byte(uint8_t u8Data){

  //Khi bắt đầu truyền thì cả sda scl đều xuống thấp. 2 dòng dưới để đảm bảo
  I2C_SDA_0;
  I2C_SCL_0;

  SDA_OUT();

  /* Khi đọc byte thì sẽ nhận được lần lượt từ phải qua trái
   * => Khi gửi, chúng ta sẽ phải chuyển dẩn từ trái sang phải
   * */
  // u8Data & 0b10000000: bit 1 đầu là đang ở ở Read
  for(uint8_t i=0; i<8; i++){
    GPIOB->ODR = ((u8Data & 0x80) >> 7) << 9; // Gửi từng byte 1 đi qua chân SDA
    u8Data <<= 1;
    delay_us(2);
    I2C_SCL_1; //Mỗi khi truyên dữ liệu là cần 1 tín hiệu clk
    delay_us(2);
    I2C_SCL_0;
    //Sau 1 SCL thì dịch bit

  } //Truyền xong 8 bit bao gồm Address

  //Sau khi truyền xong data SCL và SDA xuống mức thấp
  I2C_SCL_0;
  delay_us(2);
  I2C_SDA_0;
  delay_us(2);
}
void i2c_Read_Byte(uint8_t u8ACK){

  I2C_SDA_1; //cho nó lên cao để cbi đọc xem SDA có xuống thấp hay không
  delay_us(2);
  //chuyển SDA sang input để check
  SDA_IN();
  /* Nếu chân SDA ở mức thấp thì là xác nhận,
     còn cao thì sẽ là k xác nhận */
  uint8_t u8Rec=0;

  for(uint8_t i=0; i<8; i++){
    I2C_SCL_0;
    delay_us(2);
    //bật SCL để nhận tín hiệu ACK
    I2C_SCL_1;
    delay_us(2);
    u8Rec<<=1;  /*Dịch 1 để bỏ qua bit có trọng số thấp nhất
                  bit này là R/W, còn 7bit trước là address*/
    if(READ_SDA){
      u8Rec |= 0x01; // u8Rec++;
    }
    delay_us(2); //Đảm bảo truyền được bit trước khi SCL xuống thấp
    I2C_SCL_0;
    delay_us(2);
  }

  if(!u8ACK){ //Nếu ACK trên SDA là mức thấp thì là xác nhận đúng
    i2c_ACK();
  } else {
    i2c_NACK();
  }
}

void i2c_ACK(){ //
  I2C_SCL_0;
  SDA_OUT();
  I2C_SDA_0;
  delay_us(2);
  I2C_SCL_1;
  delay_us(2);
  I2C_SCL_0;
}
void i2c_NACK(){
  I2C_SCL_0;
  SDA_OUT();
  I2C_SDA_1;
  delay_us(2);
  I2C_SCL_1;
  delay_us(2);
  I2C_SCL_0;
}

uint8_t i2c_Wait_ACK(){
  /*Đầu tiên set SDA = 1 để khi mình nhận
    xem SDA có là 0 là có thành công không*/
  I2C_SDA_1;
  delay_us(2);
  SDA_IN();
  I2C_SDA_1;delay_us(1);
  I2C_SCL_1;delay_us(1);
  uint8_t time=0;
  while(READ_SDA){
    time++;
    if(time>250)
      i2c_Stop();
    return 1;
  }
  I2C_SCL_0;
  return 0;
}

