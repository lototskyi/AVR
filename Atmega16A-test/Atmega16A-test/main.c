#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;

    /* Replace with your application code */
    while (1) 
    {
		PORTA |= (1 << PINA0);
		_delay_ms(500);
		PORTA &= ~(1 << PINA0);
		_delay_ms(500);
    }
}

