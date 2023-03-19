#include "usart.h"

void USART_ini(unsigned int speed)
{
	UBRRH = (unsigned char) (speed >> 8);
	UBRRL = (unsigned char) speed;
	UCSRB = (1 << RXEN) | (1 << TXEN); //turn on transmitting and receiving by USART
	UCSRB |= (1 << RXCIE); // turn on interruption by USART
	UCSRA |= (1 << U2X); // double frequency
	UCSRC = (1 << URSEL) | (1 << USBS) | (1 << UCSZ1) | (1 << UCSZ0); //URSEL = 1 - we address to register UCSRC
	// UMSEL = 0 - async mode, (UPM1 = 0 and UPM0 = 0)- without controlling of parity
	// USBS = 1 - 2 stop bits, USCZ1 = 1 and USCZ0 = 1 - 8bit data mode
	
}

void USART_Transmit(unsigned char data) 
{
	while (!(UCSRA & (1 << UDRE))); // start transmit data if buffer is empty
	
	UDR = data; 
	
}