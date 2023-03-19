#include "main.h"


void showASCIISymbols()
{
	unsigned char i;
	setPos(0, 0);
	for (i = 65; i <= 127; i++)  {
		
		if (i == 84) {
			sendChar(i);
			setPos(0, 1);
		} else if (i == 104) {
			sendChar(i);
			setPos(0, 2);
		} else if (i == 124) {
			sendChar(i);
			setPos(0, 3);
		} else {
			sendChar(i);
		}
		
		_delay_ms(400);
	}
}

int main(void)
{
	I2C_Init();
	LCD_init();
	
	clearLCD();
	
	//setPos(0, 0);
	//strLCD("Counter: ");
//
	//setPos(2, 1);
	//strLCD("String 2");
	
	uint8_t count = 0;
	
	showASCIISymbols();
	
	while (1)
	{
		//_delay_ms(500);
		//count++;
		//lcd_num(count, 0, 9);
	}
}

