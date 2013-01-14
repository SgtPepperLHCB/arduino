#include <SPI.h>         
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <Time.h>

//
// Ethernet
//
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xCA } ;

unsigned int localPort = 8888;      // local port to listen for UDP packets

IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov NTP server
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov NTP server
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov NTP server

const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 bytes of the message
enum { NTP_UPDATE_CYCLE = 60*60 } ;

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 

// A UDP instance to let us send and receive packets over UDP
EthernetUDP udp ;


//
// Lcd
//
enum {
  LCD_COLS = 16,
  LCD_ROWS = 2,
  LCD_WHITE = 0x07
} ;
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield() ;
int s0 ;
unsigned long g_epoch ;
bool g_epoch_sync ;
uint8_t c ;
char databuff[ LCD_COLS * 2 ] ;
char dispbuff[ LCD_COLS + 1 ] ;


//
// setup
//
void setup() {
  Serial.begin( 9600 ) ;
  Serial.println( "ok" ) ;
  lcd.begin( LCD_COLS, LCD_ROWS ) ;
  lcd.setBacklight( LCD_WHITE ) ;
  lcd.setCursor( 0, 0 ) ;
  lcd.print( "hello, world" ) ;
  s0 = 0 ;

  // start Ethernet and UDP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  udp.begin(localPort);
  g_epoch = ntpTime() ;
  g_epoch_sync = true ;
} //-setup


//
// main loop
//
void loop() {
  // Only update if seconds change.
  if ( now() > s0 ) {
    s0 = now() ;
    g_epoch++ ;
    g_epoch_sync = ( 0 == (g_epoch % NTP_UPDATE_CYCLE) ) ;
    if ( g_epoch_sync ) {
      g_epoch = ntpTime() ;
    }
    displayDigitalClock( g_epoch, g_epoch_sync ) ;
  }

  uint8_t buttons = lcd.readButtons();
  if ( buttons ) {
    lcd.setCursor(14,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP");
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DN");
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LF");
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RT");
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SL");
    }
  }
  
  delay( 250 ) ;
} //-loop

void displayDigitalClock ( unsigned long epoch, bool epoch_sync ) {
    // Digital Clock
    sprintf( databuff, "%02d-%3s-%04d %1s", day(epoch), monthShortStr(month(epoch)), year(epoch), (epoch_sync) ? "*" : " " ) ;
    sprintf( dispbuff, "%-16s", databuff ) ;
    lcd.setCursor( 0, 0 ) ;
    lcd.print( dispbuff ) ;
   
    // display time on line 1
    sprintf( databuff, "%02d:%02d:%02d %2s utc", hourFormat12(epoch), minute(epoch), second(epoch), isAM(epoch) ? "AM" : "PM" ) ;
    sprintf( dispbuff, "%-16s", databuff ) ;
    lcd.setCursor(0, 1) ;
    lcd.print( dispbuff ) ;
}

unsigned long ntpTime ( ) {
  unsigned long epoch = 0 ;
  sendNTPpacket(timeServer); // send an NTP packet to a time server

  // wait to see if a reply is available
  delay(1000);  
  if ( udp.parsePacket() ) {  
    udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;  
    // now convert NTP time into everyday time:
    const unsigned long seventyYears = 2208988800UL;     
    epoch = secsSince1900 - seventyYears;  
    sprintf( databuff, "ut %3d %02dh%02dm%02ds", day(epoch)-1, hour(epoch), minute(epoch), second(epoch) ) ;
    Serial.println( databuff ) ;
  }
  return epoch ;
}

// send an NTP request to the time server at the given address 
unsigned long sendNTPpacket(IPAddress& address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 		   
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer,NTP_PACKET_SIZE);
  udp.endPacket(); 
}
