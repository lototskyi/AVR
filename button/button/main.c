#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//unsigned char i;
	unsigned char butcount = 0;
	
	DDRD = 0xFF; // output
	DDRB = 0x00; // input
	
	PORTD = 0b00000000;
	PORTB = 0b00000001; // pull-up resistor on pin0
	while (1)
	{

		if (!(PINB & 0b00000001))
		{
			if (butcount < 5)
			{
				butcount++;
			}
			else
			{
				PORTD = 0b00000001;
			}
		
		} 
		else
		{
			if (butcount > 0)
			{
				butcount--;
			}
			else
			{
				PORTD = 0b00000000;
			}
		}
		//for (i = 0; i <= 7; i++) {
			//
			//PORTD = (1 << i);
			//_delay_ms(500);
		//}
		
	}
}

