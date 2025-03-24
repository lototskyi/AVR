////////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: I2C protocol demo. Using the Wire.h library only, directly writes to the AD5241
             digital POT. Shows how to access the IC without a high level API driver.
                           

AUTHOR: Andre' LaMothe

COMMENTS:  To write to the POT, we need to send the slave address, followed by the command byte, followed
           by the data to write. Referring to the datasheet @ 
           
           https://www.analog.com/media/en/technical-documentation/data-sheets/ad5241_5242.pdf

           take a look below at the entire communication frame:

I2C Frame Bits
_____________________________________________________________________________________________________________
             Byte 0 - Address              Byte 1 - Command                 Byte 2 - Data
| Start | 0 1 0 1 1 AD1 AD0 R/W | Ack | A/B RS SD O1 O2 X X X | Ack | D7 D6 D5 D4 D3 D2 D1 D0 | Ack | Stop |
_____________________________________________________________________________________________________________

Slave Address Byte Instruction Byte Data Byte

where:

Start = start condition
Stop = stop condition
Ack = acknowledge
X = don’t care
AD1, AD0 = Package pin programmable address bits. Must be matched with the logic states at Pin AD1 and Pin AD0.
R/W = Read enable at high and output to SDA. Write enable at low.
A/B = RDAC subaddress select; 0 for RDAC1 and 1 for RDAC2.
RS = Midscale reset, active high.
SD = Shutdown in active high. Same as except inverse logic.
O1, O2 = Output logic pin latched values
D7, D6, D5, D4, D3, D2, D1, D0 = data bits.

Focusing on Byte 1, the command byte:

A/B RS SD O1 O2 X X X

* We want RDAC1 (there is only 1 DAC in the AD5241), so A/B = 0
* We do NOT want reset, NOR shutdown, so we set RS=0, SD=0
* O1 and O2 are crude GPIOs, we can set them to anything, so that's cool.

Then following the Command byte, we simply send the data byte 3 to set the RDAC for the POT
          

HARDWARE SETUP:

Arduinio UNO              AD5241 Digital POT (I2C version), Analog Devices, hand soldered breakout board

Signal Name     Pin#      Signal Name     Pin #
____________________________________________________________

Power Connections (use any +5 and GND you wish from Arduino)
VCC (5V)        ANY       VDD             4
GND             ANY       DGND            10 
GND             ANY       VSS             11
Note: IC has two grounds at pins 10,11

I2C Connections from Arduino AD5421
SCL             D19       SCL             6
SDA             D18       SDA             7

POT and Addressing Signals on the AD5421 (no connection to arduino)
                          A1              1 (POT terminal A)
                          W1              2 (POT wiper)
                          B1              3 (POT terminal B)

                          AD0             8 (I2C address bit 0)
                          AD1             9 (I2C address bit 1)
Note: AD1.AD0 allow us to set the lower 2-bits of the AD5421's I2C address, see datasheet for details.

Note: pullups are on not on breakout board, so this IC has no pullups, however, other breakouts on the bus have pullups.
      so, we can do without pullups, else, on the bus itself, we can add 10K pullup to add a bit to the system.

HISTORY: 

*/

////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES 
////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Wire.h"     // I2C / 2-wire library


using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// PROTOTYPES
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// DEFINES AND MACROS
////////////////////////////////////////////////////////////////////////////////////////

// careful, address is always 8 bit total,  7-bit address  with LSB acting as r/w bit select, 
// so when giving these addresses from datasheet, make sure you shift the address right or left one bit, so the 
// resulting address is in correct position, #1 problem with I2C -- wrong address, off by 1 bit!

// 0 1 0 1 1 AD1 AD0 + R/Wn
// AD1 and AD0 are set via pins 10,11 respectively, assuming we set to 00, we get the following slave address:

// 0 1 0 1 1 0 0 + R/Wn

// finally, we omit the R/Wn bit for a moment and right shift the address to compute the 7-bit address:

// 0010.1100 = 0x2C

// we will see this when we look at the logic analyzer packet decode in lecture
const uint8_t AD5241_I2C_SlaveAddress = 0x2C; 

////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS
////////////////////////////////////////////////////////////////////////////////////////

char gStringBuffer[64]; // used for printing

////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
// initialize serial port
Serial.begin(115200);
Serial.write( "\n\AD5241 Digital POT Demo -- Slowly turns the digital POT.\n\r" );

// call the begin method with or without the slave address
Wire.begin();  // if you want to change something and restart lib, call Wire.end();

// set clock to base frequency, 10K - 400K
Wire.setClock( 100000 );
} // end setup

//////////////////////////////////////////////////////////

void loop() 
{

static uint8_t potSetting = 0x80;  // the POT setting 0..255 maps to 0 to 1M ohm (or whatever size your POT is)
static uint8_t ioPins = 0x00;      // the two low bits are written to the IO bits IO0 and IO1

// start the transmission, send 7-bit address
Wire.beginTransmission( AD5241_I2C_SlaveAddress ); 

// set the command register (see notes above in header on bits)
// Command byte = A/B RS SD O1 O2 X X X
// Select RDAC 0, so A/B=0, no reset, no shutdown, RS=0, and set GPIO pins O1 and O2 to 0s
// therefore, command byte should look like 00000.xxx, set don't cares to 0 as well, final command = 00000000
Wire.write( (0b00000 | ioPins & (0x3) ) << 3 );  

// next write the POT value 0..0xFF
Wire.write( potSetting );   

// end the transaction
Wire.endTransmission();   

sprintf( gStringBuffer, "\nPOT register = %d, POT value = %d Kohms",potSetting, (int) ( 0.5f + 1000*(float)potSetting/255.0f ));
Serial.write( gStringBuffer );

// increment POT setting, it will wrap around itself since 8-bit value
potSetting++;

// increment the GPIO counter
ioPins++;

delay(100);
} // end loop
