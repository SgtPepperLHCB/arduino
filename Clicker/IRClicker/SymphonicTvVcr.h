#ifndef __SYMPHONICTVVCR_H__
#define __SYMPHONICTVVCR_H__

// Symphonic TV/VCR model=SC313E
////                                        khz b   h_mk  h_sp  z_m  z_s  1_m  1_s   f_m  f_s
//IRDeviceProfile SymphonicTvVcrProfile = { 38, 24, 3400, 3400, 880, 820, 880, 2500, 880, 0 } ;
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

enum SymphonicTvVcrCommands {
  SYMPH_POWER,
  SYMPH_WAKE_UP_SLEEP,
  SYMPH_EJECT,

  SYMPH_1,
  SYMPH_2,
  SYMPH_3,
  SYMPH_CHANNEL_RETURN,

  SYMPH_4,
  SYMPH_5,
  SYMPH_6,
  SYMPH_CHANNEL_UP,

  SYMPH_7,
  SYMPH_8,
  SYMPH_9,
  SYMPH_CHANNEL_DN,

  SYMPH_0,
  SYMPH_100,
  SYMPH_VOLUME_UP,

  SYMPH_MENU,
  SYMPH_DISPLAY,
  SYMPH_MUTE,
  SYMPH_VOLUME_DN,

  SYMPH_VCR_REWIND,
  SYMPH_VCR_PLAY,
  SYMPH_VCR_FAST_FWD,
  SYMPH_VCR_STOP,

  SYMPH_VCR_RECORD,
  SYMPH_VCR_SPEED,
  SYMPH_VCR_PAUSE,

  SYMPH_CLEAR_RESET,
  SYMPH_GAME,
  SYMPH_VCR_TIME_SEARCH,

  SYMPH_UP = SYMPH_VCR_PLAY,
  SYMPH_DN = SYMPH_VCR_STOP,
  SYMPH_LF = SYMPH_VCR_REWIND,
  SYMPH_RT = SYMPH_VCR_FAST_FWD,
} ;
unsigned long Symph_Power = 0x141ebe ;

#endif
