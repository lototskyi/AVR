#include "main.h"

uint16_t dtt;

int main(void)
{
	EEPROM_write(1, 120);
	EEPROM_write_word(3, 30000);
    EEPROM_write_dword(7, 0xFEDCBA98);
	EEPROM_write_string(16, "Hello world!");
	
	while (1) 
    {
    }
}

