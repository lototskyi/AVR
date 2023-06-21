#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    TCCR1A |= (1 << COM1A1);// | (1 << COM1A0);
    TCCR1B |= (1 << CS10) | (1 << WGM13);
    
    OCR1A = 500;
    ICR1 = 1000;
    
    DDRB |= (1 << PORTB1) | (1 << PORTB2);
    
    DDRC &= ~((1 << PORTC0) | (1 << PORTC1));
    PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);
    
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
        
        if (~PINC & (1 << PORTC2)) {
            
            ICR1 += 2;
            OCR1A += 1;
            _delay_ms(50);
            
            if (ICR1 >= 1500) {
                ICR1 = 1000;
                OCR1A = 500;
            }
        }
        
        if (~PINC & (1 << PORTC3)) {
            ICR1 -= 2;
            OCR1A -= 1;
            _delay_ms(50);
            
            if (ICR1 <= 6) {
                ICR1 = 1000;
                OCR1A = 500;
            }
        }
    }
}


