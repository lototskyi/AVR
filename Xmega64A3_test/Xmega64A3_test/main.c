#include "main.h"

int main(void)
{
    // 32MHz   
    OSC_CTRL |= OSC_RC32MEN_bm;
    while(!(OSC_STATUS & OSC_RC32MRDY_bm));
    CCP = CCP_IOREG_gc;
    CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
    
    // PORTC_OUTSET = PIN3_bm;
    PORTC_DIRSET = PIN3_bm; //TX pin as output
       
    PORTC_OUTCLR = PIN2_bm;
    //PORTC_DIRCLR = PIN2_bm; //PC2 as RX
    PORTA.DIRSET = PIN2_bm;
    USART_ini();
   
    
    while (1) 
    {
        PORTA_OUTTGL = PIN2_bm;
        USART_Transmit('O');
        USART_Transmit('K');
        USART_Transmit('!');
        USART_Transmit(0x0d);
        USART_Transmit(0x0a);
        _delay_ms(1000);
    }
}

