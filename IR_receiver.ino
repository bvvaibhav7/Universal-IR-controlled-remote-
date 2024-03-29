//Created by Venkata Vaibhav Bhagavatula on 9/10/2019

#include <IRLibDecodeBase.h> // First include the decode base
#include <IRLib_P01_NEC.h>   // Now include only the protocols you wish
#include <IRLib_P02_Sony.h>  // to actually use. The lowest numbered
#include <IRLib_P07_NECx.h>  // must be first but others can be any order.
#include <IRLib_P09_GICable.h>
#include <IRLib_P11_RCMM.h>
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal decoder
// class called "IRdecode" containing only the protocols you want.
// Now declare an instance of that decoder.
IRdecode myDecoder;
// Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop
#include <IRLibRecv.h> 
IRrecv myReceiver(2);  //pin number for the receiver
void setup() {
  Serial.begin(9600);
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println("Ready to receive IR signals");
}
void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) { 
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
    Serial.println(myDecoder.protocolNum);
    Serial.println(myDecoder.bits);
    Serial.println(myDecoder.value);
  }
}
