#include "main.h"

void port_init() {
    PORTD = 0x00;
    DDRD = 0xFF;
}


int main(void)
{
    unsigned int adc_value;
    float n;
    
    port_init();
    LCD_ini();
    ADC_Init();
    clearLCD();
    
    while (1) 
    {
        adc_value = ADC_convert();
        setPos(0, 0);
        sendCharLCD(adc_value / 1000 + 0x30);
        sendCharLCD((adc_value % 1000) / 100 + 0x30);
        sendCharLCD((adc_value % 100) / 10 + 0x30);
        sendCharLCD(adc_value % 10 + 0x30);
        
        setPos(8, 0);
        
        n = (float) adc_value / 400; // 1024/2.56 = 400
        sendCharLCD((unsigned char) n % 10 + 0x30);
        sendCharLCD('.');
        sendCharLCD(((unsigned char) (n * 10)) % 10 +0x30);
        sendCharLCD(((unsigned char) (n * 100)) % 10 +0x30);
        _delay_ms(500);
    }
}

