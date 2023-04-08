#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdbool.h>

//uint16_t counter = 0;
//bool on = false;

//ISR(TIMER1_COMPA_vect) {
//
////PORTB |= (1 << PINB1);
////_delay_ms(300);
////PORTB &= ~(1 << PINB1);
////_delay_ms(300);
//
////if (counter == 0) {
////PORTB |= (1 << PINB1);
////counter++;
////on = true;
////} else if (counter == 30) {
////PORTB &= ~(1 << PINB1);
////counter--;
////on = false;
////} else if (counter > 0 && on == true) {
////counter++;
////} else {
////counter--;
////}
//
//}

//unsigned char n_count = 0;
//
//ISR (TIMER1_COMPA_vect)
//{
//if (n_count == 0) {
//PORTB |= (1 << PINB1);
//}
//
//if (n_count == 100) {
//PORTB &= ~(1 << PINB1);
//}
//
//n_count++;
//
//if (n_count > 100) n_count = 0;
//}

int main(void)
{
    DDRB |= (1 << PINB1) | (1 << PINB4);
    PORTB &= ~(1 << PINB1);
    
    TCCR1 |= (1 << PWM1A) | (1 << COM1A1) | (1 << COM1A0);
    //TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10); // prescale 16384
    GTCCR |= (1 << PWM1B) | (1 << COM1B1) | (1 << COM1B0); // PWM on OC1B
    TCCR1 |= (1 << CS11) | (1 << CS10); // prescale 64
    TCNT1 = 0;
    //TIMSK |= (1 << OCIE1A) | (1 << OCIE1B);
    OCR1A = 159;
    OCR1B = 255;
    
    //sei();
    
    unsigned char pwm_state_a = 0;
    unsigned char pwm_state_b = 1;
    
    /* Replace with your application code */
    while (1)
    {
        
        //PORTB |= (1 << PINB1);
        //_delay_ms(1000);
        //PORTB &= ~(1 << PINB1);
        //_delay_ms(1000);
        
        //if (TCNT1 == 0x7F) {
        //PORTB |= (1 << PINB1);
        //}
        //
        //if (TCNT1 == 0xFF) {
        //PORTB &= ~(1 << PINB1);
        //}
        
        if (pwm_state_a == 0) {
            OCR1A++;
            if (OCR1A > 254) {
                pwm_state_a = 1;
            }
        }
        
        if (pwm_state_a == 1) {
            OCR1A--;
            if (OCR1A < 1) {
                pwm_state_a = 0;
            }
        }
        
        if (pwm_state_b == 1) {
            OCR1B++;
            if (OCR1B > 254) {
                pwm_state_b = 0;
            }
        }
        
        if (pwm_state_b == 0) {
            OCR1B--;
            if (OCR1B < 1) {
                pwm_state_b = 1;
            }
        }
        
        _delay_ms(3);
    }
}

