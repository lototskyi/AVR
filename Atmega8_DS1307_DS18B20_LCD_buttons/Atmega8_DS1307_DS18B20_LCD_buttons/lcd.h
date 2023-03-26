#ifndef LCD_H_
#define LCD_H_

#include "main.h"

void LCD_ini(void);
void setPos(unsigned char x, unsigned char y );
void strLCD(char str1[]);
void clearLCD();
void sendCharLCD(unsigned char c);

#endif /* LCD_H_ */