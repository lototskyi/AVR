//LED 7-Segment Display OC

#include "main.h"

unsigned char sec, min, hour, day, date, month, year;
unsigned int i;

int main(void)
{
    I2C_Init();
    
    timer_ini();
    
    DDRD = 0xFF; // output
    DDRB = 0b00011111;
    DDRC &= ~(1 << DDC3);
    PORTC &= ~(1 << PORTC3);
    PORTD = 0b00000000;
    PORTB = 0b00100000; // pull-up resistor on pin0

    init_PWM_timer();

    sei(); // set global interruption

    OCR2A = 150;

    I2C_StartCondition();
    I2C_SendByte(0b11010000);
    I2C_SendByte(7); //go to address 0x07
    I2C_SendByte(0b00010000); // SQWE on
    I2C_StopCondition();

    while (1)
    {
        //read time
        
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
        
        sec = RTC_ConvertToDec(sec);
        min = RTC_ConvertToDec(min);
        hour = RTC_ConvertToDec(hour);
        day = RTC_ConvertToDec(day);
        date = RTC_ConvertToDec(date);
        month = RTC_ConvertToDec(month);
        year = RTC_ConvertToDec(year);
        
        ledprint(hour * 100 + min);
        _delay_ms(50);
    }
}




