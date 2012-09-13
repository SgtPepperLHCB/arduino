// Raw IR decoder sketch!
//
// This sketch/program uses an Arduno and a GP1UX311QS to decode IR received.
// This can be used to make a IR receiver (by looking for a particular code)
// or transmitter (by pulsing an IR LED at ~38KHz for the durations detected.
//
// Code is public domain, check out www.ladyada.net and adafruit.com
// for more tutorials!
//
// We need to use the 'raw' pin reading methods because timing is
// very important here and the digitalRead() procedure is too slow.
//
// Digital pin #4 is the same as Pin D4 see
// http://arduino.cc/en/Hacking/PinMapping168 for 'raw' pin mapping.

//#define PRINT_RECEIVED
#define PRINT_C_ARRAY

#define USECPERTICK 50  // usec per clock interrupt tick
#define MARK_EXCESS 100 // length of raw duration buffer
#define TOLERANCE 25  // percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.) 
#define UTOL (1.0 + TOLERANCE/100.) 

#define _GAP 5000 // Minimum map between transmissions
#define GAP_TICKS (_GAP/USECPERTICK)

#define TICKS_LOW(us) (int) (((us)*LTOL/USECPERTICK))
#define TICKS_HIGH(us) (int) (((us)*UTOL/USECPERTICK + 1))

#ifndef DEBUG
int MATCH(int measured, int desired) {return measured >= TICKS_LOW(desired) && measured <= TICKS_HIGH(desired);}
int MATCH_MARK(int measured_ticks, int desired_us) {return MATCH(measured_ticks, (desired_us + MARK_EXCESS));}
int MATCH_SPACE(int measured_ticks, int desired_us) {return MATCH(measured_ticks, (desired_us - MARK_EXCESS));}
// Debugging versions are in IRremote.cpp
#endif



enum { BAUD_RATE = 115200 } ;
enum { 
  IRpin = 4 } 
;

// Maximum number of transitions that can be recorded.
// We will store up to 100 pulse pairs (this is a lot).
enum { 
  MAX_TRANSITIONS = 200 } 
;
uint16_t  transitions [MAX_TRANSITIONS];
uint8_t   keyNum = 0 ;

void setup (void) {
  Serial.begin( BAUD_RATE ) ;
  Serial.println( "ClickerCaptureRAW.ino" ) ;
}

void loop (void) {
  uint16_t delays;
  int16_t idx = -1;

  // Mask to access IR input quickly.
  enum { 
    IRpinmask = _BV (IRpin)   };

  // The maximum transition time we'll listen for.  65 milliseconds is a long time.
  enum { 
    MAX_DELAY = 65000   } 
  ;  // Milliseconds

  // What our timing resolution should be, larger is better as it's
  // more 'precise' but too large and you wont get accurate timing.
  enum { 
    RESOLUTION = 5   } 
  ;  // Milliseconds

  for (;;) {
    if ( Serial.available() > 0 ) {
      keyNum = 0 ;
      Serial.read() ;
      Serial.println( "reset\n\n" ) ;
    }
    delays = 0;

    // Wait for a transition from HIGH to LOW.
    while ((PIND & IRpinmask))  {  // Using "digitalRead (IRpin)" is too slow.
      // Pin is still HIGH, delay.
      delayMicroseconds (RESOLUTION);
      if ((delays += RESOLUTION) < MAX_DELAY)
        continue;

      // Pulse is too long, we 'timed out'.  NOTHING was received or the transmitted
      // code is complete.  Print what we've captured so far, and then reset.
      printtransitions (idx);
      return;
    }

    // We didn't time out, store the reading.
    transitions [idx += 1] = delays;

    delays = 0;

    // Similar to above, except waiting for a transition HIGH.
    while (!(PIND & IRpinmask)) {
      // Pin is still LOW, delay.
      delayMicroseconds (RESOLUTION);
      if ((delays += RESOLUTION) < MAX_DELAY)
        continue;

      printtransitions (idx);
      return;
    }

    // We read a high-low-high pulse successfully, continue!
    transitions [idx += 1] = delays;
  }
}

void printtransitions (int16_t idx) {
  if (idx < 0)
    return;
#ifdef PRINT_RECEIVED
  Serial.print("\nReceived: " ) ; Serial.println( idx ) ;
  Serial.println("   H->L       L->H, ");

  for (uint8_t i = 0; i <= idx; i += 1) {
    uint32_t j = transitions [i];

    while ((j *= 10) < 100000)  // Columnize values nicely
      Serial.print (" ");

    Serial.print (transitions [i], DEC);
    Serial.print (i & 1 ? " usec\n" : " usec ");  // Newline after printing duration for L->H transition.
  }
#endif
 
#ifdef PRINT_C_ARRAY
  //Print as C array, skipping first value.
  //Next two are header mark/space
  uint8_t step = 4 ;
  Serial.print( "{ //" ) ; Serial.print( keyNum ) ; Serial.print( "," ) ; Serial.print( idx ) ; Serial.print( "\n" ) ;
  ++keyNum ;
  uint16_t value ;
  
  //Header mark/space
  value = transitions[ 1 ] ;
  printSpaces( value ) ;
  Serial.print( value, DEC ) ; Serial.print( "," ) ;
  value = transitions[ 2 ] ;
  printSpaces( value ) ;
  Serial.print( value, DEC ) ; Serial.print( "," ) ;
  Serial.println( "" ) ;
  
  for ( uint8_t i = 3 ; i <= idx ; i+=step ) {
    //Serial.print( "  " ) ;
    for ( uint8_t j = 0 ; j < step ; ++j ) {
      if ( (i+j) <= idx ) {
        value = transitions[ i + j ] ;
        printSpaces( value ) ;
        Serial.print( value, DEC ) ; Serial.print( "," ) ;
      }
    }
    Serial.print( "\n" ) ;
  }
  Serial.print( "},\n" ) ;
#endif
  int offset = 1 ;
  if ( match(transitions[offset], 8500, 50 ) ) {
    Serial.println( "H_mk" ) ;
  }
  ++offset ;
  if ( match(transitions[offset], 4200, 50 ) ) {
    Serial.println( "H_sp" ) ;
  }
  ++offset ;
}

boolean match ( int measured, int desired, int tolerance ) {
  return (measured > (desired - tolerance)) && (measured < (desired + tolerance)) ;
}

void printSpaces( int32_t value ) {
  while ( (value *= 10) < 100000 ) {
    Serial.print( " " ) ;
  }
}
