/*
 * i2c.h
 *
 *  Created on: Apr 2, 2024
 *      Author: Quang Huy
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

void i2c_Scanbus();
void i2c_Address(uint8_t u8Address);
void i2c_Write(uint8_t u8Data);
void I2C_WriteMulti (uint8_t *data, uint8_t size);
void i2c_Start();
void i2c_Stop();

void i2c_Init();

#endif /* INC_I2C_H_ */
