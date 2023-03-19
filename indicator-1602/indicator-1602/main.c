#include "main.h"


void port_ini(void) {
	PORTD = 0x00;
	DDRD = 0xFF;
}

int main(void)
{
	port_ini();
	LCD_ini();
	
	setPos(0, 0);
	strLCD("Hello World!");

	setPos(2, 1);
	strLCD("String 2");
	while (1)
	{
		
	}
}

