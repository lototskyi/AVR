#include "lcdtwi.h"

unsigned char portlcd = 0; // store port conditions of I2C MCU


void sendHalfByte(unsigned char c) {
	c <<= 4;
	e1;
	_delay_us(50);
	portlcd &= 0b00001111;
	I2C_SendByteByADDR(portlcd |= c, 0b01001110);
	e0;
	_delay_us(50);
}

void sendByte(unsigned char c, unsigned char mode) {
	if (mode == 0) {
		rs0;
	}
	else rs1;
	
	_delay_us(50);

	unsigned char hc = 0;
	hc = c >> 4;
	sendHalfByte(hc); sendHalfByte(c); 
}

void setPos(unsigned char x, unsigned char y ) {
	
	switch(y) {
		case 0:
			sendByte(x | 0x80, 0);
			break;
		case 1:
			sendByte((x + 0x40) | 0x80, 0);
			break;
		case 2:
			sendByte((x + 0x14) | 0x80, 0);
			break;
		case 3:
			sendByte((x + 0x54) | 0x80, 0);
			break;
	}
}

void sendCharLCD(unsigned char c) {
	sendByte(c, 1);
}

void strLCD(char str1[]) {
	wchar_t n;
	
	for (n = 0; str1[n] != '\0'; n++) {
		sendCharLCD(str1[n]);
	}
}

void lcd_num(uint8_t num, uint8_t line, uint8_t pos) {
	char buf[4];
	utoa(num, buf, 10);
	setPos(pos, line);
	strLCD("   ");
	setPos(pos, line);
	strLCD(buf);
}

void LCD_init(void) {
	_delay_ms(20); //waiting

	sendHalfByte(0b00000010); /* send for 4 bit initialization of LCD  */
	_delay_ms(1);
	sendByte(0b00101000, 0); // 4bit mode, 2 lines (N=1)
	_delay_ms(1);
	sendByte(0b00001100, 0); //turn display on (D=1), cursor is off
	_delay_ms(1);
	sendByte(0b00000110, 0); //Increment cursor (shift cursor to right)
	_delay_ms(1);
	sendByte(0b00000001, 0); /* Clear display screen*/
	_delay_ms(2);
	
	backlightOn();
	setwrite();
}

void clearLCD() {
	sendByte(0b00000001, 0);
	_delay_us(1500);
}

void turnBacklightOn()
{
	backlightOn();
}

void turnBacklightOff()
{
	backlightOff();
}
