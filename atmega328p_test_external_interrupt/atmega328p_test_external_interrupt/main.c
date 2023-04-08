#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (INT0_vect) 
{
    PORTB |= (1 << PB1);
    _delay_ms(200);
    PORTB &= ~(1 << PB1);
    _delay_ms(200);
    PORTB |= (1 << PB1);
    _delay_ms(200);
    PORTB &= ~(1 << PB1);
    _delay_ms(200);
}

int main(void)
{
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
    DDRB |= (1 << PB1); 
    PORTB &= ~(1 << PB1);
    
    sei();
    
    while (1) 
    {
    }
}

