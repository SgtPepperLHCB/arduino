#include <IRremote.h>

#define BAUD_RATE 115200
const unsigned int  IR_RECEIVER_PIN = 3 ;

IRrecv ir_receiver( IR_RECEIVER_PIN ) ;
decode_results results ;

void setup ( ) {
  Serial.begin( BAUD_RATE ) ;
  ir_receiver.enableIRIn() ;
  Serial.println( "ok" ) ;
}

void dump ( const decode_results* results ) {
  const int protocol = results->decode_type ;
  Serial.print( "protocol:" ) ;
  if ( protocol==UNKNOWN) {
    Serial.println ("UNK" ) ;
  } else {
    if ( protocol==NEC ) {
      Serial.println( "NEC" ) ;
    } else if ( protocol==SONY ) {
      Serial.println( "SONY" ) ;
    } else if ( protocol==RC5  ) {
      Serial.println( "RC5" ) ;
    } else if ( protocol==RC6  ) {
      Serial.println( "RC6" ) ;
    }
  }
    Serial.print( "v:" ) ;
    Serial.print( results->value, HEX ) ;
    Serial.print( ", " ) ;
    Serial.print( results->bits, DEC ) ;
    Serial.println( " bits" ) ;
}

void loop ( ) {
  if ( ir_receiver.decode(&results) ) {
    dump( &results ) ;
    ir_receiver.resume() ;
  }
}
