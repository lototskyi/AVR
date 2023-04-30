#include "led.h"

unsigned char R1 = 0, R2 = 0, R3 = 0, R4 = 0;


void segchar(unsigned char seg)
{
    //    1 2 3 4 5 6 7 8
    //0b|dp|g|f|e|d|c|b|a|
    
    switch (seg)
    {
        case 1:	SPDR = 0b00000110; break;
        case 2:	SPDR = 0b01011011;	break;
        case 3:	SPDR = 0b01001111;	break;
        case 4:	SPDR = 0b01100110;	break;
        case 5:	SPDR = 0b01101101;	break;
        case 6:	SPDR = 0b01111101;	break;
        case 7:	SPDR = 0b00000111;	break;
        case 8:	SPDR = 0b01111111;	break;
        case 9:	SPDR = 0b01101111;	break;
        case 0:	SPDR = 0b00111111;	break;
        //case 10: SPDR = 0b01000000; break; // -
        //case 11: SPDR = 0b00000000; break; // " "
        //case 12: SPDR = 0b00111001; break; // C
    }
}

void timer_ini(void)
{
    TCCR1B |= (1 << WGM12); //CTC mode (compare mode)
    TIMSK |= (1 << OCIE1A); //bit for allowing interruption of the first counter by matching OCR1A(H and L)
    
    //OCR1AH = 0b000001111;
    //OCR1AL = 0b01100010;
    
    OCR1AH = 0b00001111;
    OCR1AL = 0b01000010;

    TCCR1B |= (1 << CS11);//set divider 8
}

void ledprint(unsigned int number)
{
    R1 = number % 10;
    R2 = number % 100 / 10;
    R3 = number % 1000 / 100;
    R4 = number / 1000;
}

unsigned char n_count = 0;

ISR (TIMER1_COMPA_vect)
{
    if (n_count == 0) {
        segchar(R1);
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        SPDR = 0b00000001;
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        
        //write to STORAGE REGISTER of 74HC595
        PORTB |= (1 << PORTB2);
        PORTB &= ~((1 << PORTB2));
    }
    
    if (n_count == 1) {
        segchar(R2);
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        SPDR = 0b00000010;
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        
        //write to STORAGE REGISTER of 74HC595
        PORTB |= (1 << PORTB2);
        PORTB &= ~((1 << PORTB2));
    }
    //
    if (n_count == 2) {
        segchar(R3);
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        SPDR = 0b00000100;
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        
        //write to STORAGE REGISTER of 74HC595
        PORTB |= (1 << PORTB2);
        PORTB &= ~((1 << PORTB2));
        
    }
    
    if (n_count == 3) {
        segchar(R4);
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        SPDR = 0b00001000;
        while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
        ;
        
        //write to STORAGE REGISTER of 74HC595
        PORTB |= (1 << PORTB2);
        PORTB &= ~((1 << PORTB2));
    }
    
    n_count++;
    
    if (n_count > 3) n_count = 0;
}
