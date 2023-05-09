/*
The lib is useful for the LED&KEY board based on TM1638
*/

#ifndef TM1638_H_
#define TM1638_H_

#include "main.h"

#define DIO PORTB0
#define CLK PORTB1
#define STB PORTB2

#define STB_UP PORTB |= (1 << STB)
#define STB_DOWN PORTB &= ~(1 << STB)

void shiftOut(char value);
void sendCommand(char value);
void clearDisplay();
void clearLed();
void reset();


#endif /* TM1638_H_ */