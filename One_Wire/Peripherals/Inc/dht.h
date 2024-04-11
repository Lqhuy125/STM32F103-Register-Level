#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"

/*
 * Config signal pin PA8
 * IN: input pull-up pull-down
 * OUT: push-pull and 50MHz
 * */
#define DHT_IO_IN()   {GPIOA->CRH &= ~(0xful << 0); GPIOA->CRH |= (8ul << 0);}
#define DHT_IO_OUT()  {GPIOA->CRH &= ~(0xful << 0); GPIOA->CRH |= (3ul << 0);}

#define DHT_OUT_0   GPIOA->BSRR |= GPIO_BSRR_BR8
#define DHT_OUT_1   GPIOA->BSRR |= GPIO_BSRR_BS8
#define DHT_IN      (bool)(GPIOA->IDR & GPIO_IDR_IDR8)

typedef struct{
  uint8_t humi;
  uint8_t temp;
} DHT_Data;

void dht_Init();
DHT_Data dht_Read_Data();
uint8_t dht_Read_Byte();
uint8_t dht_Read_Bit();
uint8_t dht_Check();
void dht_Reset();

//Cách 1:
void dht_Start();
uint8_t dht_Check_Response();
void DHT11_Read(uint8_t *t, uint8_t *h);

#endif /* INC_DHT_H_ */
