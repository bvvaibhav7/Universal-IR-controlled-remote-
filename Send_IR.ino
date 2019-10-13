//Created by Venkata Vaibhav Bhagavatula on 9/10/2019
#include <IRLibAll.h>
IRsend mySender;
void setup() {
  Serial.begin(9600);                   //baud rate
}
void loop() {
   mySender.send(#protocol_no, #hex code, #no_of_bits); //Send the IR signal
  delay(1000);
}
