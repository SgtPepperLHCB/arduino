#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <Time.h>

//
// Lcd
//
enum {
  LCD_COLS = 16,
  LCD_ROWS = 2,
  LCD_WHITE = 0x07
} ;
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield() ;
time_t t0 ;
int s0 ;
int epoch0 ;
uint8_t c ;
char databuff[ 32 ] ;
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
  t0 = 0 ;
  s0 = 0 ;
  epoch0 = 0 ;
} //-setup


//
// main loop
//
void loop() {
  if ( now() > s0 ) {
    // Only update if seconds change.
    s0 = now() ;
    memset( databuff, 0, 32 ) ;
    sprintf( databuff, "0x%02x ", c ) ;
    int l = strlen( databuff ) ;
    for ( int i = 0 ; i < 4 ; ++i ) {
      databuff[l+i*2] = c++ ;
      databuff[l+i*2+1] = ' ' ;
    }
    sprintf( dispbuff, "%-16s", databuff ) ;
    lcd.setCursor(0, 0) ;
    lcd.print( dispbuff ) ;
   
    // display uptime
    time_t dt = now() - t0 ;
    sprintf( databuff, "up %3dd%02dh%02dm%02ds", day(dt)-1, hour(dt), minute(dt), second(dt) ) ;
    sprintf( dispbuff, "%-16s", databuff ) ;
    lcd.setCursor(0, 1) ;
    lcd.print( dispbuff ) ;
  }

  uint8_t buttons = lcd.readButtons();
  if (buttons) {
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
      t0 = now() ;
    }
  }

} //-loop
