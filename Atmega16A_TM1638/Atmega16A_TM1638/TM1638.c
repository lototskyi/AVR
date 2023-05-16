#include "TM1638.h"

                    /*0*/ /*1*/ /*2*/ /*3*/ /*4*/ /*5*/ /*6*/ /*7*/ /*8*/ /*9*/
uint8_t digits[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
uint8_t leds[] = {0xC1, 0xC3, 0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xCF};
uint8_t seg[] = {0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE};
    
void sendByte(char value)
{
    char bt;
    for(char i = 0; i < 8; i++) {
        TM1638_PORT &= ~(1 << TM1638_CLK_PIN);
        _delay_us(5);
        bt = value & 1;
        
        if (bt) {
            TM1638_PORT |= (1 << TM1638_DIO_PIN);
        } else {
            TM1638_PORT &= ~(1 << TM1638_DIO_PIN);
        }
        
        value >>= 1;
        
        TM1638_PORT |= (1 << TM1638_CLK_PIN);
        _delay_us(5);
    }
}

int8_t readByte() 
{

    uint8_t value = 0;

    TM1638_DDR &= ~(1 << TM1638_DIO_PIN);
    TM1638_PORT |= (1 << TM1638_DIO_PIN);

    for(char i = 0; i < 8; i++) {
        TM1638_PORT &= ~(1 << TM1638_CLK_PIN);
        
        if ((((TM1638_PIN & (1 << TM1638_DIO_PIN)) > 0) ? 1 : 0)) {
            value |= 0x80;
        }
        value >>= 1;
        
        //value |= ((DATAPIN & (1 << DIO)) >> DIO) << i;
        TM1638_PORT |= (1 << TM1638_CLK_PIN);
    }
    
    TM1638_DDR |= (1 << TM1638_DIO_PIN);
    TM1638_PORT &= ~(1 << TM1638_DIO_PIN);
    
    return value;
}

void sendCommand(char value)
{
    STB_LOW;
    sendByte(value);
    STB_HIGH;
    _delay_us(1);
}

void clearDisplay()
{
    sendCommand(TM1638_CMD_SET_DATA); //Setting of Data Command,// Write data to the display register,// Set address to Auto increment, Normal mode
    STB_LOW;
    for (char i = 0; i < 16; i++) {
        sendByte(0x00);
    }
    STB_HIGH;
}

void sendDataByAddr(int8_t addr, int8_t data) 
{
    STB_LOW;
    sendByte(addr);
    sendByte(data);
    STB_HIGH;
}

void clearLed()
{
    sendCommand(TM1638_CMD_SET_DATA | TM1638_SET_DATA_F_ADDR | TM1638_SET_DATA_M_NORM | TM1638_SET_DISPLAY_ON);
    
    for (char i = 1; i < 16; i += 2) {
        STB_LOW;
        sendByte(0xC0 + i);
        sendByte(0x00);
        STB_HIGH;
    }
}

int8_t readButtons()
{
    uint8_t buttons = 0;
    STB_LOW;
    sendByte(TM1638_CMD_SET_DATA | TM1638_SET_DATA_READ);
    
    _delay_us(5);
    for (uint8_t i = 0; i < 4; i++)
    {
        buttons |= readByte() << i;
    }
    
    STB_HIGH;

    return buttons;
}

