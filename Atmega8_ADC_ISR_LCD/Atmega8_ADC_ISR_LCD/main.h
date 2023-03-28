#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int adc_value, adc_counter, adc_tmp;

#define e1 PORTD |= 0b00001000; //set E = 1
#define e0 PORTD &= 0b11110111; //set E = 0
#define rs1 PORTD |= 0b00000100; //set RS = 1
#define rs0 PORTD &= 0b11111011; //set RS = 0

#include "lcd.h"
#include "adc.h"

#endif /* MAIN_H_ */
