#ifndef LCD_H_
#define LCD_H_

#include "main.h"

void LCD_init(void);
void setPos(unsigned char x, unsigned char y );
void strLCD(char str1[]);
void clearLCD();
void sendChar(unsigned char c);
void lcd_num(uint8_t num, uint8_t line, uint8_t pos);

#define e1 I2C_SendByteByADDR(portlcd |= 0x04, 0b01001110) // set line E = 1
#define e0 I2C_SendByteByADDR(portlcd &= ~0x04, 0b01001110) // set line E = 0
#define rs1 I2C_SendByteByADDR(portlcd |= 0x01, 0b01001110) // set RS = 1
#define rs0 I2C_SendByteByADDR(portlcd &= ~0x01, 0b01001110) // set RS = 0
#define setled() I2C_SendByteByADDR(portlcd |= 0x08, 0b01001110) // turn the back light on
#define setwrite() I2C_SendByteByADDR(portlcd &= ~0x02, 0b01001110) // set write mode

#endif /* LCD_H_ */