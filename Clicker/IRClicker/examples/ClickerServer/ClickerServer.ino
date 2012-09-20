#include <IRClicker.h>

enum {
  BAUD_RATE = 115200
} ;

IRTransmitter tx ;
IRReceiver    rx ;
IRDevice clicker( SymphonicTvVcrProfile, tx, rx, SymphonicTvVcrCommandCodes ) ;


void setup ( ) {
  Serial.begin( BAUD_RATE ) ;
  Serial.println( "ok" ) ;
}

void loop ( ) {
  while ( Serial.available( ) > 0 ) {
    int command = Serial.parseInt( ) ;
    if ( Serial.read( ) == '\n' ) {
      clicker.send( command ) ;
      Serial.println( command ) ;
    }
  }
}
