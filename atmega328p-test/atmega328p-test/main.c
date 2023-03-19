#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	DDRB = 0xFF;
	PORTB = 0b00000001;
	

    while (1) 
    {
		PORTB |= (1 << PINB0);
		_delay_ms(500);
		PORTB &= ~(1 << PINB0);
		_delay_ms(500);
		
    }
}