#include "main.h"

extern uint8_t digits[];
extern uint8_t leds[];
extern uint8_t seg[];

uint8_t promptText[] =
{
    /*P*/ /*r*/ /*E*/ /*S*/ /*S*/ /* */ /* */ /* */
    0x73, 0x50, 0x79, 0x6d, 0x6d, 0x00, 0x00, 0x00,
    /* */ /* */ /* */ /* */ /* */ /* */ /* */ /* */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /*b*/ /*u*/ /*t*/ /*t*/ /*o*/ /*n*/ /*S*/ /* */
    0x7c, 0x1c, 0x78, 0x78, 0x5c, 0x54, 0x6d, 0x00,
    /* */ /* */ /* */ /* */ /* */ /* */ /* */ /* */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

uint8_t scrollText[] =
{
    /* */ /* */ /* */ /* */ /* */ /* */ /* */ /* */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /*H*/ /*E*/ /*L*/ /*L*/ /*O*/ /*.*/ /*.*/ /*.*/
    0x76, 0x79, 0x38, 0x38, 0x3f, 0x80, 0x80, 0x80,
    /* */ /* */ /* */ /* */ /* */ /* */ /* */ /* */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /*H*/ /*E*/ /*L*/ /*L*/ /*O*/ /*.*/ /*.*/ /*.*/
    0x76, 0x79, 0x38, 0x38, 0x3f, 0x80, 0x80, 0x80,
    /* */ /* */ /* */ /* */ /* */ /* */ /* */ /* */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

int k = 0;


void timer_init()
{
    TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);
    OCR0 = 0xFF;
    //TIMSK |= (1 << OCIE0);
    //sei();
}

void portInit()
{
    DDRB |= (1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0);
    PORTB &= ~((1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0));
    sendCommand(0x89); //Display control //Set the pulse width to 14/16 //Display ON
}

void showNumber(int num) 
{
    uint8_t d1 = num % 10;
    uint8_t d2 = num / 10 % 100;
    
    sendDataByAddr(seg[7], digits[d1]);
    sendDataByAddr(seg[6], digits[d2]);
}


int main(void)
{
    int8_t buttonsData;
    
    portInit();
    timer_init(); 
    USART_ini(34); //28800
    
    clearDisplay();
    sendCommand(TM1638_CMD_SET_DATA | TM1638_SET_DATA_F_ADDR | TM1638_SET_DATA_M_NORM);
    
    int j = 0;

    while (1) 
    {
        buttonsData = readButtons();
        
        for (uint8_t t = 0; t < 8; t++) {
            if (buttonsData & (1 << t)) {
                sendDataByAddr(leds[t], 0x01);
            } else {
                sendDataByAddr(leds[t], 0x00);
            }
        }
        
        //for (int i = 0; i < 8; i++) {
            //
            //buttonsData = readButtons();
            //USART_Transmit(buttonsData);
            //if (buttonsData == 0x01) {
                //i = 0;
                //j = 0;
                //showNumber(j);
                //clearLed();
                //j++;
            //}
            //
            //sendDataByAddr(leds[i], 0x01);
            //_delay_ms(50);
        //}
        
        //showNumber(j);
        //
        
        
        if (TIFR & (1 << OCF0) && j == 128) {
            clearDisplay();
            
            for (uint8_t n = 0; n < 8; n++) {
                sendDataByAddr(seg[n], scrollText[k + n]);
            }

            k++;

            if (k + 9 > sizeof(scrollText)) {
                k = 0;
            }
            
            USART_Transmit(buttonsData);
        }
        
        j++;
        
        if (j > 128) {
            j = 0;
        }
        
        //_delay_ms(200);
    }
}

