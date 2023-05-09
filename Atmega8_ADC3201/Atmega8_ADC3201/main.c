#include "main.h"

void port_ini(void) {
    PORTD = 0x00;
    DDRD = 0xFF;
    DDRC &= ~(1 << PORTC4) | (1 << PORTC5);
    PORTC |= (1 << PORTC4) | (1 << PORTC5);
}

void SPI_init() {
    DDRB |= (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5);
    PORTB &= ~((1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5));
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); //SPI on, master
}

void SPI_sendByte(char byte)
{
    SPDR = byte;
    
    while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    ;
}

unsigned char SPI_exchangeByte(char byte)
{
    SPDR = byte;
    
    while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    ;
    return SPDR;
}

unsigned int read3201()
{
    unsigned int b1, b2;
    PORTB &= ~(1 << PORTB2); //CS
    
    b1 = SPI_exchangeByte(0);
    b2 = SPI_exchangeByte(0);
    
    b1 = (b1 << 8) | b2;
    b1 <<= 3; //get rid of unnecessary bits
    b1 >>= 4;
    
    PORTB |= (1 << PORTB2); //CS
    
    return b1;
}

float convert_3201(unsigned int dt)
{
    //Miscellaneous: -Wl,-u,vfprintf -lprintf_flt -lm
    float dt1;
    dt1 = ((float)dt * 4.6) / 4096; //4.6 is ref
    return dt1;
}


int main(void)
{
    float dt = 0;
    char str[10];
        
    port_ini();
    I2C_Init();
    LCD_init();
    clearLCD();
    SPI_init();

    setPos(0, 0);
    sendCharLCD('2');

    while (1)
    {
        setPos(0, 0);
        
        dt = convert_3201(read3201());
        sprintf(str, "%.2fv ", dt);
        strLCD(str);
        
        _delay_ms(500);
    }
}






