////////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: Edited version of FreeRTOS sample "Blink_AnalogRead" demo.

AUTHOR: Andre' LaMothe

COMMENTS: Just cleaned up code, to make easier to understand.
          
          This example code is in the public domain.

HISTORY: 

*/

////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES ////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino_FreeRTOS.h>


////////////////////////////////////////////////////////////////////////////////////////
// PROTOTYPES///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

// define tasks for Blink, AnalogRead, Print
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void TaskPrint(void *pvParameters);  

////////////////////////////////////////////////////////////////////////////////////////
// DEFINES /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

// for LED blink task
const uint8_t LED_pin    = 8; // use this pin to blink LED

////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS  //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
// the setup function runs once when you press reset or power the board
  
// initialize serial communication at 9600 bits per second:
Serial.begin(115200);

while(!Serial) 
      {
      ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
      } // end while

// Now set up 3 tasks to run independently.

// blinks the built in LED
xTaskCreate(TaskBlink
            ,"Blink"    // A name just for humans
            ,128        // This stack size can be checked & adjusted by reading the Stack Highwater
            ,NULL
            ,2          // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
            ,NULL );

// reads the analog pin and prints to terminal
xTaskCreate(TaskAnalogRead
            ,"AnalogRead"
            ,128       // Stack size
            ,NULL
            ,2         // Priority
            ,NULL );

// prints to the screen
xTaskCreate(TaskPrint
            ,"Print"    // A name just for humans
            ,128        // This stack size can be checked & adjusted by reading the Stack Highwater
            ,NULL
            ,2          // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
            ,NULL );

// prints to the screen
xTaskCreate(TaskPrint2
            ,"Print"    // A name just for humans
            ,128        // This stack size can be checked & adjusted by reading the Stack Highwater
            ,NULL
            ,2          // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
            ,NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.

} // end setup

////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  // Empty. Things are done in Tasks.
} // end loop

////////////////////////////////////////////////////////////////////////////////////////
// TASK FUNCTIONS  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void TaskPrint(void *pvParameters)  
{
  // this task simply prints to the terminal
  
  // this is redundant, you do NOT need to redeclare formal parms to a C function, but
  // these old FreeRTOS demo do this, so we will keep this pattern intact for posterity
  (void) pvParameters; 
  
  // note: this is an infinite loop! the OS will interrupt it to run other tasks!!!
  while(1) // A Task shall never return or exit.
      {
      Serial.write("\n\rPrint Task.....................\n\r");
      vTaskDelay( 250 / portTICK_PERIOD_MS ); // wait for 3 seconds
      } // end for 
} // end TaskPrint

////////////////////////////////////////////////////////////////////////////////////////

void TaskPrint2(void *pvParameters)  
{
  // this task simply prints to the terminal
  
  // this is redundant, you do NOT need to redeclare formal parms to a C function, but
  // these old FreeRTOS demo do this, so we will keep this pattern intact for posterity
  (void) pvParameters; 
  
  // note: this is an infinite loop! the OS will interrupt it to run other tasks!!!
  while(1) // A Task shall never return or exit.
      {
      Serial.write("\n\rPrint Task #2.....................\n\r");
      vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for 3 seconds
      } // end for 

} // end TaskPrint2

////////////////////////////////////////////////////////////////////////////////////////


void TaskBlink(void *pvParameters)  
{
  // this is redundant, you do NOT need to redeclare formal parms to a C function, but
  // these old FreeRTOS demo do this, so we will keep this pattern intact for posterity
  (void) pvParameters; 
  
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, LEONARDO, MEGA, and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  
  The MICRO does not have a LED_BUILTIN available. For the MICRO board please substitute
  the LED_BUILTIN definition with either LED_BUILTIN_RX or LED_BUILTIN_TX.
  e.g. pinMode(LED_BUILTIN_RX, OUTPUT); etc.
  
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_pin, OUTPUT);

  // note: this is an infinite loop! the OS will interrupt it to run other tasks!!!
  while(1) // A Task shall never return or exit.
      {
      digitalWrite(LED_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
      vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for one second
      digitalWrite(LED_pin, LOW);    // turn the LED off by making the voltage LOW
      vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for one second
      } // end for 
      
} // end TaskBlink

////////////////////////////////////////////////////////////////////////////////////////

void TaskAnalogRead(void *pvParameters)
{
  // this is redundant, you do NOT need to redeclare formal parms to a C function, but
  // these old FreeRTOS demo do this, so we will keep this pattern intact for posterity
  (void) pvParameters; 
  
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

  // note: this is an infinite loop! the OS will interrupt it to run other tasks!!!
  while(1)
      {
      // read the input on analog pin 0:
      int sensorValue = analogRead(A0);
      // print out the value you read:
      Serial.println(sensorValue);
      vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
      } // end for

} // end TaskAnalogRead 
