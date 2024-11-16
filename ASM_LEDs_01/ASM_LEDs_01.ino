////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES 
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

volatile uint8_t pinCounter = 1;

void setup() {
  Serial.begin(115200);
  Serial.write( "\n\rSetup Complete.\n\r" );

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {

//memory operation
#if 0
  asm volatile("push r16");               // save the registers we use to stack
  asm volatile("lds r16, pinCounter");    // read pinCounter from C/C++ globals and store into r16
  // asm volatile("sts (0x05+0x20), r16");// write r16 to PORTB using memory operation, so add 0x20 to address
  asm volatile("out 0x05, r16");          // write r16 to PORTB using IO operation, so add 0x20 to address
  asm volatile("pop r16");                // restore registers from stack

  pinCounter = pinCounter << 1;

  if (pinCounter >= 0x10) {
    pinCounter = 1;
  }

  delay(250);
#endif


#if 0
  asm volatile ("   push r16");              // save registers on stack
  asm volatile ("   push r17");
  asm volatile ("   push r18");

  asm volatile ("   ldi r16, 0x01");        // load r16 0x01 so we can shift it to the left each iteration
  asm volatile ("   lds r17, pinCounter");  // r17 will be loop counter, load C/C++ var pinCounter into it
  asm volatile ("shift_loop:");             // even in inline asm we can create labels
  asm volatile ("   cpi r17, 0x00");        // we want to do this C/C++ operation basically: r16 = r16 << pinCounter
  asm volatile ("   breq shift_done");      // this short loop accomplishes that we test the loop counter r17 each
  asm volatile ("   lsl r16");              // iteration, if not equal to 0, we shift left to the bitmask in r16 and
  asm volatile ("   dec r17");              // continue. More advanced processor can do this in single instruction!
  asm volatile ("   rjmp shift_loop");
  asm volatile ("shift_done:");             // when the loop is done, we have a bitmask in r16 that we can then write into
  asm volatile ("   sts (0x05+0x20), r16"); // an IO port, in this case, we use PORTB @ 0x05, and since we are using
                                            // memory addressing instruction and not the OUT instruction, we need to add 0x20
  asm volatile ("   pop r18");              // finaly restore the registers from the stack
  asm volatile ("   pop r17");
  asm volatile ("   pop r16");

  // update C/C++ global
  if (++pinCounter >= 4 )
    pinCounter = 0;

  delay( 250 );
#endif


#if 0
  asm volatile("push r16");
  asm volatile("in r16, 0x09");         // read PIND into r16
  asm volatile("lsr r16");
  asm volatile("lsr r16");
  asm volatile("com r16");
  asm volatile("andi r16, 0x03");       // mask and write value back out to PORTB 
  asm volatile("out 0x05, r16");        
  asm volatile("pop r16");

Serial.print("\nPush button demo");
delay(100);

#endif


#if 1
  // basically C/C++ version of ASM below..
  // Serial.write( pinCounter + ' ' );

  // this code writes out to the UART, assumes it's been initialized and running already
  asm volatile("    push r24");            // save registers on stack, but don't really need to based on register addresses
  asm volatile("    push r25");              
  asm volatile("    push r18");              

  asm volatile("USART_Transmit:");
  asm volatile("    lds r18, 0xC0");       // Wait for empty transmit buffer, check UDRE0 flag in USART0 control/status
  asm volatile("    sbrs r18, 0x05");
  asm volatile("    rjmp USART_Transmit");

  asm volatile("    lds r24, pinCounter"); // Copy data into buffer register
  asm volatile("    adiw r24, ' '");       // add ASCII ' ', i.e. space character
  asm volatile("    sts 0xC6, r24");       // write data to transmit buffer UDR0

  asm volatile("    pop r18");             // restore registers from stack
  asm volatile("    pop r25");            
  asm volatile("    pop r24");            

  // update C/C++ global
  if (++pinCounter > 95 )
    pinCounter = 0;

  // print newline every few chars...
  if ( ( pinCounter % 32 ) == 0 )
    Serial.write('\n');

  delay( 50 );

#endif


}
