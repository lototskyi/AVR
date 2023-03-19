#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char i;
	
	DDRD = 0xFF;
	PORTD = 0b00000001;
	while (1)0
	{
		for (i = 0; i <= 7; i++) {
			
			PORTD = (1 << i);
			_delay_ms(500);
		}
		
	}
}

