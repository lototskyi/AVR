#include "main.h"


unsigned char seg_char(int seg) {
    switch (seg) {
        case 1:	return ~(0b00000110);
        case 2:	return ~(0b01011011);
        case 3:	return ~(0b01001111);
        case 4:	return ~(0b01100110);
        case 5:	return ~(0b01101101);
        case 6:	return ~(0b01111101);
        case 7:	return ~(0b00000111);
        case 8:	return ~(0b01111111);
        case 9:	return ~(0b01101111);
        case 0:	return ~(0b00111111);
        case 10: return ~(0b01000000); // -
        case 11: return ~(0b00000000); // " "
        case 12: return ~(0b00111001); // C
        case 13: return 0b01111111; // .
    }
    return 0b00000000;
}    

int main(void)
{
   
    DDRB |= (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5);
    PORTB &= ~((1 << PORTB2) | (1 << PORTB3) | (1 << PORTB5));
    SPCR |= (1 << SPE) | (1 << MSTR); //SPI on, master
    
    SPDR = 0b00000000;
    
    while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
    ;
    
    //write to STORAGE REGISTER of 74HC595
    PORTB |= (1 << PORTB2);
    PORTB &= ~((1 << PORTB2));
    _delay_ms(500);

    char arr[14] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 10, 11, 12, 13};

    while (1)
    {
        
        for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++) {
            
            SPDR = seg_char(arr[i]);
            
            while(!(SPSR & (1<<SPIF))) //waiting for data to be transmitted
            ;
            
            //write to STORAGE REGISTER of 74HC595
            PORTB |= (1 << PORTB2);
            PORTB &= ~((1 << PORTB2));
            _delay_ms(1000);
            
        }
    }
}


