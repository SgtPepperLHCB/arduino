#ifndef __IRDEVICE_H__
#define __IRDEVICE_H__

#include "IRReceiver.h"
#include "IRTransmitter.h"

class IRDevice {
public:
  IRDevice ( IRDeviceProfile profile, IRTransmitter tx, IRReceiver rx, IRDeviceCommand* commands=NULL ) ;

  virtual void sendCode ( unsigned long data ) ;
  virtual void send ( IRDeviceCommand command ) ;

private:
  IRDeviceCommand*  _commands ;
  IRDeviceProfile   _profile ;
  IRReceiver        _rx ;
  IRTransmitter     _tx ;

} ; //-IRDevice

#endif