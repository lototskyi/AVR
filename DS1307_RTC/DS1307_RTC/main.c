#include "main.h"

unsigned char sec, min, hour, day, date, month, year;

int main(void)
{
	I2C_Init();
	USART_ini(8);
	
	// set time
	//I2C_StartCondition();
	//I2C_SendByte(0b11010000);
	//I2C_SendByte(0); //go to address 0x00
	//I2C_SendByte(RTC_ConvertFromBinDec(0)); //sec
	//I2C_SendByte(RTC_ConvertFromBinDec(18)); //min
	//I2C_SendByte(RTC_ConvertFromBinDec(21)); //hour
	//I2C_SendByte(RTC_ConvertFromBinDec(2)); //day of week
	//I2C_SendByte(RTC_ConvertFromBinDec(14)); //date
	//I2C_SendByte(RTC_ConvertFromBinDec(3)); //month
	//I2C_SendByte(RTC_ConvertFromBinDec(23)); //year
	//I2C_StopCondition();
	
    while (1) 
    {
		//read time
		
		I2C_SendByteByADDR(0, 0b11010000); // got to address 0x00
		_delay_ms(500);
		
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
		
		sec = RTC_ConvertToDec(sec);
		min = RTC_ConvertToDec(min);
		hour = RTC_ConvertToDec(hour);
		day = RTC_ConvertToDec(day);
		date = RTC_ConvertToDec(date);
		month = RTC_ConvertToDec(month);
		year = RTC_ConvertToDec(year);
		
		USART_Transmit(date / 10 + 0x30); //transform numbers to code of numbers
		USART_Transmit(date % 10 + 0x30);
		USART_Transmit(".");
		USART_Transmit(month / 10 + 0x30);
		USART_Transmit(month % 10 + 0x30);
		USART_Transmit(".");
		USART_Transmit(year / 10 + 0x30);
		USART_Transmit(year % 10 + 0x30);
		USART_Transmit(' ');
		USART_Transmit('-');
		USART_Transmit(day+0x30);
		USART_Transmit('-');
		USART_Transmit(' ');
		USART_Transmit(' ');
		USART_Transmit(hour / 10 + 0x30);
		USART_Transmit(hour % 10 + 0x30);
		USART_Transmit(':');
		USART_Transmit(min / 10 + 0x30);
		USART_Transmit(min % 10 + 0x30);
		USART_Transmit(':');
		USART_Transmit(sec / 10 + 0x30);
		USART_Transmit(sec % 10 + 0x30);
		USART_Transmit(0x0d); //go to start of the string
		USART_Transmit(0x0a); //carriage return
    }
}

