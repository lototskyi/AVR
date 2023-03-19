#include "main.h"

unsigned char dtt;
uint16_t dt16;
uint32_t dt32;

int main(void)
{
	//EEPROM_write(1, 120);

	USART_ini(8);
	
	asm("nop");
			
	dtt = EEPROM_read(1);
	USART_Transmit(dtt);
	
	dt16 = EEPROM_read_word(3);
	USART_Transmit((unsigned char) (dt16 >> 8));
    USART_Transmit((unsigned char) dt16);
	
	dt32 = EEPROM_read_dword(7);
	USART_Transmit((unsigned char) (dt32 >> 24));
	USART_Transmit((unsigned char) (dt32 >> 16));
	USART_Transmit((unsigned char) (dt32 >> 8));
	USART_Transmit((unsigned char) dt32);
	
	const char * buff = EEPROM_read_string(16, 12);
	for (int i = 0; i < 12; i++) {
		USART_Transmit(buff[i]);
	}
	
    while (1) 
    {
    }
}

