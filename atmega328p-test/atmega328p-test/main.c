#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


#define beep_on TCCR1B |= (1<<CS11) | (1 << WGM13)
#define beep_off TCCR1B &= ~((1<<CS11) | (1 << WGM13))

int main(void)
{

    DDRB |=  (1 << PORTB1); //Define PORTB1 (PIN15) as Output
    PORTB &= ~(1 << PORTB1);
    DDRD &= ~((1 << PORTD3) | (1 << PORTD4));
    PORTD |= (1 << PORTD3) | (1 << PORTD4);
    TCCR1A |= (1 << COM1A1) | (1 << WGM12) | (1 << WGM11) | (1 << WGM10);  //Set Timer Register
    TCCR1B |= (1 << CS10);
    OCR1A = 0;
    
    unsigned char pwm_state = 0;

    int beep_timer = 0;
    int beep_status = 1;

    while (1) 
    {
        if (pwm_state == 0) {
            OCR1A++;
            if (OCR1A == 1023) {
                pwm_state = 1;
            }
            
        }
        
        if (pwm_state == 1) {
            OCR1A--;
            if (OCR1A == 1) {
                pwm_state = 0;
            }
            
        }            
        
        
		//if (pwm_state == 0) {
    		//OCR1A++;
    		//ICR1 += 2;
    		//_delay_ms(50);
    		//if (ICR1 >= 1500) {
        		//pwm_state = 1;
        		//ICR1 = 350;
    		//}
		//}
		//
		//if (pwm_state == 1) {
    		//OCR1A--;
    		//ICR1 -= 2;
    		//_delay_ms(50);
    		//if (ICR1 <= 6) {
        		//pwm_state = 0;
        		//ICR1 = 350;
    		//}
		//}
		
		_delay_ms(3);
		
		//if (~PIND & (1 << PORTD3)) {
    		//ICR1 += 2;
    		//OCR1A++;
    		//_delay_ms(200);
    		//if (ICR1 >= 1500) OCR1A = 350;
		//}
		//
		//if (~PIND & (1 << PORTD4)) {
    		//ICR1 -= 2;
    		//OCR1A--;
    		//_delay_ms(200);
    		//if (ICR1 <= 6) OCR1A = 350;
		//}
		
        //if (~PIND & (1 << PORTD4)) {
            //
            //if (beep_status == 1) {
                //beep_on;
                //_delay_ms(10);
            //}
//
            //beep_timer++;
            //
            //if (beep_timer > 10) {
                //beep_off;
                //_delay_ms(20);
                //beep_timer = 0;
                //beep_status = 0;
            //}
            //
        //} else {
            //beep_off;
            //beep_timer = 0;
            //beep_status = 1;
        //}
        
    }
}