#include "main.h"

#define MOSI 3
#define MISO 4
#define SCK  5
#define SS   2

char buffer2[512] = {};

void port_init()
{
    PORTD = 0x00;
    DDRD = 0xFF;
    
    PORTB |= (1 << SS) | (1 << MISO) | (1 << MOSI);
    DDRB  |= (1 << SS) | (1 << MOSI) | (1 << SCK);
}

int main(void)
{
    FATFS fs;
    FRESULT res;
    WORD s1;
    
    port_init();
    LCD_ini();
    
    clearLCD();
    
    setPos(0, 0);
    strLCD("Mount SD... ");
    res = pf_mount(&fs);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    setPos(0, 1);
    strLCD("Open file... ");
    res = pf_open("/123.txt");
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    //pointer
    setPos(0, 2);
    strLCD("Move pointer... ");
    res = pf_lseek(0); //pointer to 0 in file
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    //read
    setPos(0, 3);
    strLCD("Read file... ");
    res = pf_read(buffer2, 128, &s1);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(2000);
    
    clearLCD();
    setPos(0, 0);
    strLCD(buffer2);

    //unmount file system
    _delay_ms(1000);
    setPos(0, 1);
    strLCD("Unmount FS... ");
    res = pf_mount(0x00);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    setPos(0, 2);
    strLCD("Mount FS... ");
    res = pf_mount(&fs);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);

    setPos(0, 3);
    strLCD("Open file... ");
    res = pf_open("/123.txt");
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(2000);

    clearLCD();
    
    // write data
    setPos(0, 0);
    strLCD("Write data... ");
    sprintf(buffer2, "World Hello!");
    res = pf_write(buffer2, strlen(buffer2), &s1);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    setPos(0, 1);
    strLCD("Finalize... ");
    res = pf_write(0, 0, &s1); //finish writing
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    //unmount file system
    setPos(0, 2);
    strLCD("Unmount FS... ");
    res = pf_mount(0x00);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    //read changed text
    setPos(0, 3);
    strLCD("Mount SD... ");
    res = pf_mount(&fs);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(2000);
    
    clearLCD();
    
    setPos(0, 0);
    strLCD("Open file... ");
    res = pf_open("/123.txt");
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    //pointer
    setPos(0, 1);
    strLCD("Move pointer... ");
    res = pf_lseek(0); //pointer to 0 in file
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(1000);
    
    //read
    setPos(0, 2);
    strLCD("Read file... ");
    res = pf_read(buffer2, 128, &s1);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    _delay_ms(3000);
    
    setPos(0, 3);
    strLCD(buffer2);

    _delay_ms(2000);
    clearLCD();

    //unmount file system
    setPos(0, 0);
    strLCD("Unmount FS... ");
    res = pf_mount(0x00);
    if (res == FR_OK) strLCD("Done");
    else strLCD("Error");
    
    while (1)
    {
        

    }
}




