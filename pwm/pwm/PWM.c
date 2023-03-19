#include "PWM.h"


void init_PWM_timer(void) {
	
	ASSR = 0x00;
	TCCR2 = 0b01101110; // Fast PWM, Clear OC2 on compare match, clkT2S/256 (From prescaler) (real frequency 8Mhz/256 = 31250Hz)
	TCNT2 = 0x00; // Timer value 0
	OCR2 = 0; // Output compare register = 0, (in our case is a 0% duty cycle)
	TIMSK |= 0x00;//
}