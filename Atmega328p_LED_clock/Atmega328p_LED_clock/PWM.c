#include "PWM.h"


void init_PWM_timer(void) {
	
	ASSR = 0x00;
    
    //Fast PWM
    TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2A &= ~((1 << COM2A0) | (1 << COM2B0) | (1 << COM2B1));
    TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20); //32
    TCCR2B &= ~(1 << WGM22);
    
	TCNT2 = 0x00; // Timer value 0
	OCR2A = 10;
	TIMSK2 |= 0x00;//
}