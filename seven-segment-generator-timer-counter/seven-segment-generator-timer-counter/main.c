//Atmega8
//LED 7-Segment Display OC

#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

unsigned char i;

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
	
	OCR1AH = 0b01111010; //set number for comparing (31250) (8000000 / 32768 = 244.1406 - frequency per second) 
	OCR1AL = 0b00010010; // but CS12 - divider is 256, so 8000000 / 256 = 31250, so we set this number to bits OCR1AH and OCR1AL
	TCCR1B |= (1 << CS12);//set divider
}

ISR (TIMER1_COMPA_vect)
{
	if (i > 9) i = 0;

	segchar(i);
	i++;
}

int main(void)
{
	
	//unsigned char butcount = 0, butstate = 0;
	
	timer_ini();
	
	DDRD = 0xFF; // output
	DDRB = 0x00; // input
	
	PORTD = 0b00000000;
	PORTB = 0b00000001; // pull-up resistor on pin0
	
	i = 0;

	sei(); // set global interruption

	while (1)
	{
		//for (i = 0; i < 10; i++)
		//{
			//while (butstate == 0)
			//{
				//if (!(PINB & 0b00000001))
				//{
					//if (butcount < 5)
					//{
						//butcount++;
					//}
					//else
					//{
						//i = 0;
					//}
					//
				//}
				//else
				//{
					//if (butcount > 0)
					//{
						//butcount--;
					//}
					//else
					//{
						//butstate = 1;
					//}
				//}
			//}
			//
			//segchar(i);
			//_delay_ms(500);
			//butstate = 0;
		//}
	}
}




