#include "main.h"

unsigned char sec, min, hour, day, date, month, year;

unsigned char counter = 0;
unsigned char butcount = 0;
unsigned char butcount2 = 0;

void setCurrentTime()
{

	I2C_StartCondition();
	I2C_SendByte(0b11010000);
	I2C_SendByte(0); //go to address 0x00
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //sec
	I2C_SendByte(RTC_ConvertFromBinDec(38)); //min
	I2C_SendByte(RTC_ConvertFromBinDec(20)); //hour
	I2C_SendByte(RTC_ConvertFromBinDec(7)); //day of week
	I2C_SendByte(RTC_ConvertFromBinDec(19)); //date
	I2C_SendByte(RTC_ConvertFromBinDec(3)); //month
	I2C_SendByte(RTC_ConvertFromBinDec(23)); //year
	I2C_StopCondition();
	
}

void readTime()
{
	
	I2C_SendByteByADDR(0, 0b11010000); // got to address 0x00
	_delay_ms(100);
	
	I2C_StartCondition();
	I2C_SendByte(0b11010001); //send bit READ
	sec = I2C_ReadByte();
	min = I2C_ReadByte();
	hour = I2C_ReadByte();
	day = I2C_ReadByte();
	date = I2C_ReadByte();
	month = I2C_ReadByte();
	year = I2C_ReadLastByte();
	I2C_StopCondition();
}

void convertTimeStringsToASCIIcodes()
{
	sec = RTC_ConvertToDec(sec);
	min = RTC_ConvertToDec(min);
	hour = RTC_ConvertToDec(hour);
	day = RTC_ConvertToDec(day);
	date = RTC_ConvertToDec(date);
	month = RTC_ConvertToDec(month);
	year = RTC_ConvertToDec(year);
}

void showTimeOnDisplay()
{
	setPos(0, 0);
	
	sendCharLCD(date / 10 + 0x30); //transform numbers to code of numbers
	sendCharLCD(date % 10 + 0x30);
	sendCharLCD('.');
	sendCharLCD(month / 10 + 0x30);
	sendCharLCD(month % 10 + 0x30);
	sendCharLCD('.');
	sendCharLCD('2');
	sendCharLCD('0');
	sendCharLCD(year / 10 + 0x30);
	sendCharLCD(year % 10 + 0x30);
	sendCharLCD(' ');
	sendCharLCD('-');
	sendCharLCD(day+0x30);
	sendCharLCD('-');
	setPos(0, 1);
	sendCharLCD(hour / 10 + 0x30);
	sendCharLCD(hour % 10 + 0x30);
	sendCharLCD(':');
	sendCharLCD(min / 10 + 0x30);
	sendCharLCD(min % 10 + 0x30);
	sendCharLCD(':');
	sendCharLCD(sec / 10 + 0x30);
	sendCharLCD(sec % 10 + 0x30);
}

void incrementMinutes()
{
	turnBacklightOn();
	I2C_StartCondition();
	I2C_SendByte(0b11010000); //write
	I2C_SendByte(0x00);
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //sec
	I2C_StopCondition();
	
	I2C_StartCondition();
	I2C_SendByte(0b11010000); //write
	I2C_SendByte(0x01); //go to address 0x01
	
	min = min + 1;
	
	if (min == 60) min = 0;
	
	I2C_SendByte(RTC_ConvertFromBinDec(min)); //min
	I2C_StopCondition();
}

void buttonClickTurnBacklightOn()
{
	if (!(PIND & 0x80)) {
		if (butcount < 3) {
			butcount++;
		} else {
			counter = 0;
			turnBacklightOn();
		}
		
	} else {
		if (butcount > 0) {
			butcount--;
		}
	}
}

void buttonClickIncrementMinutes()
{
	if (!(PIND & 0x40)) {
		if (butcount2 < 3) {
			butcount2++;
		} else {
			counter = 0;
			incrementMinutes();
		}
		
	} else {
		if (butcount2 > 0) {
			butcount2--;
		}
	}
}

void portInit()
{
	DDRD &= ~((1 << PIND7) | (1 << PIND6)); //set PIND7 and PIND6 to input
	PORTD |= ((1 << PIND7) | (1 << PIND6)); //set pull-up resistor on PIND7 and PIND6
}


int main(void)
{
	//setCurrentTime();
	
	portInit();
	
	I2C_Init();
	LCD_init();
	clearLCD();
	
	while (1)
	{
		
		readTime();
		convertTimeStringsToASCIIcodes();
		showTimeOnDisplay();
		
		buttonClickTurnBacklightOn();
		buttonClickIncrementMinutes();
		
		if (counter == 100) {
			turnBacklightOff();
			counter = 0;
		}

		counter++;

	}
}

