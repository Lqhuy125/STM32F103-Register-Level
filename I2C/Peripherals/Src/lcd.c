/*
 * lcd.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Quang Huy
 */


#include "lcd.h"

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup


void LCD_Write (uint8_t Address, uint8_t *Data, int size)
{
  i2c_Start();
  i2c_Address(Address);
  for (int i=0; i<size; i++) i2c_Write(*Data++);
  i2c_Stop();
}

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (cmd&0xf0);
  data_l = ((cmd<<4)&0xf0);
  data_t[0] = data_u|0x0C;  //en=1, rs=0
  data_t[1] = data_u|0x08;  //en=0, rs=0
  data_t[2] = data_l|0x0C;  //en=1, rs=0
  data_t[3] = data_l|0x08;  //en=0, rs=0
  LCD_Write (SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4);
}

void lcd_send_data (char data)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (data&0xf0);
  data_l = ((data<<4)&0xf0);
  data_t[0] = data_u|0x0D;  //en=1, rs=0
  data_t[1] = data_u|0x09;  //en=0, rs=0
  data_t[2] = data_l|0x0D;  //en=1, rs=0
  data_t[3] = data_l|0x09;  //en=0, rs=0
  LCD_Write (SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4);
}

void lcd_clear (void)
{
  lcd_send_cmd (0x80);
  for (int i=0; i<70; i++)
  {
    lcd_send_data (' ');
  }
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}


void lcd_init (void)
{
  // 4 bit initialisation
  delay_ms(50);  // wait for >40ms
  lcd_send_cmd (0x30);
  delay_ms(5);  // wait for >4.1ms
  lcd_send_cmd (0x30);
  delay_us(150);  // wait for >100us
  lcd_send_cmd (0x30);
  delay_ms(10);
  lcd_send_cmd (0x20);  // 4bit mode
  delay_ms(10);

  // dislay initialisation
  lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
  delay_ms(1);
  lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
  delay_ms(1);
  lcd_send_cmd (0x01);  // clear display
  delay_ms(2);
  lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
  delay_ms(1);
  lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
  while (*str) lcd_send_data (*str++);
}
