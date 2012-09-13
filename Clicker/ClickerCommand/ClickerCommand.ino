#include <avr/io.h>
#include <avr/pgmspace.h>
#include <IRremote.h>
#include "SymphonicTV_VCR.h"

enum { BAUD_RATE        = 115200 } ;
enum { IR_FREQ_KHZ      = 38 } ;
enum { MAX_BUFFER_SIZE  = 64 } ;

IRsend irsend ;
uint16_t buffer[ MAX_BUFFER_SIZE ] ;

//
// Setup serial, etc.
//

void setup() {
  Serial.begin( BAUD_RATE ) ;
  Serial.println( "ok" ) ;
}

//
// Loop forever.
//

boolean forever = true ;

void loop ( ) {

  if ( forever ) {
    for ( int i = 0 ; i < symphCMD_COUNT ; ++i ) {
      memcpy_P( buffer, &symphonicTvVcrClicker[i], symphCMD_SIZE_BYTES ) ;
      unsigned long data = 0 ;
      for ( int j = 3 ; j < symphCMD_SIZE ; j+=2 ) {
        if ( buffer[j] > 2000 ) {
          data |= 1 ;
        } else {
          data |= 0 ;
        }
        //Serial.print( i ) ; Serial.print(",") ; Serial.print(j) ; Serial.print(",") ; Serial.print(buffer[j]) ; Serial.print( "=" ) ; Serial.println( data, BIN ) ;
        data <<= 1 ;
      }
      data >>= 1 ;
      Serial.print( i ) ; Serial.print( "=" ) ; Serial.println( data, HEX ) ;
    }
    forever = false ;

  }
  /*
    while ( Serial.available() > 0 ) {
      int command = Serial.parseInt() ;
      if ( Serial.read() == '\n' ) {
        // Copy command out of PROGMEM into local buffer.
        memcpy_P( buffer, &symphonicTvVcrClicker[command], symphCMD_SIZE_BYTES ) ;
        irsend.sendRaw( buffer, symphCMD_SIZE, IR_FREQ_KHZ ) ;
        Serial.println( command ) ;
      }
    }
   * */

} //-loop
