#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

#define NOID 0xCC //skip identification
#define T_CONVERT 0x44 // code of temperature measuring
#define READ_DATA 0xBE

#define PORTTEMP PORTD
#define DDRTEMP DDRD
#define PINTEMP PIND
#define BITTEMP 1

int dt_check();
char convertTemp (unsigned int tt);

#endif /* DS18B20_H_ */