#include  <SoftwareSerial.h>

#define _XBEE_DEBUG

const int rx = 2 ;
const int tx = 3 ;
const long sp_baud_rate = 115200 ;
const long xb_baud_rate = 57600 ;  //must match xbee configuration.
const String ATTN = "this is the voice of colossus" ;

SoftwareSerial xbs( rx, tx ) ;

const int INPUT_BUFFER_SIZE = 64 ;
const char EOL = '\n' ;

void setup ( ) {
#ifdef _XBEE_DEBUG
  Serial.begin( sp_baud_rate ) ;
  Serial.println( ATTN ) ;
#endif
  xbs.begin( xb_baud_rate ) ;
} //-setup


String xbuffer ;
void loop ( ) {
  if ( readline(xbs, xbuffer) ) {
#ifdef _XBEE_DEBUG
    Serial.print( "RX:" ) ; Serial.print( xbuffer ) ; Serial.print(":") ; Serial.println( xbuffer.length() ) ;
#endif
    xbs.print( xbuffer ) ; xbs.write( EOL ) ;
    Serial.print( "TX:" ) ; Serial.print( xbuffer ) ; Serial.write( EOL ) ;
    xbuffer = "" ;
  }
} //-loop


boolean readline ( Stream& stream, String& buffer ) {
  int in ;
  if ( stream.available() ) {
    in = stream.read() ;
    if ( in == EOL ) {
      return true ;
    }
    buffer += (char)in ;
#ifdef _XBEE_DEBUG
    //Serial.print( "r_:" ) ; Serial.print( in ) ; Serial.print( ":" ) ; Serial.print( (char)in ) ; Serial.print( ":" ) ; Serial.print( buffer ) ; Serial.print( ":" ) ; Serial.println( buffer.length() ) ;
#endif
  } //-if.available

  return false ;
} //-readline
