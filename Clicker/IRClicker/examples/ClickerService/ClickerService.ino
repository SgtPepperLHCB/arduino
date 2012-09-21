#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>
#include <util.h>
#include <EthernetUdp.h>
#include <SPI.h>

#include <IRClicker.h>

char GET_VERB[]  = "GET /clicker" ;
byte mac [] = { 0xde, 0xad, 0xbe, 0xef, 0xca, 0xca } ;
byte ip []  = { 192,168,1,88 } ;
enum {
  HTTP_PORT = 80,
  BAUD_RATE = 115200,
  BUFSIZE   = 200,
} ;

IRTransmitter tx ;
IRReceiver    rx ;
IRDevice clicker( SymphonicTvVcrProfile, tx, rx, SymphonicTvVcrCommandCodes ) ;

EthernetServer server( HTTP_PORT ) ;

void setup ( ) {
  Serial.begin( BAUD_RATE ) ;
  Ethernet.begin( mac, ip ) ;
  server.begin() ;

  Serial.println( "ok" ) ;
}

void loop ( ) {
/*
  while ( Serial.available( ) > 0 ) {
    int command = Serial.parseInt( ) ;
    if ( Serial.read( ) == '\n' ) {
      clicker.send( command ) ;
      Serial.println( command ) ;
    }
  }
*/
  char clientLine[ BUFSIZE ] ;
  int index = 0 ; 
  EthernetClient client = server.available() ;
  if ( client ) {
    // An http request ends with a blank line.
    boolean isBlank = true ;

    // Reset input buffer.
    index = 0 ;

    while ( client.connected() ) {
      if ( client.available() ) {
        char c = client.read() ;

        // If it isn't a newline, add character to buffer.
        if ( c != '\n' && c != '\r' ) {
          clientLine[ index ] = c ;
          ++index ;
          // Start tossing out data if we overrun our buffer.
          if ( index > BUFSIZE ) {
            index = BUFSIZE - 1 ;
          }
          // Give me more data!
          continue ;
        }

        // Got a newline, so string is done.
        clientLine[ index ] = 0 ;

        //dbg
        Serial.println( clientLine ) ;
        if ( strstr(clientLine, GET_VERB ) != 0 ) {
          client.println( "HTTP/1.1 200 OK" ) ;
          client.println( "Content-Type: text/html" ) ;
          client.println() ;
          char *command ;
          command = clientLine + sizeof( GET_VERB ) ;
          ( strstr(clientLine, " HTTP") )[ 0 ] = 0 ;
          //Serial.println( command ) ;
          client.println( command ) ;
          clicker.send( atoi(command) ) ;
        } else {
          client.println( "HTTP/1.1 404 Not Found" ) ;
          client.println( "Content-Type: text/html" ) ;
          client.println() ;
          client.println( "I'm sorry Dave, I'm afraid I can't do that :(" ) ;
        }
      }
      break ;
    }
    delay( 1 ) ;
    client.stop() ;
  }
}
