#include "main.h"

#define MOSI 3
#define MISO 4
#define SCK  5
#define SS   2

//char buffer[512] = "NOTE: When an MPU program with checking the busy flag (DB7) is made, it must be necessary 1/2fosc is necessary for executing the next instruction by the falling edge of the 'E' signal after the busy flag (DB7) goes to 'Low'.  In case of RAM write operation, AC is increased/decreased by 1 as in read operation. At this time, AC indicates next address position, but only the previous data can be read by the read instruction. The selection of RAM is set by the previous address set instruction. If the address...";
char buffer2[512] = {};

unsigned char Pattern1[]= {0x0e,0x0e,0x04,0x04,0x1f,0x04,0x0a,0x0a};
unsigned char Pattern2[]= {0x0e,0x0e,0x15,0x0e,0x04,0x04,0x0a,0x11};
unsigned char Pattern3[]= {0x00,0x00,0x0a,0x15,0x11,0x0a,0x04,0x00};
unsigned char Pattern4[]= {0x00,0x00,0x0a,0x1f,0x1f,0x0e,0x04,0x00};

void port_init()
{
    PORTD = 0x00;
    DDRD = 0xFF;
    
    PORTB |= (1 << SS) | (1 << MISO) | (1 << MOSI);
    DDRB  |= (1 << SS) | (1 << MOSI) | (1 << SCK);
}

void SPI_SendByte(unsigned char byte)
{
    unsigned char i;
    
    for (i = 0; i < 8; i++) {
        if ((byte & 0x80) == 0x00) {
            PORTB &= ~(1 << MOSI);
        } else {
            PORTB |= (1 << MOSI);
        }
        
        byte <<= 1;
        
        PORTB |= (1 << SCK);
        asm("nop"); //skip 1 tact
        PORTB &= ~(1 << SCK);
    }
}

unsigned char SPI_ReceiveByte()
{
    unsigned char i, result = 0;
    
    for (i = 0; i < 8; i++) {
        PORTB |= (1 << SCK);
         
        result <<= 1;
         
        if ((PINB & (1 << MISO)) != 0x00) {
            result = result | 0x01;
        }
        PORTB &= ~(1 << SCK);
        asm("nop"); //skip 1 tact
    }
    
    return result;
}

unsigned char SD_cmd(char dt0, char dt1, char dt2, char dt3, char dt4, char dt5)
{
    unsigned char result = 0;
    long int cnt;
    SPI_SendByte(dt0); //index
    SPI_SendByte(dt1); //argument
    SPI_SendByte(dt2); //
    SPI_SendByte(dt3);
    SPI_SendByte(dt4); 
    SPI_SendByte(dt5); //control sum
    
    cnt = 0;
    
    do //white for result
    {
        result = SPI_ReceiveByte();
        cnt++;
    } while ((result & 0x80) != 0x00 && cnt < 0xFFFF);
    return result;
}

unsigned char SD_Init() 
{
    unsigned char i, temp;
    long int cnt;
    
    for (i = 0; i < 10; i++) { // 80 impulses (not less than 74)
        SPI_SendByte(0xFF);
    }
    
    PORTB &= ~(1 << SS);// chip select
    temp = SD_cmd(0x40, 0x00, 0x00, 0x00, 0x00, 0x95); //CMD0 datasheet 102 and 96
    
    if (temp != 0x01) return 1; //exit if answer is not 0x01
    
    SPI_SendByte(0xFF);
    
    cnt = 0;
    
    do //white for result
    {
        temp = SD_cmd(0x41, 0x00, 0x00, 0x00, 0x00, 0x95); //CMD1
        SPI_SendByte(0xFF);
        cnt++;
    } while ((temp != 0x00) && cnt < 0xFFFF); //waiting for answer R1
    
    if (cnt >= 0xFFFF) return 2;
    
    return 0;
}

unsigned char SD_WriteBlock(char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4)
{
    unsigned char result;
    
    long int cnt;
    result = SD_cmd(0x58, dt1, dt2, dt3, dt4, 0x95); //CMD24 datasheet 51, 97-98
    
    if (result != 0x00) return 3;
    
    SPI_SendByte(0xFF);
    SPI_SendByte(0xFE); // buffer start
    
    for (cnt = 0; cnt < 512; cnt++) {
        SPI_SendByte(bf[cnt]);
    }
    
     SPI_SendByte(0xFF);
     SPI_SendByte(0xFF); // checksum
     
     result = SPI_ReceiveByte();
     
     if ((result & 0x05) != 0x05) return 4; //datasheet 111
     
     cnt = 0;
     
     do //white for result
     {
         result = SPI_ReceiveByte();
         cnt++;
     } while ((result != 0xFF) && cnt < 0xFFFF);
     
     if (cnt >= 0xFFFF) return 5;
     
     return 0;
}

unsigned char SD_ReadBlock(char* bf, unsigned char dt1, unsigned char dt2, unsigned char dt3, unsigned char dt4)
{
    unsigned char result;
    
    long int cnt;
    result = SD_cmd(0x51, dt1, dt2, dt3, dt4, 0x95); //CMD17 datasheet 50, 96
    
    if (result != 0x00) return 3;
    
    SPI_SendByte(0xFF);
    
    cnt = 0;
    
    do //white for result
    {
        result = SPI_ReceiveByte();
        cnt++;
    } while ((result != 0xFE) && cnt < 0xFFFF);
    
    if (cnt >= 0xFFFF) return 5;
    
    for (cnt = 0; cnt < 512; cnt++) {
        bf[cnt] = SPI_ReceiveByte(); //read data into buffer
    }
    
    SPI_ReceiveByte();
    SPI_ReceiveByte();

    return 0;
}


int main(void)
{
    unsigned char i;
    char str[10];
    unsigned char result;
    
    port_init();
    LCD_ini();
    
    clearLCD();
    
    strLCD("String 1");
    
    setPos(2, 1);
    strLCD("String 2");
    
    setPos(4, 2);
    strLCD("String 3");
    
    setPos(6, 3);
    strLCD("String 4");
    
    _delay_ms(1000);
    
    result = SD_Init();
    clearLCD();
    
    setPos(0, 0);
    sprintf(str, "%d", result);
    strLCD(str);
    
    //result = SD_WriteBlock(buffer, 0x00, 0x00, 0x04, 0x00); //write block from buffer
    //setPos(0, 1);
    //sprintf(str, "%d", result);
    //strLCD(str);
    
    result = SD_ReadBlock(buffer2, 0x00, 0x00, 0x04, 0x00); //read block into buffer
    setPos(0, 2);
    sprintf(str, "%d", result);
    strLCD(str);
    
    _delay_ms(1000);
    
    for (i = 0; i <= 22; i++) {
        strLCD80(buffer2 + i * 20);
        _delay_ms(1000);
    }
    
    //strLCD80(buffer);
    //_delay_ms(2000);
    //strLCD80(buffer + 20);
    
    
    
    //for (i = 0; i <= 22; i++) {
    //strLCD80(buffer + i * 20);
    //_delay_ms(400);
    //}
    
    while (1)
    {
        

    }
}



