#include "IRTransmitter.h"

//#define IR_DEBUG

void IRTransmitter::send ( unsigned int buffer[], int length, int khz ) {
  enableIROut( khz ) ;
  for ( int i = 0 ; i < length ; ++i ) {
    (i & 1) ? space( buffer[i] ) : mark( buffer[i] ) ;
  }
  space( 0 ) ; // Just to be sure it is off
} //-send

void IRTransmitter::send ( IRDeviceProfile profile, unsigned long data ) {
#ifdef IR_DEBUG
  Serial.println( data, HEX ) ;
#endif
  enableIROut( profile.freqKHZ ) ;

  mark( profile.headerMark ) ;
  space( profile.headerSpace ) ;

  data = data << (32 - profile.bits) ;
  for ( unsigned int i = 0 ; i < profile.bits ; ++i ) {
    if ( data & TOPBIT ) {
      mark( profile.bitMark ) ;
      space( profile.oneSpace ) ;
    } else {
      mark( profile.bitMark ) ;
      space( profile.zedSpace ) ;
    }
    data <<= 1 ;
  }

  mark( profile.bitMark ) ;
  space( profile.footerSpace ) ;
}

//
// Private methods
//

void IRTransmitter::enableIROut ( int khz ) {
  // Disable timer interrupt
  TIMER_DISABLE_INTR ;
  pinMode( TIMER_PWM_PIN, OUTPUT ) ;
  digitalWrite( TIMER_PWM_PIN, LOW ) ;
  TIMER_CONFIG_KHZ( khz ) ;
}

//
// mark - output (modulated)
//

void IRTransmitter::mark ( int usec ) {
#ifdef IR_DEBUG
  Serial.println( usec ) ; //Serial.print( "m" ) ;
#endif
  TIMER_ENABLE_PWM ;
  delayMicroseconds( usec ) ;
}

//
// space - no output
//

void IRTransmitter::space ( int usec ) {
#ifdef IR_DEBUG
  Serial.println( usec ) ; //Serial.print( "s" ) ;
#endif
  TIMER_DISABLE_PWM ;
  delayMicroseconds( usec ) ;
}
