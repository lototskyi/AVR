#include "lcd.h"


void sendHalfByte(unsigned char c) {
	c <<= 4;
	e1;
	_delay_us(50);
	PORTD &= 0b00001111; //clear data on ports DB4-DB7
	PORTD |= c;
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

void LCD_ini(void) {
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
}

void clearLCD() {
	sendByte(0b00000001, 0);
	_delay_us(1500);
}

void strLCD(char str1[]) {
	wchar_t n;
	
	for (n = 0; str1[n] != '\0'; n++) {
		sendCharLCD(str1[n]);
	}
}

void strLCD80(char str1[]) {
    unsigned char n;
    
    sendByte(0x80, 0); //string 1
    
    for (n = 0; n <= 19; n++) {
        sendCharLCD(str1[n]);
    }
    
    for (n = 40; n <= 59; n++) { //string 3
        sendCharLCD(str1[n]);
    }
    
    sendByte(0xC0, 0); //string 2
    
    for (n = 20; n <= 39; n++) {
        sendCharLCD(str1[n]);
    }
    
    for (n = 60; n <= 79; n++) {
        sendCharLCD(str1[n]);
    }
}

void createCustomCharacter(unsigned char *Pattern, const char Location)
{
    int i=0;
    sendByte(0x40 + (Location * 8), 0); //Send the Address of CGRAM
    for (i=0; i<8; i++)
        sendByte(Pattern[i], 1); //Pass the bytes of pattern on LCD
}
