//LED 7-Segment Display OC

#include "main.h"

#define MODETIMEVIEW 100
#define MODETEMPERVIEW 101
#define MODEDATEVIEW 102
#define MODEDAYVIEW 103
#define MODEYEARVIEW 104
#define MODESECVIEW 105

#define MODEINC 201
#define MODENOINC 202

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

unsigned char sec, min, hour, day, date, month, year, alarmhour, alarmmin;
unsigned char i;

void port_init() 
{
     DDRD = 0xFF; // output
     DDRB = 0b00011111;
     DDRC &= ~(1 << DDC3);
     DDRC |= (1 << DDC1); // alarm
     PORTC &= ~((1 << PORTC3) | (1 << PORTC1));
     PORTD = 0b00000000;
     PORTB = 0b00100000; // pull-up resistor on pin0
}

void ModifyRTC()
{
    I2C_StartCondition();
    I2C_SendByte(0b11010000);
    
    switch (clockeditmode) {
        case MODEHOUREDIT: //hours
        
            I2C_SendByte(2);

            if (hour < 23) {
                I2C_SendByte(RTC_ConvertFromBinDec(hour + 1));
            } else {
                I2C_SendByte(RTC_ConvertFromBinDec(0));
            }
       
            break;
        case MODEMINEDIT: //mins
        
            I2C_SendByte(1);
            
            if (min < 59) {
                I2C_SendByte(RTC_ConvertFromBinDec(min + 1));
            } else {
                I2C_SendByte(RTC_ConvertFromBinDec(0));
            }

            break;
        case MODESECEDIT: //sec
            
            I2C_SendByte(0);
            I2C_SendByte(RTC_ConvertFromBinDec(0));
            break;
        case MODEDATEEDIT: //date
            
            I2C_SendByte(4); //go to address 0x04

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

            break;
        case MODEMONTHEDIT: //month
        
            I2C_SendByte(5);
            
            if (month < 12) {
                I2C_SendByte(RTC_ConvertFromBinDec(month + 1));
            } else {
                I2C_SendByte(RTC_ConvertFromBinDec(1));
            }
        
            break;
        case MODEYEAREDIT: //year
        
            I2C_SendByte(6);
            
            if (year < 99) {
                I2C_SendByte(RTC_ConvertFromBinDec(year + 1));
            } else {
                I2C_SendByte(RTC_ConvertFromBinDec(1));
            }

            break;
        case MODEDAYEDIT: //day
        
            I2C_SendByte(3);
            
            if (day < 7) {
                I2C_SendByte(RTC_ConvertFromBinDec(day + 1));
            } else {
                I2C_SendByte(RTC_ConvertFromBinDec(1));
            }
        
            break;
        case MODEALARMHOUREDIT: //alarm hour
            if (alarmhour < 23) {
                EEPROM_write(2, alarmhour + 1);
            } else {
                EEPROM_write(2, 0);
            }
            break;
        case MODEALARMMINEDIT: //alarm mins
        
            if (alarmmin < 59) {
                EEPROM_write(3, alarmmin + 1);
            } else {
                EEPROM_write(3, 0);
            }
        
            break;

    }
    
    I2C_StopCondition();
}

void alarm()
{
    if (sec % 4 != 0) PORTC |= (1 << PORTC1);
    _delay_ms(15);
    PORTC &= ~(1 << PORTC1);
}

void alarm_off()
{
    PORTC &= ~(1 << PORTC1);
}

int main(void)
{
    unsigned int tt = 0; //temperature
    unsigned char clockmode = MODETIMEVIEW;
    clockeditmode = MODENONEEDIT;
    clockincmode = MODENOINC;
    alarmcmp = 0;
    button_cnt = 0;
    alarmbeep = 0;
    
    if (EEPROM_read(1) > 1) EEPROM_write(1, 0); //check if correct data were written - 1/0
    alarmmode = EEPROM_read(1);
    
    if (EEPROM_read(2) > 23) EEPROM_write(2, 0); //alarm hours 
    if (EEPROM_read(3) > 59) EEPROM_write(3, 0); //alarm minutes
    
    I2C_Init();
    
    timer_ini();
    port_init();
    init_button_port();
    init_PWM_timer();
    init_button_timer();
    ADC_Init();
    
    sei(); // set global interruption

    OCR2A = 7;

    I2C_StartCondition();
    I2C_SendByte(0b11010000);
    I2C_SendByte(7); //go to address 0x07
    I2C_SendByte(0b00010000); // SQWE on
    I2C_StopCondition();

    while (1)
    {
        //read time
        
        I2C_SendByteByADDR(0, 0b11010000); // got to address 0x00
        
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
        
        if (sec < 30 || sec > 41) {
            clockmode = MODETIMEVIEW;
        } else if (sec < 34) {
            clockmode = MODETEMPERVIEW;
        } else if (sec < 38) {
            clockmode = MODEDAYVIEW;
        } else {
            clockmode = MODEDATEVIEW;
        }
        
        tt = convertTemp(dt_check());
        
        alarmhour = EEPROM_read(2);
        alarmmin = EEPROM_read(3);
        
        if (alarmmin == min && alarmhour == hour && clockeditmode == MODENONEEDIT) {
            
            if (alarmcmp == 0) {
                alarmbeep = 1;
            }
            
            alarmcmp = 1;
            
        } else {
            alarmcmp = 0;
        }
        
        if (clockeditmode != MODENONEEDIT && clockincmode == MODEINC) {
            ModifyRTC();
            clockincmode = MODENOINC;
        }
        
        if (adc_value < 80) {
            OCR2A = 80 - adc_value;
        } else {
            OCR2A = 7;
        }
        
        if (clockeditmode == MODENONEEDIT) {
            if (clockmode == MODETIMEVIEW) {
                ledprint(hour * 100 + min, clockmode);
            }
            
            if (clockmode == MODETEMPERVIEW) {
                ledprint((tt >> 1) * 100 + ((tt % 2) * 5) * 10, clockmode);
            }
            
            if (clockmode == MODEDAYVIEW) {
                ledprint(day * 10, clockmode);
            }
            
            if (clockmode == MODEDATEVIEW) {
                ledprint(month + date * 100, clockmode);
            }
        } else if (clockeditmode == MODEMINEDIT || clockeditmode == MODEHOUREDIT) {
            ledprint(hour * 100 + min, MODETIMEVIEW);
        } else if (clockeditmode == MODESECEDIT) {
            ledprint(sec, MODESECVIEW);
        } else if (clockeditmode == MODEDATEEDIT || clockeditmode == MODEMONTHEDIT) {
            ledprint(date * 100 + month, MODEDATEVIEW);
        } else if (clockeditmode == MODEDAYEDIT) {
            ledprint(day * 10, MODEDAYVIEW);
        } else if (clockeditmode == MODEYEAREDIT) {
            ledprint(year + 2000, MODEYEARVIEW);
        } else if (clockeditmode == MODEALARMMINEDIT || clockeditmode == MODEALARMHOUREDIT) {
            ledprint(alarmhour * 100 + alarmmin, MODETIMEVIEW);
        }

        if (alarmcmp == 1 && alarmbeep == 1) {
            alarm();
        } else {
            alarm_off();
        }
    }
}