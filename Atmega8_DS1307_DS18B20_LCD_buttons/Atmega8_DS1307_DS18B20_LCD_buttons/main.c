#include "main.h"

#define BUTTONPORT PORTC
#define BUTTONPORT1 PORTC1
#define BUTTONPORT2 PORTC2
#define BUTTONPORT3 PORTC3

#define BUTTONPIN PINC
#define BUTTONPIN1 PINC1
#define BUTTONPIN2 PINC2
#define BUTTONPIN3 PINC3

#define BUTTONDDR DDRC
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

void port_init()
{
    PORTD = 0x00;
    DDRD = 0xFF;
    BUTTONDDR &= ~((1 << BUTTONDDR3) | (1 << BUTTONDDR2) | (1 << BUTTONDDR3));
    BUTTONPORT |= ((1 << BUTTONPORT3) | (1 << BUTTONPORT2) | (1 << BUTTONPORT1));
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


char buttonPress (char index) 
{
    char result = 0, buttonCount = 0, buttonState = 0;
    
    switch (index) {
        case 1:
            while (buttonState == 0) {
                if (!(BUTTONPIN & (1 << BUTTONPIN1))) {
                    if (buttonCount < 5) {
                        buttonCount++;
                    } else {
                        result = 1;
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
        
            break;
        case 2:
        
            while (buttonState == 0) {
                if (!(BUTTONPIN & (1 << BUTTONPIN2))) {
                    if (buttonCount < 5) {
                        buttonCount++;
                    } else {
                        result = 2;
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
            break;
        case 3:
            
            while (buttonState == 0) {
                if (!(BUTTONPIN & (1 << BUTTONPIN3))) {
                    if (buttonCount < 5) {
                        buttonCount++;
                    } else {
                        result = 3;
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
        
            break;
    }
    
    return result;
}

int main(void)
{
    unsigned int tt = 0;
    unsigned char button1state = 0; //state of button 1
    unsigned char clockmode = CLOCKMODE0;
    char blinkstate = 0;
    
    port_init();
    I2C_Init();
    LCD_ini();
    clearLCD();
    
    while (1)
    {
        //read time
        
        I2C_SendByteByADDR(0, 0b11010000); // got to address 0x00
        _delay_ms(50);
        
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
        
        sec = RTC_ConvertToDec(sec);
        min = RTC_ConvertToDec(min);
        hour = RTC_ConvertToDec(hour);
        day = RTC_ConvertToDec(day);
        date = RTC_ConvertToDec(date);
        month = RTC_ConvertToDec(month);
        year = RTC_ConvertToDec(year);
        
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
            
            if (buttonPress(1) == 1) {
                
                if (button1state == 0) { //get status not to go to month change mode
                    clockmode = CLOCKMODEMONTH; //month change mode
                    button1state = 1;
                }
            }
            
            if (clockmode == CLOCKMODEDATE) {
                button1state = 0;
            }
            
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
        
            if (buttonPress(1) == 1) {
            
                if (button1state == 0) {
                    clockmode = CLOCKMODEYEAR;
                    button1state = 1;
                }
            }
        
            if (clockmode == CLOCKMODEMONTH) {
                button1state = 0;
            }
            
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
            
            if (buttonPress(1) == 1) {
                
                if (button1state == 0) {
                    clockmode = CLOCKMODEDAY;
                    button1state = 1;
                }
            }
            
            if (clockmode == CLOCKMODEYEAR) {
                button1state = 0;
            }
            
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
            sendCharLCD(day+0x30);
            sendCharLCD('-');
        } else { //DAY OF WEEK
            
            if (blinkstate == 0) {
                sendCharLCD(' ');
                sendCharLCD(' ');
                sendCharLCD(' ');
                blinkstate = 1;
            } else {
                sendCharLCD('-');
                sendCharLCD(day+0x30);
                sendCharLCD('-');
                blinkstate = 0;
            }
            
            if (buttonPress(1) == 1) {
                
                if (button1state == 0) {
                    clockmode = CLOCKMODEHOUR;
                    button1state = 1;
                }
            }
            
            if (clockmode == CLOCKMODEDAY) {
                button1state = 0;
            }
            
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
            
            if (buttonPress(1) == 1) {
                
                if (button1state == 0) {
                    clockmode = CLOCKMODEMIN;
                    button1state = 1;
                }
            }
            
            if (clockmode == CLOCKMODEHOUR) {
                button1state = 0;
            }
            
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
            
            if (buttonPress(1) == 1) {
                
                if (button1state == 0) {
                    clockmode = CLOCKMODESEC;
                    button1state = 1;
                }
            }
            
            if (clockmode == CLOCKMODEMIN) {
                button1state = 0;
            }
            
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
    
            if (buttonPress(1) == 1) {
        
                if (button1state == 0) {
                    clockmode = CLOCKMODE0; //clock mode
                    button1state = 1;
                }
            }
    
            if (clockmode == CLOCKMODESEC) {
                button1state = 0;
            }
            
            if (buttonPress(2) == 2) { //button 2
                ModifyRTC(7, 0); // 7 - sec; 0 - set 30
            }
            if (buttonPress(3) == 3) { //button 3
                ModifyRTC(7, 1); // 7 - sec; 1 - set 0
            }
    
        }

        sendCharLCD(' ');
        tt = convertTemp(dt_check()); //get temp
        sendCharLCD(tt / 10 + 0x30);
        sendCharLCD(tt % 10 + 0x30);
        sendCharLCD('*');
        sendCharLCD('C');
    }
}
