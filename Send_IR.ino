#include <IRLibAll.h>
IRsend mySender;
void setup() {
  Serial.begin(9600);
}
void loop() {
   mySender.send(#protocol_no, #hex code, #no_of_bits);
  delay(1000);
}
