#ifndef __IRTRANSMITTER_H__
#define __IRTRANSMITTER_H__

#include  <Arduino.h>
#include "IRClickerInt.h"
#include "IRDeviceProfile.h"


class IRTransmitter {
public:

  IRTransmitter ( ) {
  }

  void send ( unsigned int buffer[], int length, int khz ) ;
  void send ( IRDeviceProfile profile, unsigned long data ) ;

private:
  void enableIROut ( int khz ) ;
  void mark ( int usec ) ;
  void space ( int usec ) ;

} ; //-IRTransmitter

#endif
