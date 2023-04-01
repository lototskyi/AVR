#include "main.h"

#define BUTTONPORT PORTC
#define BUTTONPORT0 PORTC0
#define BUTTONPORT1 PORTC1
#define BUTTONPORT2 PORTC2
#define BUTTONPORT3 PORTC3

#define BUTTONPIN PINC
#define BUTTONPIN0 PINC0
#define BUTTONPIN1 PINC1
#define BUTTONPIN2 PINC2
#define BUTTONPIN3 PINC3

#define BUTTONDDR DDRC
#define BUTTONDDR0 DDC0
#define BUTTONDDR1 DDC1
#define BUTTONDDR2 DDC2
#define BUTTONDDR3 DDC3

#define CLOCKMODE0 0 //mode of showing time
#define CLOCKMODEDATE 1
#define CLOCKMODEMONTH 2
#define CLOCKMODEYEAR 3
#define CLOCKMODEDAY 4
#define CLOCKMODEHOUR 5
#define CLOCKMODEMIN 6
#define CLOCKMODESEC 7

unsigned char sec, min, hour, day, date, month, year;

unsigned char counter = 0;
unsigned char butcount = 0;
unsigned char butcount2 = 0;

unsigned int ch = 0;
unsigned int tt = 0;
unsigned int dt = 0;

unsigned char button1state = 0; //state of button 1
unsigned char clockmode = CLOCKMODE0;
char blinkstate = 0;

//void setCurrentTime()
//{
//
//I2C_StartCondition();
//I2C_SendByte(0b11010000);
//I2C_SendByte(0); //go to address 0x00
//I2C_SendByte(RTC_ConvertFromBinDec(0)); //sec
//I2C_SendByte(RTC_ConvertFromBinDec(00)); //min
//I2C_SendByte(RTC_ConvertFromBinDec(22)); //hour
//I2C_SendByte(RTC_ConvertFromBinDec(2)); //day of week
//I2C_SendByte(RTC_ConvertFromBinDec(21)); //date
//I2C_SendByte(RTC_ConvertFromBinDec(3)); //month
//I2C_SendByte(RTC_ConvertFromBinDec(23)); //year
//I2C_StopCondition();
//
//}

void readTime()
{
    
    I2C_SendByteByADDR(0, 0b11010000); // got to address 0x00
    _delay_ms(1);
    
    I2C_StartCondition();
    I2C_SendByte(0b11010001); //send bit READ
    sec = I2C_ReadByte();
    min = I2C_ReadByte();
    hour = I2C_ReadByte();
    day = I2C_ReadByte();
    date = I2C_ReadByte();
    month = I2C_ReadByte();
    year = I2C_ReadLastByte();
    I2C_StopCondition();
}

void convertTimeStringsToASCIIcodes()
{
    sec = RTC_ConvertToDec(sec);
    min = RTC_ConvertToDec(min);
    hour = RTC_ConvertToDec(hour);
    day = RTC_ConvertToDec(day);
    date = RTC_ConvertToDec(date);
    month = RTC_ConvertToDec(month);
    year = RTC_ConvertToDec(year);
}

void turnBacklightOnAndResetCounter()
{
    counter = 0;
    turnBacklightOn();
}

char buttonProcess(char buttonpin, int type)
{
    char result = 0, buttonCount = 0, buttonState = 0;
    
    while (buttonState == 0) {
        if (!(BUTTONPIN & (1 << buttonpin))) {
            turnBacklightOnAndResetCounter();
            if (buttonCount < 5) {
                buttonCount++;
            } else {
                result = type;
                buttonState = 1;
            }
            
        } else {
            if (buttonCount > 0) {
                buttonCount--;
            } else {
                buttonState = 1;
            }
        }
    }
    
    return result;
}

char buttonPress (char index)
{
    char result = 0;
    
    switch (index) {
        case 1:
            result = buttonProcess(BUTTONPIN1, 1);
            break;
        case 2:
            result = buttonProcess(BUTTONPIN2, 2);
            break;
        case 3:
            result = buttonProcess(BUTTONPIN3, 3);
            break;
        case 4:
            result = buttonProcess(BUTTONPIN0, 4); 
    }
    
    return result;
}

void ModifyRTC(char index, char direction)
{
    I2C_StartCondition();
    I2C_SendByte(0b11010000);
    
    switch (index) {
        case 1: //date
            I2C_SendByte(4); //go to address 0x04
            if (direction == 1) {
                if (month == 2) { //Feb
                    if (year % 4 == 0) { // a leap year
                        if (date < 29) {
                            I2C_SendByte(RTC_ConvertFromBinDec(date + 1));
                        } else {
                            I2C_SendByte(RTC_ConvertFromBinDec(1));
                        }
                    } else {
                        if (date < 28) {
                            I2C_SendByte(RTC_ConvertFromBinDec(date + 1));
                        } else {
                            I2C_SendByte(RTC_ConvertFromBinDec(1));
                        }
                    }
                } else if ((month == 4) | (month == 6) | (month == 9) | (month == 11)) {
                    if (date < 30) {
                        I2C_SendByte(RTC_ConvertFromBinDec(date + 1));
                    } else {
                        I2C_SendByte(RTC_ConvertFromBinDec(1));
                    }
                } else {
                    if (date < 31) {
                        I2C_SendByte(RTC_ConvertFromBinDec(date + 1));
                    } else {
                        I2C_SendByte(RTC_ConvertFromBinDec(1));
                    }
                }
            }
        
            if (direction == 0) {
                if (month == 2) { //Feb
                    if (year % 4 == 0) { // a leap year
                        if (date > 1) {
                            I2C_SendByte(RTC_ConvertFromBinDec(date - 1));
                        } else {
                            I2C_SendByte(RTC_ConvertFromBinDec(29));
                        }
                    } else {
                        if (date > 1) {
                            I2C_SendByte(RTC_ConvertFromBinDec(date - 1));
                        } else {
                            I2C_SendByte(RTC_ConvertFromBinDec(28));
                        }
                    }
                } else if ((month == 4) | (month == 6) | (month == 9) | (month == 11)) {
                    if (date > 1) {
                        I2C_SendByte(RTC_ConvertFromBinDec(date - 1));
                    } else {
                        I2C_SendByte(RTC_ConvertFromBinDec(30));
                    }
                } else {
                    if (date > 1) {
                        I2C_SendByte(RTC_ConvertFromBinDec(date - 1));
                    } else {
                        I2C_SendByte(RTC_ConvertFromBinDec(31));
                    }
                }
            }
            break;
        case 2: //month
        
            I2C_SendByte(5);
        
            if (direction == 1) {
                if (month < 12) {
                    I2C_SendByte(RTC_ConvertFromBinDec(month + 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(1));
                }
            }
        
            if (direction == 0) {
                if (month > 1) {
                    I2C_SendByte(RTC_ConvertFromBinDec(month - 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(12));
                }
            }
        
            break;
        case 3: //year
        
            I2C_SendByte(6);
        
            if (direction == 1) {
                if (year < 99) {
                    I2C_SendByte(RTC_ConvertFromBinDec(year + 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(1));
                }
            }
        
            if (direction == 0) {
                if (year > 1) {
                    I2C_SendByte(RTC_ConvertFromBinDec(year - 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(99));
                }
            }
        
            break;
        case 4: //day
        
            I2C_SendByte(3);
            
            if (direction == 1) {
                if (day < 7) {
                    I2C_SendByte(RTC_ConvertFromBinDec(day + 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(1));
                }
            }
            
            if (direction == 0) {
                if (day > 1) {
                    I2C_SendByte(RTC_ConvertFromBinDec(day - 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(7));
                }
            }
            
            break;
        case 5: //hours
        
            I2C_SendByte(2);
            
            if (direction == 1) {
                if (hour < 23) {
                    I2C_SendByte(RTC_ConvertFromBinDec(hour + 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(0));
                }
            }
            
            if (direction == 0) {
                if (hour > 0) {
                    I2C_SendByte(RTC_ConvertFromBinDec(hour - 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(23));
                }
            }
            
            break;
        case 6: //mins
        
            I2C_SendByte(1);
            
            if (direction == 1) {
                if (min < 59) {
                    I2C_SendByte(RTC_ConvertFromBinDec(min + 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(0));
                }
            }
            
            if (direction == 0) {
                if (min > 0) {
                    I2C_SendByte(RTC_ConvertFromBinDec(min - 1));
                } else {
                    I2C_SendByte(RTC_ConvertFromBinDec(59));
                }
            }
            
            break;
        case 7: //sec
        
            I2C_SendByte(0);
        
            if (direction == 1) { //reset sec to 0
                I2C_SendByte(RTC_ConvertFromBinDec(0));
            }
        
            if (direction == 0) { //reset sec to 30
                I2C_SendByte(RTC_ConvertFromBinDec(30));
            }
        
            break;
        
    }

    I2C_StopCondition();
}

void setClockModeAndButtonState(unsigned char clockmode1, unsigned char clockmode2) 
{
    if (buttonPress(1) == 1) {
        
        if (button1state == 0) { //get status not to go to month change mode
            clockmode = clockmode1; //month change mode
            button1state = 1;
        }
    }
    
    if (clockmode == clockmode2) {
        button1state = 0;
    }

}

void showTimeOnDisplay()
{
    setPos(0, 0);
    
    if (buttonPress(1) == 1) {// Button 1 is pressed
        
        if (clockmode == CLOCKMODE0) {
            clockmode = CLOCKMODEDATE; //set date mode
            
            blinkstate = 0;
            button1state = 1;
        }
        
    }
    
    if (clockmode != CLOCKMODEDATE) {
        sendCharLCD(date / 10 + 0x30); //transform numbers to code of numbers
        sendCharLCD(date % 10 + 0x30);
    } else { //DATE
        
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD(date / 10 + 0x30); //transform numbers to code of numbers
            sendCharLCD(date % 10 + 0x30);
            blinkstate = 0;
        }

        setClockModeAndButtonState(CLOCKMODEMONTH, CLOCKMODEDATE);
        
        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(1, 0); // 1 - date; 0 - go back
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(1, 1); // 1 - date; 1 - go forward
        }
    }
    
    sendCharLCD('.');
    
    if (clockmode != CLOCKMODEMONTH) {
        sendCharLCD(month / 10 + 0x30);
        sendCharLCD(month % 10 + 0x30);
    } else {
      
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD(month / 10 + 0x30);
            sendCharLCD(month % 10 + 0x30);
            blinkstate = 0;
        }

        setClockModeAndButtonState(CLOCKMODEYEAR, CLOCKMODEMONTH);
        
        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(2, 0); // 2 - month; 0 - go back
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(2, 1); // 2 - month; 1 - go forward
        }
        
    }
    
    
    sendCharLCD('.');
    
    if (clockmode != CLOCKMODEYEAR) {
        sendCharLCD('2');
        sendCharLCD('0');
        sendCharLCD(year / 10 + 0x30);
        sendCharLCD(year % 10 + 0x30);
    } else { //YEAR
        
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD('2');
            sendCharLCD('0');
            sendCharLCD(year / 10 + 0x30);
            sendCharLCD(year % 10 + 0x30);
            blinkstate = 0;
        }

        setClockModeAndButtonState(CLOCKMODEDAY, CLOCKMODEYEAR);

        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(3, 0); // 3 - year; 0 - go back
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(3, 1); // 3 - year; 1 - go forward
        }
        
    }
    
    sendCharLCD(' ');
    
    if (clockmode != CLOCKMODEDAY) {
        sendCharLCD('-');
        sendCharLCD(day + 0x30);
        sendCharLCD('-');
    } else { //DAY OF WEEK
        
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD('-');
            sendCharLCD(day + 0x30);
            sendCharLCD('-');
            blinkstate = 0;
        }
        
        setClockModeAndButtonState(CLOCKMODEHOUR, CLOCKMODEDAY);

        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(4, 0); // 4 - day of week; 0 - go back
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(4, 1); // 4 - day of week; 1 - go forward
        }
        
    }
    
    setPos(0, 1);
    
    if (clockmode != CLOCKMODEHOUR) {
        sendCharLCD(hour / 10 + 0x30);
        sendCharLCD(hour % 10 + 0x30);
    } else { //HOUR
        
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD(hour / 10 + 0x30);
            sendCharLCD(hour % 10 + 0x30);
            blinkstate = 0;
        }

        setClockModeAndButtonState(CLOCKMODEMIN, CLOCKMODEHOUR);
        
        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(5, 0); // 5 - hours; 0 - go back
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(5, 1); // 5 - hours; 1 - go forward
        }
        
    }
    
    sendCharLCD(':');

    if (clockmode != CLOCKMODEMIN) {
        sendCharLCD(min / 10 + 0x30);
        sendCharLCD(min % 10 + 0x30);
    } else { //MIN
        
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD(min / 10 + 0x30);
            sendCharLCD(min % 10 + 0x30);
            blinkstate = 0;
        }
        
        setClockModeAndButtonState(CLOCKMODESEC, CLOCKMODEMIN);

        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(6, 0); // 6 - mins; 0 - go back
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(6, 1); // 6 - mins; 1 - go forward
        }
        
    }

    sendCharLCD(':');

    if (clockmode != CLOCKMODESEC) {
        sendCharLCD(sec / 10 + 0x30);
        sendCharLCD(sec % 10 + 0x30);
    } else { //SEC
        
        if (blinkstate == 0) {
            sendCharLCD(' ');
            sendCharLCD(' ');
            blinkstate = 1;
        } else {
            sendCharLCD(sec / 10 + 0x30);
            sendCharLCD(sec % 10 + 0x30);
            blinkstate = 0;
        }
        
        setClockModeAndButtonState(CLOCKMODE0, CLOCKMODESEC);

        if (buttonPress(2) == 2) { //button 2
            ModifyRTC(7, 0); // 7 - sec; 0 - set 30
        }
        if (buttonPress(3) == 3) { //button 3
            ModifyRTC(7, 1); // 7 - sec; 1 - set 0
        }
        
    }
    
    ch = dt_check();
    
    tt = convertTemp(ch); //get temp int
    dt = getDecimalTemp(ch); //get temp dec
    
    sendCharLCD(' ');
    sendCharLCD(tt / 10 + 0x30);
    sendCharLCD(tt % 10 + 0x30);
    sendCharLCD(',');
    sendCharLCD(dt / 10 + 0x30);
    sendCharLCD(dt % 10 + 0x30);
    sendCharLCD('*');
    sendCharLCD('C');
}


void buttonClickTurnBacklightOn()
{
    if (!(PIND & 0x80)) {
        if (butcount < 3) {
            butcount++;
        } else {
            counter = 0;
            turnBacklightOn();
        }
        
    } else {
        
        if (butcount > 0) {
            butcount--;
        }
    }
}


void portInit()
{
    DDRD &= ~((1 << PIND7) | (1 << PIND6)); //set PIND7 and PIND6 to input
    PORTD |= ((1 << PIND7) | (1 << PIND6)); //set pull-up resistor on PIND7 and PIND6
    
    BUTTONDDR &= ~((1 << BUTTONDDR3) | (1 << BUTTONDDR2) | (1 << BUTTONDDR1) | (1 << BUTTONDDR0));
    BUTTONPORT |= ((1 << BUTTONPORT3) | (1 << BUTTONPORT2) | (1 << BUTTONPORT1) | (1 << BUTTONPORT0));
}


int main(void)
{
    //setCurrentTime();
    
    portInit();
    I2C_Init();
    LCD_init();
    clearLCD();
    
    while (1)
    {
        
        readTime();
        convertTimeStringsToASCIIcodes();
        showTimeOnDisplay();
        
        buttonClickTurnBacklightOn();
        
        if (buttonPress(4) == 4) {
            turnBacklightOn();
            counter = 0;
        }

        if (counter == 100) {
            turnBacklightOff();
            counter = 0;
        }

        counter++;
    }
}



