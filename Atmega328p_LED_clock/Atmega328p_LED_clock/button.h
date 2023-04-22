#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

#define BUTTONPORT PORTB
#define BUTTONPORT1 PORTB5
#define BUTTONPIN PINB
#define BUTTONPIN1 PINB5
#define BUTTONDDR DDRB
#define BUTTONDDR1 DD5

void init_button_timer(void);
void init_button_port();

#endif /* BUTTON_H_ */