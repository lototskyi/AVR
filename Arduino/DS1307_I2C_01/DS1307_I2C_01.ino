////////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: I2C protocol demo. Based on the Adafruit DS1307 demo from the RTClib library.


COMMENTS:  The demo boots, checks for RTC IC on I2C bus, then checks if the RTC is not running, if not
           then sets the time. After the demo simply reads the time with the API and prints it out in 
           a loop. Very few changes have been made to demo, mostly formatting to make reading easier.

HARDWARE SETUP:

Arduinio UNO              DS1307 RTC (Real Time Clock) Breakout board - Elegoo 37 in 1 Sensor kit version

Signal Name     Pin#      Signal Name     Pin #
____________________________________________________________

Power Connections (use any +5 and GND you wish from Arduino)
VCC (5V)        ANY       V+              VCC (labeled)
GND             ANY       GND             GND (labeled)

I2C Connections from Arduino to DS1307
SCL             D19       SCL             SCL (labeled)
SDA             D18       SDA             SDA (labeled)
      
Misc
                          SQWOUT          SQWOUT (labeled), connect to LED for indicator.
            

Note: pullups are on breakout board, so we don't need to add them to breadboard.

HISTORY: 

*/

// INCLUDES ///////////////////////////////////////////////

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Wire.h"     // I2C / 2-wire library
#include "RTClib.h"   // adafruit RTClib library

using namespace std;

// DEFINES ////////////////////////////////////////////////

// GLOBALS ////////////////////////////////////////////////

RTC_DS1307 rtc;  // rtc object

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////

void setup () 
{
Serial.begin(115200);


if (!rtc.begin()) 
  {
  Serial.println("Couldn't find RTC");
  Serial.flush();
  while (1) delay(10);
  } // end if

if (!rtc.isrunning()) 
  {
  Serial.println("RTC is NOT running, let's set the time!");
  // When time needs to be set on a new device, or after a power loss, the
  // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  } // end if

// When time needs to be re-set on a previously configured device, the
// following line sets the RTC to the date & time this sketch was compiled
// rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// This line sets the RTC with an explicit date & time, for example to set
// January 21, 2014 at 3am you would call:
// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

// set time to now using compile time or time of choice
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//rtc.adjust(DateTime(2023, 2, 10, 23, 0, 0));
  
} // end setup

////////////////////////////////////////////////////////////////////////////////////////

void loop () 
{
DateTime now = rtc.now();

Serial.print(now.month(), DEC);
Serial.print('/');
Serial.print(now.day(), DEC);
Serial.print('/');
Serial.print(now.year(), DEC);


Serial.print(" (");
Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
Serial.print(") ");

// convert from 24 hour to 12
if ( now.hour() <= 12 )
  Serial.print(now.hour(), DEC);
else
  Serial.print(now.hour()-12, DEC);

Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
Serial.println();

Serial.print(" since midnight 1/1/1970 = ");
Serial.print(now.unixtime());
Serial.print("s = ");
Serial.print(now.unixtime() / 86400L);
Serial.println("d");

// for fun, calculate a date which is 7 days, 12 hours, 30 minutes, and 6 seconds into the future
DateTime future (now + TimeSpan(7,12,30,6));

Serial.print(" now + 7d + 12h + 30m + 6s: ");
Serial.print(future.year(), DEC);
Serial.print('/');
Serial.print(future.month(), DEC);
Serial.print('/');
Serial.print(future.day(), DEC);
Serial.print(' ');
Serial.print(future.hour(), DEC);
Serial.print(':');
Serial.print(future.minute(), DEC);
Serial.print(':');
Serial.print(future.second(), DEC);
Serial.println();

Serial.println();
delay(1000);
} // end loop
