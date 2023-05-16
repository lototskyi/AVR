#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define e1 PORTD |= 0b00000100; //set E = 1
#define e0 PORTD &= 0b11111011; //set E = 0
#define rs1 PORTD |= 0b00000010; //set RS = 1
#define rs0 PORTD &= 0b11111101; //set RS = 0

void LCD_ini(void);
void setPos(unsigned char x, unsigned char y );
void strLCD(char str1[]);
void clearLCD();

#endif /* LCD_H_ */