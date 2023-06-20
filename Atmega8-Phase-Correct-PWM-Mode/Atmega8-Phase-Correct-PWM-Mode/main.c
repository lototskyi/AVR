#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << CS10);
    
    OCR1A = 511;
    
    DDRB |= (1 << PORTB1) | (1 << PORTB2);
   
    DDRC &= ~((1 << PORTC0) | (1 << PORTC1));
    PORTC |= (1 << PORTC0) | (1 << PORTC1);
    
    while (1)
    {
        if (~PINC & (1 << PORTC0)) {
            OCR1A += 5;
            _delay_ms(200);
            
            if (OCR1A >= 1018) {
                OCR1A = 511;
            }
        }
        
        if (~PINC & (1 << PORTC1)) {
            OCR1A -= 5;
            _delay_ms(200);
            
            if (OCR1A <= 6) {
                OCR1A = 511;
            }
        }
    }
}

