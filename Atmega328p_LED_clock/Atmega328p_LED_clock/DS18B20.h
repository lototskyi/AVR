#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

#define NOID 0xCC //skip identification
#define T_CONVERT 0x44 // code of temperature measuring
#define READ_DATA 0xBE
#define W_SCRATCHPAD 0x4e#define THERM_DECIMAL_STEPS_12BIT 625

#define PORTTEMP PORTC
#define DDRTEMP DDRC
#define PINTEMP PINC
#define BITTEMP 2

int dt_check();
char convertTemp (unsigned int tt);
char getDecimalTemp(unsigned int tt);

#endif /* DS18B20_H_ */