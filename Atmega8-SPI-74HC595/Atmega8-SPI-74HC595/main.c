#include "main.h"


int main(void)
{
    unsigned int i = 0;
    
    DDRB |= (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5);
    PORTB &= ~((1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5));
    SPCR |= (1 << SPE) | (1 << MSTR); //SPI on, master
    
    SPDR = 0b00000000;
    
    while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    ;
    
    //write to STORAGE REGISTER of 74HC595
    PORTB |= (1 << PORTB2);
    PORTB &= ~((1 << PORTB2));
    _delay_ms(2000);
    
    SPDR = 0b11111111;
    while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    ;
    //write to STORAGE REGISTER of 74HC595
    PORTB |= (1 << PORTB2);
    PORTB &= ~((1 << PORTB2));
    _delay_ms(2000);
    while (1) 
    {
        
        for (i = 0; i < 256; i++) {
            SPDR = i;
            while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
            ;
            
            //write to STORAGE REGISTER of 74HC595
            PORTB |= (1 << PORTB2);
            PORTB &= ~((1 << PORTB2));
            _delay_ms(50);
        }
        
        i = 0;
        
    }
}

