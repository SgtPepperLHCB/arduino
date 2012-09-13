#define __AVR_ATmega328P__

#include <binary.h>
#include <HardwareSerial.h>
#include <pins_arduino.h>
#include <WConstants.h>
#include <wiring.h>
#include <wiring_private.h>
#include <WProgram.h>
#include <EEPROM/EEPROM.h>
#include  <IRremote.h>

#define BAUD_RATE 115200

#define IRpin_PIN PIND
#define IRpin     2

#define MAXPULSE        32000 // Maximum pulse we'll listen for.
#define RESOLUTION_USEC 10    // Timing resolution.  Larger is better, but too large and you won't get accurate timing.

#define PULSE_ARRAY_DEPTH   100
uint16_t  pulses [ PULSE_ARRAY_DEPTH ] [ 2 ] ;  // Pair is high-low pulse.
uint8_t   currentPulse = 0 ;                    // Index into pulses we're storing.


void setup() {
  Serial.begin( BAUD_RATE ) ;
  Serial.print( IRpin_PIN ) ;
  Serial.println( "ok" ) ;
} //-setup

void loop() {
  uint16_t  highPulse, lowPulse ;
  highPulse = lowPulse = 0 ;

  // High-pulse detection.
  //while (digitalRead(IRpin) ) {   // Too slow
  while ( IRpin_PIN & (1 << IRpin) ) {  // while pin is still HIGH
    highPulse++ ; delayMicroseconds( RESOLUTION_USEC ) ;

    if ( (highPulse >= MAXPULSE) && (currentPulse != 0) ) {
      report() ;
      currentPulse = 0 ;
      return ;
    }
  }
  // We did not timeout, so save pulse reading.
  pulses[ currentPulse][0] = highPulse ;

  // Low-pulse detection.
  while ( !(IRpin_PIN & _BV(IRpin)) ) { // while pin is still LOW
    lowPulse++ ; delayMicroseconds( RESOLUTION_USEC ) ;
    if ( (lowPulse >= MAXPULSE) && (currentPulse != 0) ) {
      report() ;
      currentPulse = 0 ;
      return ;
    }
  }
  // We did not timeout, so save pulse reading.
  pulses[ currentPulse][1] = lowPulse ;

  // We've read one high-low pulse successfully, continue...
  currentPulse++ ;
   
} //-loop

//
// report() - write pulse array data to Serial.
void report ( ) {
  Serial.println( "\n\n" ) ;
  Serial.println( currentPulse ) ;  // Write number of pairs
  for ( uint8_t i = 0 ; i < currentPulse-1 ; ++i ) {
    Serial.print( pulses[i][1] * RESOLUTION_USEC / 10, DEC ) ;
    Serial.print( "," ) ;
    Serial.print( pulses[i][0] * RESOLUTION_USEC / 10, DEC ) ;
    Serial.println( "," ) ;
  }
  Serial.print( pulses[currentPulse-1][1] * RESOLUTION_USEC / 10, DEC ) ;
  Serial.println( ", 0" ) ;
}
