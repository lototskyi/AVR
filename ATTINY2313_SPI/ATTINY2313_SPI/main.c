#include "main.h"


void port_ini(void) {
    PORTD = 0x00;
    DDRD = 0xFF;
}

void SPI_init()
{
    DDRB |= ((1 << PB4) | (1 << PB6) | (1 << PB7)); //USI pins output mode
    DDRB &= ~(1 << PB5); //DI
    PORTB &= ~((1 << PB4) | (1 << PB6) | (1 << PB7));
}

char SPI_ExchangeByte(char byte) 
{
    USIDR = byte; //USI data register
    USISR |= (1 << USIOIF); //clear the counter interrupt flag
    
    while(!(USISR & (1 << USIOIF))) {
        USICR |= ((1 << USIWM0) | (1 << USICS1) | (1 << USICLK) | (1 << USITC)); //send byte
        _delay_us(10);
    }
    
    return USIDR;
}

int main(void)
{
    char str[4];
    unsigned char n = 0, m = 0;
    
    port_ini();
    LCD_ini();
    
    SPI_init();
    
    setPos(0, 0);
    strLCD("Hello World!");

    _delay_ms(1000);

    setPos(2, 1);
    strLCD("String 2");
    
    _delay_ms(1000);
    
    while (1)
    {
        clearLCD();
        setPos(0, 0);
        
        n = (unsigned char)rand() % 256;
        
        m = SPI_ExchangeByte(n);
        
        itoa(n, str, 10);
        strLCD(str);
        
        setPos(0, 1);
        itoa(m, str, 10);
        strLCD(str);
        
        _delay_ms(1000);
    }
}

