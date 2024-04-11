/*
 * i2c.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Quang Huy
 */
#include "i2c.h"

void delay(uint32_t delay)
{
  for (volatile int i=0;i<1000;i++);
}
void i2c_Init(){
  /* STEPS
   1. Enable I2C clock and GPIO clock
      Enable AFIO clock
   2. Config I2C pin
      MODE: outut
      CNF: alternate function output open drain
   3.Reset I2C
   4. Chọn tần số cho I2C
   5. CCR
   6. TRISE
   7. Enable I2C */

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

  GPIOB->CRL|=GPIO_CRL_MODE6;
  GPIOB->CRL|=GPIO_CRL_CNF6;
  GPIOB->CRL|=GPIO_CRL_MODE7;
  GPIOB->CRL|=GPIO_CRL_CNF7;

  //Reset I2C
  I2C1->CR1 |= I2C_CR1_SWRST;
  I2C1->CR1 &= ~I2C_CR1_SWRST;

  //Config 18MHz for i2c
  I2C1->CR2 |= (18<<0);
  /*
     * t_mong_muốn = 5000ns
     * I2C FREQ =  18MHz
     * => t_mong_muốn = CCR * T_freq
     * => 5000ns = CCR * 1/18MHz => CCR = 90
     * */
  I2C1->CCR = 90;
  /*
     * T_rise = (T_r(SCL)/T_PCLK1) + 1
     * T_r(SCL) max của standark mode là 1000ns
     * T_PCLK1: Sẽ được khởi tạo từ RCC
     *
     * T_rise = 1000ns/(1/18MHz) + 1 = 18+1 = 19
     * */
  I2C1->TRISE = 19;
  I2C1->CR1 |= (1<<0); //Enable I2C
}
void i2c_Scanbus(){

  /*
   * @brief Scan bus
   *
   * 1. Start
   * 2. - Ghi dữ liệu vào thanh ghi DR ( thanh ghi DR 8bit)
   *      (i<<1|0): i<<1 and với bit 0 vì bit cuối này sẽ là bit Write/Read
   *      (0:Write - 1:Read)
   *      Tại chức năng scan bus, chúng ta lấy địa chỉ của thiết bị về nên là
   *      ghi vào thanh ghi DR
   *    - Đợi cả 2 thanh ghi SR1 và SR2 cùng lên cao
   * 3. Stop
   * 4. Wait ~ 100us cho lần scan tiếp theo
   * 5. - Check bit ACK tại thanh ghi SR1.
   *    - Nếu có tín hiệu => hiển thị address thiết bị
   * */
  for (uint8_t i=0;i<128;i++)
  {
    i2c_Start();

    I2C1->DR=(i<<1|0);
    while(!(I2C1->SR1)||!(I2C1->SR2)){};

    delay_us(117);

    if (I2C1->SR1&I2C_SR1_ADDR )
    {
      printf("Found I2C device at adress 0x%X\n\r",i);
      delay_ms(1170);
    }

    i2c_Stop();
  }
}

void i2c_Start(){
  I2C1->CR1 |= (1<<10);  // Enable the ACK
  I2C1->CR1 &= ~(1<<8);  // Generate START
  I2C1->CR1 |= (1<<8);  // Generate START
//  if((I2C1->SR1 & I2C_SR1_BERR))
//    I2C1->CR1 |= I2C_CR1_SWRST;

//  while (!(I2C1->SR1 & I2C_SR1_SB)){
//    printf("Error\n");
//    delay(585);
//    I2C1->CR1 |= I2C_CR1_SWRST;
//  };  // Wait for SB bit to set

  while (!(I2C1->SR1 & (1<<0)));  // Wait fror SB bit to set
}

void i2c_Stop(){
  I2C1->CR1 |= (1<<9);  // Stop I2C
}

void i2c_Write(uint8_t u8Data){
  /**** STEPS FOLLOWED  ************
  1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
  2. Send the DATA to the DR Register
  3. Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
  */
  while( !(I2C1->SR1 & I2C_SR1_TXE) );
  I2C1->DR = u8Data;
  while( !(I2C1->SR1 & I2C_SR1_BTF) );
}
void i2c_Address(uint8_t u8Address){
  /**** STEPS FOLLOWED  ************
  1. Send the Slave Address to the DR Register
  2. Wait for the ADDR (bit 1 in SR1) to set. This indicates the end of address transmission
  3. clear the ADDR by reading the SR1 and SR2 */
  I2C1->DR = u8Address;
  while(!(I2C1->SR1 & I2C_SR1_ADDR));
  // read SR1 and SR2 to clear the ADDR bit
  uint8_t temp = I2C1->SR1 | I2C1->SR2;
}
void I2C_WriteMulti (uint8_t *data, uint8_t size)
{
/**** STEPS FOLLOWED  ************
1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
2. Keep Sending DATA to the DR Register after performing the check if the TXE bit is set
3. Once the DATA transfer is complete, Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
*/
  while (!(I2C1->SR1 & I2C_SR1_TXE));  // wait for TXE bit to set
  while (size)
  {
    while (!(I2C1->SR1 & I2C_SR1_TXE));  // wait for TXE bit to set
    I2C1->DR = (uint32_t )*data++;  // send data
    size--;
  }
  while (!(I2C1->SR1 & I2C_SR1_BTF));  // wait for BTF to set
}

