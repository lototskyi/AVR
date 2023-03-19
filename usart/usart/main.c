#include "main.h"

unsigned char x = 0, y = 0;

void port_ini(void) {
	PORTD = 0x00;
	DDRD = 0xFF;
}

ISR(USART_RXC_vect)
{
	int b;
	b = UDR;
	
	setPos(x, y);
	
	sendChar(b);
	
	if (x < 15) {
		x++;
		} else {
		x = 0;
		
		if (y == 0) {
			y = 1;
		} else if (y == 1) {
			y = 0; clearLCD();
		}
	}
}

int main(void)
{
	port_ini();
	LCD_ini();
    sei();
	
	USART_ini(34); //34 is speed 28800 (table in datasheet)
	USART_Transmit('O');
	USART_Transmit('K');
	USART_Transmit('!');
	USART_Transmit(0x0d);
	USART_Transmit(0x0a);

	clearLCD();
	
    while (1) 
    {
		
    }
}

