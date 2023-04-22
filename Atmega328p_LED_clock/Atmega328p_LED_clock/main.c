//LED 7-Segment Display OC

#include "main.h"

#define MODETIMEVIEW 100
#define MODETEMPERVIEW 101
#define MODEDATEVIEW 102
#define MODEDAYVIEW 103

#define MODENONEEDIT 0
#define MODEMINEDIT 1

unsigned char sec, min, hour, day, date, month, year;
unsigned int i;

void port_init() 
{
     DDRD = 0xFF; // output
     DDRB = 0b00011111;
     DDRC &= ~(1 << DDC3);
     PORTC &= ~(1 << PORTC3);
     PORTD = 0b00000000;
     PORTB = 0b00100000; // pull-up resistor on pin0
}

int main(void)
{
    unsigned int tt = 0; //temperature
    unsigned char clockmode = MODETIMEVIEW;
    clockeditmode=MODENONEEDIT;
    
    button_cnt = 0;
    
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
        
        if (adc_value < 80) {
            OCR2A = 80 - adc_value;
            } else {
            OCR2A = 7;
        }
        
        //if (clockmode == MODETIMEVIEW) {
            //ledprint(hour * 100 + min, clockmode);
        //}
        //
        //if (clockmode == MODETEMPERVIEW) {
            //ledprint((tt >> 1) * 100 + ((tt % 2) * 5) * 10, clockmode);
        //}
        //
        //if (clockmode == MODEDAYVIEW) {
            //ledprint(day * 10, clockmode);
        //}
        //
        //if (clockmode == MODEDATEVIEW) {
            //ledprint(month + date * 100, clockmode);
        //}
        
        ledprint(button_cnt, MODEDATEVIEW);
    }
}




