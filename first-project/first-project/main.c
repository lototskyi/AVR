
#include <avr/io.h>


int main(void)
{
	DDRD = 0xFF;
    
	PORTD = 0b00000001;

    while (1) 
    {
		
    }
}

