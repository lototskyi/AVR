#include "main.h"

void SPI_init() {
    DDRB |= (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5);
    PORTB &= ~((1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5));
    SPCR |= (1 << SPE) | (1 << MSTR); //SPI on, master
}

int main(void)
{
    
    unsigned int i = 0;
    
    SPI_init();
    timer_init();
    sei();
    
    //SPDR = 0b00000000;
    //
    //while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    //;
    
    SPDR = 0b00000000;
    
    while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    ;
    
    //write to STORAGE REGISTER of 74HC595
    PORTB |= (1 << PORTB2);
    PORTB &= ~((1 << PORTB2));
    _delay_ms(500);

    while (1)
    {
        for (i = 0; i < 10000; i++) {
            ledprint(i);
            _delay_ms(10);
        }
    }
}




