/*
 * i2c.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Quang Huy
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

/*
 *  Sử dụng PB8 PB9 là SCL SDA cho i2c
 *  SDA_IN  PB9 cnf:10 mode: 00
 *  SDA_OUT PB9 cnf:00 mode: 11
 *
 *  SCL PB8 OUTPUT cnf:00 mode: 11
 * */
#define SDA_IN()  {GPIOB->CRH &= ~(0xful << 4); GPIOB->CRH |= (8 << 4);}
#define SDA_OUT() {GPIOB->CRH &= ~(0xful << 4); GPIOB->CRH |= (3 << 4);}
#define SCL_OUT() {GPIOB->CRH &= ~(0xful << 0); GPIOB->CRH |= (3 << 0);}

#define I2C_SCL_1   GPIOB->BSRR |= GPIO_BSRR_BS8 //SCL=1
#define I2C_SDA_1   GPIOB->BSRR |= GPIO_BSRR_BS9 //SDA=1
#define I2C_SCL_0   GPIOB->BSRR |= GPIO_BSRR_BR8 //SCL=0
#define I2C_SDA_0   GPIOB->BSRR |= GPIO_BSRR_BR9 //SDA=0
#define READ_SDA    (bool)(GPIOB->IDR & GPIO_IDR_IDR9)

void i2c_Init();
void i2c_Start();
void i2c_Stop();

/*
 * Khi gửi, sẽ gửi bit có trọng số cao thứ 2 đầu tiên, rồi lần lượt đến bit 0
 * bit có trọng số cao nhất sẽ là bit write/read
 * */
void i2c_Send_Byte(uint8_t u8Data);
void i2c_Read_Byte(uint8_t u8ACK);
void i2c_ACK();
void i2c_NACK();
uint8_t i2c_Wait_ACK();
#endif /* INC_I2C_H_ */
