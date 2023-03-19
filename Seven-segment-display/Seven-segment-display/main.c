//LED 7-Segment Display OC

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

void segchar(unsigned char seg) 
{
	//    1 2 3 4 5 6 7 8
	//0b|dp|g|f|e|d|c|b|a|
	
	switch (seg)
	{
		case 1: 
			PORTD = 0b00000110;
			break;
		case 2:
			PORTD = 0b01011011;
			break;
		case 3:
			PORTD = 0b01001111;
			break;
		case 4:
			PORTD = 0b01100110;
			break;
		case 5:
			PORTD = 0b01101101;
			break;
		case 6:
			PORTD = 0b01111101;
			break;
		case 7:
			PORTD = 0b00000111;
			break;
		case 8:
			PORTD = 0b01111111;
			break;
		case 9:
			PORTD = 0b01101111;
			break;
		case 0:
			PORTD = 0b00111111;
			break;
	}
}

int main(void)
{
	unsigned char i;
	unsigned char butcount = 0, butstate = 0;
	
	DDRD = 0xFF; // output
	DDRB = 0x00; // input
	
	PORTD = 0b00000000;
	PORTB = 0b00000001; // pull-up resistor on pin0
	
	
	while (1)
	{
		for (i = 0; i < 10; i++)
		{
			while (butstate == 0)
			{
				if (!(PINB & 0b00000001))
				{
					if (butcount < 5)
					{
						butcount++;
					}
					else
					{
						i = 0;
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
						butstate = 1;
					}
				}
			}
			
			segchar(i);
			_delay_ms(500);
			butstate = 0;
		}
	}
}


