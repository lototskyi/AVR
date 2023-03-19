//Atmega8
//LED 7-Segment Display OC

#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int i;
unsigned char R1 = 0, R2 = 0;

void segchar(unsigned char seg)
{
	//    1 2 3 4 5 6 7 8
	//0b|dp|g|f|e|d|c|b|a|
	
	switch (seg)
	{
		case 1:	PORTD = 0b00000110; break;
		case 2:	PORTD = 0b01011011;	break;
		case 3:	PORTD = 0b01001111;	break;
		case 4:	PORTD = 0b01100110;	break;
		case 5:	PORTD = 0b01101101;	break;
		case 6:	PORTD = 0b01111101;	break;
		case 7:	PORTD = 0b00000111;	break;
		case 8:	PORTD = 0b01111111;	break;
		case 9:	PORTD = 0b01101111;	break;
		case 0:	PORTD = 0b00111111;	break;
	}
}

void timer_ini(void)
{
	TCCR1B |= (1 << WGM12); //CTC mode (compare mode)
	TIMSK |= (1 << OCIE1A); //bit for allowing interruption of the first counter by matching OCR1A(H and L)
	
	OCR1AH = 0b00001111;
	OCR1AL = 0b01000010;

	TCCR1B |= (1 << CS11);//set divider 8
}

unsigned char n_count = 0;

ISR (TIMER1_COMPA_vect)
{
	
	if (n_count == 0) {PORTB &= ~(1 << PINB0); PORTB |= (1 << PINB1); segchar(R1);}
	if (n_count == 1) {PORTB &= ~(1 << PINB1); PORTB |= (1 << PINB0); segchar(R2);}

	n_count++;
	
	if (n_count > 1) n_count = 0;
}

void ledprint(unsigned int number)
{
	R1 = number / 10;
	R2 = number % 10;
}

int main(void)
{
	unsigned char butcount = 0, butstate = 0;
	
	timer_ini();
	
	DDRD = 0xFF; // output
	DDRB = 0b00001111;
	
	PORTD = 0b00000000;
	PORTB = 0b00100000; // pull-up resistor on pin0

	sei(); // set global interruption

	//ledprint(97);

	while (1)
	{
		for (i = 0; i < 100; i++)
		{
			while (butstate == 0)
			{
				if (!(PINB & 0b00100000))
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
			
			ledprint(i);
			_delay_ms(500);
			butstate = 0;
		}
	}
}




