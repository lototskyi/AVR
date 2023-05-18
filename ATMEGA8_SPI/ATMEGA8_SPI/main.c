#include "main.h"

char str[4];

void port_ini(void) {
    PORTD = 0x00;
    DDRD = 0xFF;
}

void SPI_init_SL()
{
    DDRB |= (1 << PB4);
    DDRB &= ~((1 << PB2) | (1 << PB3) | (1 << PB5));
    SPCR |= (1 << SPE) | (1 << SPIE); //SPI on, enable interruption
    sei();
}

ISR(SPI_STC_vect) 
{
    unsigned char n;
    
    n = SPDR;
    
    clearLCD();
    setPos(0, 0);
    itoa(n, str, 10);
    strLCD(str);
    SPDR = n;
}

int main(void)
{
    port_ini();
    LCD_ini();
    SPI_init_SL();
    
    setPos(0, 0);
    strLCD("Hello World!");

    setPos(2, 1);
    strLCD("String 2");
    
    setPos(4, 2);
    strLCD("String 3");
    
    setPos(6, 3);
    strLCD("String 4");
    while (1)
    {
        
    }
}