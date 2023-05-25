#include "main.h"

char buffer[512] = "NOTE: When an MPU program with checking the busy flag (DB7) is made, it must be necessary 1/2fosc is necessary for executing the next instruction by the falling edge of the 'E' signal after the busy flag (DB7) goes to 'Low'.  In case of RAM write operation, AC is increased/decreased by 1 as in read operation. At this time, AC indicates next address position, but only the previous data can be read by the read instruction. The selection of RAM is set by the previous address set instruction. If the address...";
char test[20] = "qwertyuiopasdfghjkl;";
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
    
    setPos(0, 0);
    strLCD("String 1");

    setPos(2, 1);
    strLCD("String 2");
    
    setPos(4, 2);
    strLCD("String 3");
    
    setPos(6, 3);
    strLCD("String 4");
    
    //_delay_ms(2000);
    //strLCD80(buffer);
    //_delay_ms(2000);
    //strLCD80(buffer + 20);
    
    //for (i = 0; i <= 22; i++) {
        //strLCD80(buffer + i * 20);
        //_delay_ms(1000);
    //}
    
    for (i = 0; i <= 1; i++) {
        strLCD80(test + i * 20);
        _delay_ms(100);
    }
    
    //for (i = 0; i <= 432; i++) {
        //strLCD80(buffer + i);
        //_delay_ms(200);
    //}
    
    while (1) 
    {
        
    }
}

