/*
The lib is useful for the LED&KEY board based on TM1638
*/

#ifndef TM1638_H_
#define TM1638_H_

#include "main.h"

// Main Settings
#define	TM1638_DIO_PIN			    PB0
#define	TM1638_CLK_PIN			    PB1
#define	TM1638_STB_PIN			    PB2
#define	TM1638_DELAY_US			    (5)
#define	TM1638_MAX_BRIGHTNESS		0x07
#define TM1638_PORT                 PORTB
#define TM1638_PIN                  PINB
#define TM1638_DDR                  DDRB

// TM1638 commands
#define	TM1638_CMD_SET_DATA		    0x40
#define	TM1638_CMD_SET_ADDR		    0xC0
#define	TM1638_CMD_SET_DSIPLAY		0x80

// TM1638 data settings (use bitwise OR to construct complete command)
#define	TM1638_SET_DATA_WRITE		0x00 // write data to the display register
#define	TM1638_SET_DATA_READ		0x02 // read the key scan data
#define	TM1638_SET_DATA_A_ADDR		0x00 // automatic address increment
#define	TM1638_SET_DATA_F_ADDR		0x04 // fixed address
#define	TM1638_SET_DATA_M_NORM		0x00 // normal mode
#define	TM1638_SET_DATA_M_TEST		0x10 // test mode

// TM1638 display control command set (use bitwise OR to construct complete command)
#define	TM1638_SET_DISPLAY_OFF		0x00 // off
#define	TM1638_SET_DISPLAY_ON		0x08 // on

//#define DATAPIN PINB
//#define PORT PORTB
//#define PORTDDR DDRB
//#define DIO PORTB0
//#define CLK PORTB1
//#define STB PORTB2

#define STB_HIGH PORTB |= (1 << TM1638_STB_PIN)
#define STB_LOW PORTB &= ~(1 << TM1638_STB_PIN)

void shiftOut(char value);
void sendCommand(char value);
void clearDisplay();
void sendDataByAddr(int8_t addr, int8_t data);
void clearLed();
int8_t readButtons();


#endif /* TM1638_H_ */