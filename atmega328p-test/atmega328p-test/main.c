#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	DDRD = 0xFF;
	PORTD = 0b00000001;
	

    while (1) 
    {
		PORTD |= (1 << PIND0);
		_delay_ms(500);
		PORTD &= ~(1 << PIND0);
		_delay_ms(500);
		
    }
}