#include "eepromext.h"

char err1 = 0; //here will be an error

int EE_WriteByte(unsigned char c) 
{
	TWDR = c; //write byte to data register
	TWCR = (1 << TWINT) | (1 << TWEN); //turn on the data transfer
	while(!(TWCR & (1 << TWINT))); //waiting until TWINT is set
	
	if ((TWSR & 0xF8) != TW_MT_DATA_ASK) {
		return 1;
	}
	
	return 0;
}

unsigned char EE_ReadByte(void)
{
	err1 = 0;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); //turn on the data receiving
	while(!(TWCR & (1 << TWINT))); //waiting until TWINT is set
	
	 if ((TWSR & 0xF8) != TW_MR_DATA_ASK) err1=1;
	 else err1=0;
	
	return TWDR;
}

unsigned char EE_ReadLastByte(void)
{
	err1 = 0;
	TWCR = (1 << TWINT) | (1 << TWEN); //turn on the data receiving
	while(!(TWCR & (1 << TWINT))); //waiting until TWINT is set
	
	if ((TWSR & 0xF8) != TW_MR_DATA_NASK) err1=1;
	else err1=0;
	
	return TWDR;
}