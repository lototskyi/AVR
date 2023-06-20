#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    TCCR1A |= (1 << COM1A1) | (1 << WGM10) | (1 << WGM11);
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << WGM12) | (1 << CS10);
    
    OCR1A = 999;
    
    DDRB |= (1 << PORTB1) | (1 << PORTB2);
    PORTB &= ~(1 << PORTB1) | (1 << PORTB2);
    
    
    while (1) 
    {
        
    }
}

