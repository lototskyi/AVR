#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define timer_on TCCR1B |= (1 << CS12) | (1 << CS10);
#define timer_off TCCR1B &= ~((1 << CS12) | (1 << CS10));

ISR (TIMER1_OVF_vect) {
    timer_off;
    PORTC |= (1 << PC5);
    _delay_ms(150);
    PORTC &= ~(1 << PC5);
    _delay_ms(100);
    timer_on;
}

int main(void)
{
    DDRC = 0xFF;
    PORTC = 0x00;
    
    timer_on;
    TIMSK1 |= (1 << TOIE1);
    TCNT1 = 0;
    sei();
    while (1) 
    {
        for (int i = 0; i < 4; i++) {
            PORTC |= (1 << i);
            _delay_ms(150);
            PORTC &= ~(1 << i);
        }
        _delay_ms(3);
    }
}

