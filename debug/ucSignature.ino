/* thanks to Jim Eli ( https://ucexperiment.wordpress.com/2012/02/23/determine-which-arduino-%C2%B5c-your-code-is-on/ )  */

/*
  determine which Arduino uC processor the code is running on
  ( ATmega168, 328, 1280 or 2560 )
  Signature bytes:
              Atmel  Flash  uC
  ATmega168   0x1e   0x94   0x06
  ATmega328   0x1e   0x95   0x0f
  ATmega1280	0x1e   0x97   0x03
  ATmega2560	0x1e   0x98   0x01
  
  Nb: for the Flash memory amount, 0x94 stands for 16K, 0x95 for 32K, ..
  
*/

#include <avr/signature.h>
 
void setup(void) {
  Serial.begin(9600);
  Serial.println(SIGNATURE_0, HEX);
  Serial.println(SIGNATURE_1, HEX);
  Serial.println(SIGNATURE_2, HEX);
}
 
void loop(void) {}
