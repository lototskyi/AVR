#include "adc.h"

extern unsigned int adc_value, adc_counter, adc_tmp;

char high_adc = 0, low_adc = 0;

ISR(ADC_vect)
{
    low_adc = ADCL;
    high_adc = ADCH;// ADCH must be read last
    
    //the arithmetic average of ADC value to prevent values from often change
    if (adc_counter < 20) {
        adc_tmp += high_adc * 256 + low_adc;
        adc_counter++;
    } else {
        adc_value = adc_tmp / 20;
        adc_counter = 0;
        adc_tmp = 0;
    }
}


void ADC_Init()
{
    ADCSRA |= (1 << ADEN) // enable ADC
              | (1 << ADSC) // run conversion
              | (1 << ADFR) // Free Running mode
              | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) // Division Factor = 128, 62.5kHz
              | (1 << ADIE); // ADC Interrupt Flag
    ADMUX |= (1 << REFS1) | (1 << REFS0); //Internal 2.56V Voltage Reference, default input ADC0
}