////////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: VT100 animation demo.

AUTHOR: Andre' LaMothe

COMMENTS: 

VT100 commands can be found here:

http://www.braun-home.net/michael/info/misc/VT100_commands.htm

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

#include "CCAMD_VT100_Lib.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// DEFINES AND MACROS
////////////////////////////////////////////////////////////////////////////////////////

// GPIO pins we are connecting dpad momentary switches to
#define DPAD_UP_PIN     12
#define DPAD_DOWN_PIN   11
#define DPAD_LEFT_PIN   10
#define DPAD_RIGHT_PIN  9

////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS
////////////////////////////////////////////////////////////////////////////////////////

// this holds strings we build up for this and that
char gStringBuffer[ 64 ];

// this holds our array of characters we want to animate thru each frame
uint8_t ditherChars[ 4 ] = { 
                            ASCII_BLOCK_DITHERED_LIGHT, 
                            ASCII_BLOCK_DITHERED_MEDIUM, 
                            ASCII_BLOCK_DITHERED_DARK, 
                            ASCII_BLOCK_SOLID
                            };

////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  // the setup function runs once when you press reset or power the board  

  // initialize serial port
  Serial.begin(115200);

  // boot our computer...
  VT100_Boot();
  delay( 3000 );

  // print prompt
  VT100_SetCursor( 12, 0 );
  Serial.write( "\n\rReady:" );

  // hide the cursor
  VT100_SendCmd( VT100_HIDE_CURSOR );

  // Set up dpad inputs connected to momentary switches as inputs with pullups
  pinMode(DPAD_UP_PIN, INPUT_PULLUP);
  pinMode(DPAD_DOWN_PIN, INPUT_PULLUP);
  pinMode(DPAD_LEFT_PIN, INPUT_PULLUP);
  pinMode(DPAD_RIGHT_PIN, INPUT_PULLUP);

} // end setup

////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{

  // enable/disable this if you want to play with the VT100 "snake" prototype game :)
  #if 1

  // game loop - erase move draw repeat...

  // create local static variables that persist each call, only other option is to make them globals
  static int player_x = 40;
  static int player_y = 12;
  static int playerAnimCount = 0;

  // read the dpad (momentary switches), active LOW
  if ( digitalRead( DPAD_UP_PIN ) == 0 )
    player_y--;
  else
  if ( digitalRead( DPAD_DOWN_PIN ) == 0 )
    player_y++;

  if ( digitalRead( DPAD_RIGHT_PIN ) == 0 )
    player_x++;
  else
  if ( digitalRead( DPAD_LEFT_PIN ) == 0 )
    player_x--;

  // perform screen bounds checks...

  // animated the player
  if (++playerAnimCount >= 4 )
    playerAnimCount = 0;


  // clear the screen
  VT100_ClearScreen();

  // draw the player at new position
  VT100_SetCursor( player_y, player_x );
  Serial.write( ditherChars[ playerAnimCount ] );

  // pause a moment...
  delay( 100 );

  #endif

  // return to main() for a moment, let arduino API do its thing...

} // end loop

/////////////////////////////////////////////////////////////////////////////////////////
