#include "button.h"

extern unsigned int button_cnt;
extern unsigned char clockeditmode, clockincmode, alarmbeep;
unsigned char buttonstat = 0, cnt = 0;

#define MODENONEEDIT 0
#define MODEHOUREDIT 1
#define MODEMINEDIT 2
#define MODESECEDIT 3
#define MODEDATEEDIT 4
#define MODEMONTHEDIT 5
#define MODEYEAREDIT 6
#define MODEDAYEDIT 7
#define MODEALARMHOUREDIT 8
#define MODEALARMMINEDIT 9

#define MODEINC 201;
#define MODENOINC 202;

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
    if (buttonstat == 1) {
        cnt++;
    }
    
    if (cnt > 30) {
        buttonstat = 0;
        cnt = 0;
    }
    
    if (!(BUTTONPIN & (1 << BUTTONPIN1)) && (buttonstat == 0)) {
        button_cnt++;
    } else {
        
        if (button_cnt > 3 && button_cnt <= 60) { //debouncing
            clockincmode = MODEINC;
            
            if (clockeditmode == MODENONEEDIT) {
                alarmbeep = 0; //alarm off
            }
        }
        
        button_cnt = 0;
    }
    
    
    if (button_cnt > 60) {
        
        if (clockeditmode < MODEALARMMINEDIT) {
            clockeditmode++;
        } else {
            clockeditmode = MODENONEEDIT;
        }
        
        clockincmode = MODENOINC;
        
        button_cnt = 0;
        
        buttonstat = 1;
    }
    
    
}