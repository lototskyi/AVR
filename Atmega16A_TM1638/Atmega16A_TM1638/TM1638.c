#include "TM1638.h"

                    /*0*/ /*1*/ /*2*/ /*3*/ /*4*/ /*5*/ /*6*/ /*7*/ /*8*/ /*9*/
uint8_t digits[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };

void shiftOut(char value)
{
    char bt;
    for(char i = 0; i < 8; i++) {
        bt = value & 1;
        
        if (bt) {
            PORTB |= (1 << DIO);
            } else {
            PORTB &= ~(1 << DIO);
        }
        
        value >>= 1;
        PORTB |= (1 << CLK);
        _delay_us(1);
        PORTB &= ~(1 << CLK);
        _delay_us(1);
    }
}

void sendCommand(char value)
{
    STB_DOWN;
    shiftOut(value);
    STB_UP;
    _delay_us(1);
}

void clearDisplay()
{
    sendCommand(0x40); //Setting of Data Command,// Write data to the display register,// Set address to Auto increment, Normal mode
    STB_DOWN;
    for (char i = 0; i < 16; i++) {
        shiftOut(0x00);
    }
    STB_UP;
}

void clearLed()
{
    sendCommand(0x44); //Setting of Data Command,// Write data to the display register,// Normal mode
    
    for (char i = 1; i < 16; i += 2) {
        STB_DOWN;
        shiftOut(0xC0 + i);
        shiftOut(0x00);
        STB_UP;
    }
}

void reset()
{
    clearDisplay();
    
    sendCommand(0x44); //Setting of Data Command //Normal mode //Write data to the display register //Fixed address
    
    STB_DOWN;
    shiftOut(0xc0);

    shiftOut(digits[0]);

    STB_UP;
}