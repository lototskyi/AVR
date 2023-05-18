#ifndef LCD_H_
#define LCD_H_

#include "main.h"

void LCD_ini(void);
void setPos(unsigned char x, unsigned char y );
void strLCD(char str1[]);
void clearLCD();
void sendCharLCD(unsigned char c);

#define e1 PORTD |= 0b00001000; //set E = 1
#define e0 PORTD &= 0b11110111; //set E = 0
#define rs1 PORTD |= 0b00000100; //set RS = 1
#define rs0 PORTD &= 0b11111011; //set RS = 0

#endif /* LCD_H_ */