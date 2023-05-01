#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
    DDRB = 0xFF;
    
    TCCR0 |= (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS01);
    OCR0 = 0;
    TCNT0 = 0;
    
    unsigned char pwm_state = 0;

    /* Replace with your application code */
    while (1) 
    {
		//PORTA |= (1 << PORTA0);
		//_delay_ms(100);
		//PORTA &= ~(1 << PORTA0);
		//_delay_ms(100);
		//PORTA |= (1 << PORTA0);
		//_delay_ms(100);
		//PORTA &= ~(1 << PORTA0);
		//_delay_ms(100);
		//PORTA |= (1 << PORTA0);
		//_delay_ms(100);
		//PORTA &= ~(1 << PORTA0);
		//_delay_ms(100);
		//PORTA |= (1 << PORTA0);
		//_delay_ms(2000);
		//PORTA &= ~(1 << PORTA0);
		//_delay_ms(2000);
		
        
        if (pwm_state == 0) {
            OCR0++;
            if (OCR0> 254) {
                pwm_state = 1;
            }
        }
        
        if (pwm_state == 1) {
            OCR0--;
            if (OCR0 < 1) {
                pwm_state = 0;
            }
        }
        
        _delay_ms(3);
    }
}

