#include "button.h"

extern unsigned int button_cnt;
extern unsigned char clockeditmode;

#define MODENONEEDIT 0
#define MODEMINEDIT 1

void init_button_port()
{
    BUTTONDDR &= ~(1 << BUTTONDDR1);
    BUTTONPORT |= (1 << BUTTONPORT1);
}

void init_button_timer(void) {
    
    TIMSK0 |= (1 << TOIE0);
    TCCR0B |= (1 << CS02) | (1 << CS00);
}

ISR (TIMER0_OVF_vect) 
{
    if(clockeditmode==MODENONEEDIT) {
        
        if (!(BUTTONPIN & (1 << BUTTONPIN1))) {
            button_cnt++;
        } else {
            button_cnt = 0;
        }
        
        if (button_cnt > 60) {
            clockeditmode = MODEMINEDIT;
        }
        
    }
    
    //if (button_cnt < 10000) {
        //button_cnt++;
    //} else {
        //button_cnt = 0;
    //}
}