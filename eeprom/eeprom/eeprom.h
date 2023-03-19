#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write_word(unsigned int uiAddress, uint16_t ucData); // write 2-byte value
uint16_t EEPROM_read_word(unsigned int uiAddress); // read 2-byte value
void EEPROM_write_dword(unsigned int uiAddress, uint32_t ucData); // write 4-byte value
uint32_t EEPROM_read_dword(unsigned int uiAddress); // read 4-byte value
void EEPROM_write_string(unsigned int uiAddress, char str1[]); // write string
const char* EEPROM_read_string(unsigned int uiAddress, unsigned int sz); // read string

#endif /* EEPROM_H_ */