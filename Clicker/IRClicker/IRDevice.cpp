#include "IRDevice.h"

IRDevice::IRDevice ( IRDeviceProfile profile, IRTransmitter tx, IRReceiver rx, IRDeviceCommand* commands ) {
  _profile = profile ;
  _tx = tx ;
  _rx = rx ;
  _commands = commands ;
}

void IRDevice::sendCode ( unsigned long data ) {
  _tx.send( _profile, data ) ;
}

void IRDevice::send ( IRDeviceCommand command ) {
  _tx.send( _profile, _commands[command] ) ;
}
