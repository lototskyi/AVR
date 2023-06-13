#ifndef LCD_H_
#define LCD_H_

#include "main.h"

void LCD_ini(void);
void setPos(unsigned char x, unsigned char y );
void strLCD(char str1[]);
void strLCD80(char str1[]); //fill in the full LCD (80 symbols)
void clearLCD();
void sendCharLCD(unsigned char c);
void createCustomCharacter(unsigned char *Pattern, const char Location);

#define e1 PORTD |= 0b00001000; //set E = 1
#define e0 PORTD &= 0b11110111; //set E = 0
#define rs1 PORTD |= 0b00000100; //set RS = 1
#define rs0 PORTD &= 0b11111011; //set RS = 0

#endif /* LCD_H_ */