#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{

    DDRB |=  (1<<PORTB1); //Define PORTB1 (PIN15) as Output
    TCCR1A |= (1<<COM1A1) | (1<<WGM10);  //Set Timer Register
    TCCR1B |= (1<<WGM12) | (1<<CS11);
    OCR1A = 0;
    
    unsigned char pwm_state = 0;

    while (1) 
    {
		if (pwm_state == 0) {
    		OCR1A++;
    		if (OCR1A > 254) {
        		pwm_state = 1;
    		}
		}
		
		if (pwm_state == 1) {
    		OCR1A--;
    		if (OCR1A < 1) {
        		pwm_state = 0;
    		}
		}
		
		_delay_ms(3);
		
    }
}