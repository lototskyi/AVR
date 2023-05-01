#include "main.h"

char dg = 8;

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

void send_7219(char rg, char dt) 
{
    PORTB &= ~(1 << PORTB2);
    
    SPI_sendByte(rg);
    SPI_sendByte(dt);
    
    PORTB |= (1 << PORTB2);
}

void clear_7219()
{
    char i = dg;
    
    do {
        send_7219(i, 0xF);// empty symbol
    } while (--i);
}

void number_7219(volatile long n)
{
    char ng = 0; //negative
    if (n < 0) {
        ng = 1;
        n *= -1;
    }
    clear_7219();
    
    if (n == 0) {
        send_7219(0x01, 0);
        return;
    }
    
    char i = 0;
    
    do {
        send_7219(++i, n % 10);
        n /= 10;
    } while (n);
    
    if (ng) {
        send_7219(i + 1, 0xA);//minus
    }
}

int main(void)
{
    
    unsigned int i = 0;
    
    SPI_init();
    
    send_7219(0x09, 0xFF); //decode mode
    send_7219(0x0B, dg - 1); //scan limit
    send_7219(0x0A, 0x03); //intensity
    send_7219(0x0C, 0x01); //turn on display
    clear_7219();

    send_7219(1, 0x1);
    send_7219(2, 0x2);
    send_7219(3, 0x3);
    send_7219(4, 0x4);
    send_7219(5, 0x5);
    send_7219(6, 0x6);
    send_7219(7, 0x7);
    send_7219(8, 0x8);

    _delay_ms(2000);

    number_7219(-2022);
    
    _delay_ms(2000);

    while (1)
    {
        number_7219(i);
        i++;
        _delay_ms(200);
    }
}






