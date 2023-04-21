#include "DS18B20.h"

int dt_testDevice()
{
    char stekTemp = SREG; //save data of status register
    cli(); //disable interrupts
    char dt;
    
    DDRTEMP |= 1 << BITTEMP; //pull wire bus low (port in output mode)
    _delay_us(485);
    DDRTEMP &= ~(1 << BITTEMP); // pull wire bus up (port in input mode)
    _delay_us(65);
    
    if ((PINTEMP & (1 << BITTEMP)) == 0) { //check response from device
        dt = 1;
    } else {
        dt = 0;
    }

    SREG = stekTemp;
    _delay_us(420); // should be 480 but 420 is enough
    return dt;
}

void dt_sendBit(char bt) 
{
    char stekTemp = SREG; //save data of status register
    cli(); //disable interrupts
    
    DDRTEMP |= 1 << BITTEMP; //pull wire bus low (port in output mode)
    _delay_us(2);
    
    if (bt) {
        DDRTEMP &= ~(1 << BITTEMP);
    }
    _delay_us(65);
    
    DDRTEMP &= ~(1 << BITTEMP);
    SREG = stekTemp;
}

void dt_sendByte(unsigned char bt) //send every bit to device
{
    char i;
    
    for (i = 0; i < 8; i++) {
        if ((bt & (1 << i)) == 1 << i) { // send 1
            dt_sendBit(1);
        } else {
            dt_sendBit(0);
        }
    }
}

char dt_readBit() 
{
    char stekTemp = SREG; //save data of status register
    cli(); //disable interrupts
    char bt;
    
    DDRTEMP |= 1 << BITTEMP; //pull wire bus low (port in output mode)
    _delay_us(2);
    DDRTEMP &= ~(1 << BITTEMP); // pull wire bus up (port in input mode)
    _delay_us(13);
    
   bt = (PINTEMP & (1 << BITTEMP)) >> BITTEMP; //read bit
    _delay_us(45);
    
    SREG = stekTemp;
    
    return bt;
}

char dt_readByte()
{
    char c = 0;
    char i;
    
    for(i = 0; i < 8; i++) {
        c |= dt_readBit() << i; // read bit
    }
    
    return c;
}


int dt_check() //convert data to temperature
{
    unsigned char bt; // variables to read byte
    unsigned int tt = 0;
    
    if (dt_testDevice() == 1) { // if device exists
        dt_sendByte(NOID); // skip device identification
        dt_sendByte(T_CONVERT);
        _delay_ms(100);
        
        dt_testDevice();
        dt_sendByte(NOID);
        
        dt_sendByte(READ_DATA);
        bt = dt_readByte(); //read low bit
        tt = dt_readByte(); //read high bit
        
        tt = ((tt << 8) | bt);
    }
    return tt;
}

char convertTemp (unsigned int tt) 
{
    char t = tt >> 3; //integer part
    return t;
}

char getDecimalTemp(unsigned int tt) 
{
    char t = ((tt & 15) * THERM_DECIMAL_STEPS_12BIT) / 100; //decimal part, divide by 100 means to round the value to 2 digits
    return t;
}