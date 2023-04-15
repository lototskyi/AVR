#include "PWM.h"


void init_PWM_timer(void) {
	
	ASSR = 0x00;
    
    //Fast PWM, prescaler 8 (real frequency 8Mhz/256 = 31250Hz)
    TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2A &= ~((1 << COM2A0) | (1 << COM2B0) | (1 << COM2B1));
    TCCR2B |= (1 << CS21);
    TCCR2B &= ~((1 << WGM22) | (1 << CS22) | (1 << CS20));
    
	TCNT2 = 0x00; // Timer value 0
	OCR2A = 0; // Output compare register = 0, (in our case is a 0% duty cycle)
	TIMSK2 |= 0x00;//
}