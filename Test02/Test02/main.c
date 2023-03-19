#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
    PORTD = 0b00000000;
    while (1) 
    {
		PORTD |= (1<<(PORTD0));
		_delay_ms(500);
		PORTD &= ~(1<<(PORTD0));
		_delay_ms(500);
    }
}

