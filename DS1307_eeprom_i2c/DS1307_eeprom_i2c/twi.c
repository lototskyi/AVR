#include "twi.h"

void I2C_Init(void)
{
	TWBR = 0x20; // frequency of I2C (if 8MHz of MC then 100kHz) [TWBR = ((F_CPU/F_SCL) - 16)/(2 * 4^TWPS))]
}

void I2C_StartCondition(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT))); //waiting until TWINT is set
}

void I2C_StopCondition(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_SendByte(unsigned char c)
{
	TWDR = c; //write byte to data register
	TWCR = (1 << TWINT) | (1 << TWEN); //turn on the data transfer
	while(!(TWCR & (1 << TWINT))); //waiting until TWINT is set
}