#include "main.h"

char buffer[512] = "NOTE: When an MPU program with checking the busy flag (DB7) is made, it must be necessary 1/2fosc is necessary for executing the next instruction by the falling edge of the 'E' signal after the busy flag (DB7) goes to 'Low'.  In case of RAM write operation, AC is increased/decreased by 1 as in read operation. At this time, AC indicates next address position, but only the previous data can be read by the read instruction. The selection of RAM is set by the previous address set instruction. If the address...";
unsigned char Pattern1[]= {0x0e,0x0e,0x04,0x04,0x1f,0x04,0x0a,0x0a};
unsigned char Pattern2[]= {0x0e,0x0e,0x15,0x0e,0x04,0x04,0x0a,0x11};
unsigned char Pattern3[]= {0x00,0x00,0x0a,0x15,0x11,0x0a,0x04,0x00};
unsigned char Pattern4[]= {0x00,0x00,0x0a,0x1f,0x1f,0x0e,0x04,0x00};

void port_init()
{
    PORTD = 0x00;
    DDRD = 0xFF;
}

int main(void)
{
    unsigned int i;
    
    port_init();
    LCD_ini();
    
    clearLCD();
    
    createCustomCharacter(Pattern1, 1);
    createCustomCharacter(Pattern2, 3);
    createCustomCharacter(Pattern3, 0);
    createCustomCharacter(Pattern4, 2);
    
    //strLCD("String 1");
//
    //setPos(2, 1);
    //strLCD("String 2");
    //
    //setPos(4, 2);
    //strLCD("String 3");
    //
    //setPos(6, 3);
    //sendCharLCD(0);
    
    //sendCharLCD(1);
    //strLCD("String 4");
    
    //_delay_ms(2000);
    //strLCD80(buffer);
    //_delay_ms(2000);
    //strLCD80(buffer + 20);
    
    //for (i = 0; i <= 22; i++) {
        //strLCD80(buffer + i * 20);
        //_delay_ms(1000);
    //}
    
    //for (i = 0; i <= 22; i++) {
        //strLCD80(buffer + i * 20);
        //_delay_ms(400);
    //}
    
    //for (i = 0; i <= 432; i++) {
        //strLCD80(buffer + i);
        //_delay_ms(200);
    //}
    
    while (1) 
    {
        
        setPos(9, 0);
        sendCharLCD(0);
        setPos(10, 0);
        sendCharLCD(1);
        _delay_ms(500);
        
        setPos(9, 0);
        sendCharLCD(2);
        setPos(10, 0);
        sendCharLCD(3);
        _delay_ms(500);
    }
}

