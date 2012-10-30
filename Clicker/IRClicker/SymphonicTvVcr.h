#ifndef __SYMPHONICTVVCR_H__
#define __SYMPHONICTVVCR_H__

// Symphonic TV/VCR model=SC313E
//                                       khz  bt  h_mk  h_sp  b_m  z_s  1_s   f_s
IRDeviceProfile SymphonicTvVcrProfile = { 38, 24, 3400, 3400, 880, 820, 2500, 0 } ;
IRDeviceCommand SymphonicTvVcrCommandCodes [] = {
  0x141EBE, // power
  0x168E97, // wake-up/sleep 
  0x16FE90, // eject
  0x17EE81, // 1
  0x161E9E, // 2
  0x151EAE, // 3
  0x95C6A3, // channel return
  0x171E8E, // 4
  0x149EB6, // 5
  0x169E96, // 6
  0x142EBD, // channel up
  0x159EA6, // 7
  0x179E86, // 8
  0x145EBA, // 9
  0x144EBB, // channel down
  0x165E9A, // 0
  0x36FC90, // +100
  0x143EBC, // volume up
  0x16AE95, // menu
  0x158EA7, // display
  0x173E8C, // mute
  0x163E9C, // volume down
  0x14CEB3, // rew
  0x154EAB, // play
  0x148EB7, // ffwd
  0x14EEB1, // stop
  0x156EA9, // record
  0x377C88, // speed
  0x174E8B, // pause/still
  0x17CE83, // clear/reset counter
  0x96B694, // game
  0x15CEA3, // time search
} ;

#endif
