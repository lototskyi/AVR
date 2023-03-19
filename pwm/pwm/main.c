#include "main.h"

void port_ini(void) {
	PORTB = 0x00;
	DDRB = 0b00001000;
}

int main(void)
{
	unsigned char pwm_state = 0;
	
	port_ini();
	init_PWM_timer();
	
    while (1) 
    {
		
		if (pwm_state == 0) {
			OCR2++;
			if (OCR2 > 254) {
				pwm_state = 1;
			}
		} 
		
		if (pwm_state == 1) {
			OCR2--;
			if (OCR2 < 1) {
				pwm_state = 0;
			}
		}
		
		_delay_ms(3);
		
    }
}

