#include "main.h"

extern uint8_t digits[];

void portInit()
{
    DDRB |= (1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0);
    PORTB &= ~((1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0));
    sendCommand(0x89); //Display control //Set the pulse width to 14/16 //Display ON
    reset();
}

void showNumber(int num) 
{
    uint8_t d1 = num % 10;
    uint8_t d2 = num / 10 % 100;

    STB_DOWN;
    shiftOut(0xCE);
    shiftOut(digits[d1]);
    STB_UP;

    STB_DOWN;
    shiftOut(0xCE - 2);
    shiftOut(digits[d2]);
    STB_UP;
    
}


int main(void)
{
    portInit();

    int j = 0;

    while (1) 
    {
        sendCommand(0x44);
        
        for (int i = 1; i <= 16; i = i+2) {
            
            STB_DOWN;
            shiftOut(0xC0 + i);
            shiftOut(0x01);
            STB_UP;
            
            _delay_ms(200);
        }
        
        //STB_DOWN;
        //shiftOut(0xCE);
        //shiftOut(digits[j]);
        //STB_UP;
        
        showNumber(j);
        
        j++;
        
        if (j > 99) {
            j = 0;
        }
        
        clearLed();
        _delay_ms(100);
    }
}

