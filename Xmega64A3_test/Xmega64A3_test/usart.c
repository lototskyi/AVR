#include "usart.h"

void USART_ini()
{
    // Baud rate selection
    // BSEL = (32000000 / (2^0 * 16*9600) -1 = 207.333 -> BSCALE = 0
    // FBAUD = ( (32000000)/(2^0*16(207+1)) = 9615.384 -> it's alright
    
    USARTC0_BAUDCTRLB = 0; //Just to be sure that BSCALE is 0
    USARTC0_BAUDCTRLA = 207; // 207
    
    
    //Disable interrupts, just for safety
    USARTC0_CTRLA = 0;
    //8 data bits, no parity and 1 stop bit
    USARTC0_CTRLC = USART_CHSIZE_8BIT_gc;
    
    //Enable receive and transmit
    USARTC0_CTRLB = USART_TXEN_bm | USART_RXEN_bm; // And enable high speed mode
    
    //char bsel = 12;
    //USARTC0_BAUDCTRLB = 0;//(unsigned char)(bsel>>8);
    //USARTC0_BAUDCTRLA = 12;//(unsigned char)bsel;
    //// USARTF0.CTRLA=0x03;
    //USARTC0.CTRLC = (USARTC0.CTRLC & ~USART_CHSIZE_gm) | USART_CHSIZE_8BIT_gc;
    //USARTC0.CTRLB = (USART_RXEN_bm | USART_TXEN_bm);
    
}

void USART_Transmit(char data) 
{
    while(!(USARTC0_STATUS & USART_DREIF_bm));
    
	USARTC0_DATA = data; 
	
}