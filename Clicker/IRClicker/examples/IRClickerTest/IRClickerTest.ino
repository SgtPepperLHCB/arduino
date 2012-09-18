#include <IRClicker.h>

enum {
  BAUD_RATE = 115200
} ;

IRTransmitter tx ;
IRReceiver    rx ;
IRDevice clicker( SymphonicTvVcrProfile, tx, rx, SymphonicTvVcrCommandCodes ) ;
int counter = 0 ;
int counterMax = 1 ;

void setup ( ) {
  Serial.begin( BAUD_RATE ) ;
  Serial.println( "ok" ) ;
}

void loop ( ) {
  for ( ; counter < counterMax ; ++counter ) {
    delay( 3000 ) ;
    //( counter % 2 ) ? tx.send( SymphonicTvVcr, Symph_ChannelUp ) : tx.send( SymphonicTvVcr, Symph_ChannelDn ) ;
    clicker.sendCode( Symph_Power ) ; delay( 6000 ) ;
    
    clicker.send( SYMPH_CHANNEL_UP ) ; delay( 3000 ) ;
    clicker.send( SYMPH_CHANNEL_DN ) ; delay( 3000 ) ;
    clicker.send( SYMPH_1 ) ; delay( 1000 ) ;
    clicker.send( SYMPH_2 ) ; delay( 3000 ) ;
    clicker.send( SYMPH_GAME ) ; delay( 3000 ) ;
    clicker.send( SYMPH_GAME ) ; delay( 3000 ) ;
    
    clicker.send( SYMPH_MENU ) ; delay( 1000 ) ;
    clicker.send( SYMPH_VCR_STOP ) ; delay( 500 ) ;
    clicker.send( SYMPH_VCR_STOP ) ; delay( 500 ) ;
    clicker.send( SYMPH_DN ) ; delay( 500 ) ;
    clicker.send( SYMPH_UP ) ; delay( 500 ) ;
    clicker.send( SYMPH_MENU ) ; delay( 500 ) ;
    
    clicker.send( SYMPH_POWER ) ; delay( 6000 ) ;
  }
}
