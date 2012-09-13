#ifndef __IRDEVICEPROFILE_H__
#define __IRDEVICEPROFILE_H__

class IRDeviceProfile {
public:
  int freqKHZ ;
  unsigned int bits ;
  unsigned int headerMark ;
  unsigned int headerSpace ;
  unsigned int bitMark ;
  //unsigned int zedMark ;
  unsigned int zedSpace ;
  //unsigned int oneMark ;
  unsigned int oneSpace ;
  //unsigned int footerMark ;
  unsigned int footerSpace ;
} ;

typedef unsigned long IRDeviceCommand ;

#endif