#include "adc.h"


void ADC_Init()
{
    ADCSRA |= (1 << ADEN) // enable ADC
              | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Division Factor = 128, 62.5kHz
    
    ADMUX |= (1 << REFS1) | (1 << REFS0); //Internal 2.56V Voltage Reference, default input ADC0
}

unsigned int ADC_convert()
{
    ADCSRA |= (1 << ADSC); //start converting
    
    while (!(ADCSRA & (1 << ADSC))); //check if converting is ended
    
    return (unsigned int) ADC;
}