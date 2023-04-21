#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "PWM.h"
#include "led.h"
#include "twi.h"
#include "RTC.h"
#include "adc.h"
#include "DS18B20.h"

unsigned int adc_value, adc_counter, adc_tmp;

#endif /* MAIN_H_ */
