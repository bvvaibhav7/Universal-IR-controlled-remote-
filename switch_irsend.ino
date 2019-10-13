//Created by Venkata Vaibhav Bhagavatula on 9/10/2019 
// Rotary encoder 1 is being used for Selection of device
//Rotary encoder 2 is being used for selction of functionality

#include <IRLibAll.h> //includiing the IR library

#define outputA 8     //CLK pin for Rotary encoder 1
#define outputB 9     //DT pin for the Rotary encoder 1

#define outputC 6     //CLK pin for Rotary encoder 2
#define outputD 7     //DT pin for Rotary encoder 2

//Variables for the Rotary encoder 2
int counter = 0;      //counter for counting the position
int aState;           //Variable to hold the present state
int aLastState;       //Variable to hold the last state
int val1;             //Value showing the position of the encoder 

//Valriables for the rotary encoder 1
int counter1 = 0;     //counter for counting the position
int aState1;          //Variable to hold the present state
int aLastState1;      //Variable to hold the last state
int val2;             //Value showing the position of the encoder 


IRsend mySender;      //Variable for sending the IR signal to the receiver at the device end

#define SW 5          //Conncting the seitch button of the Rotary encoder 2 to act as a push button
 
 void setup() { 
  //Declaring the variables defined as inputs or outputs
   pinMode(SW, INPUT_PULLUP);     
   pinMode (outputA, INPUT);
   pinMode (outputB, INPUT);
   pinMode (outputC, INPUT);
   pinMode (outputD, INPUT);
   
   Serial.begin (9600);             //setting the baud rate of 9600
   
   // Reading the initial state of the outputA
   aLastState  = digitalRead(outputA);
   // Reading the initial state of the outputC
   aLastState1 = digitalRead(outputC);
 } 

 void loop()
 {     
      aState = digitalRead(outputA);         // Reads the "current" state of the outputA
                                             // If the previous and the current state of the outputA are different, that means a Pulse has occured
      aState1 = digitalRead(outputC);        // Reads the "current" state of the outputA
                                             // If the previous and the current state of the outputA are different, that means a Pulse has occured
    
    if (aState != aLastState)                //If any pulse has occured....
    {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(outputB) != aState) {
        counter ++;                         //increment the counter if the encoder is rotated in clock wise direction
      } else {
        counter --;                         //Decrement the counter if the encoder is rotated in anti clock wise direction 
      }

      val1 = (counter % 40) * 0.5;          //Finding the position of the rotary encoder

      //Printing the functionlities that can be operated at the current position of the rotary encoder so as to make user comfortable
      //Position 1: Switching on/off the device
      //Position 2: Increase the volume of the device
      //Position 3: Decrease the volume of the device
      //Position 4: Mute the device
      //Position 5: change the channel of the device to next
      //Position 6: change the channel of the device to prev
      Serial.println("The position of encooder is");
      if(val1==1)
      {
        Serial.println("You may Switch on/off");
      }
      
      else if(val1==2)
      {
        Serial.println("You may increase volume now");
      }

      else if(val1==3)
      {
        Serial.println("You may decrease volume now");
      }

      else if(val1==4)
      {
        Serial.println("You may mute the volume now");
      }

      else if(val1==5)
      {
        Serial.println("You may change the channel to next");
      }

      else if(val1==6)
      {
        Serial.println("You may change the channel to previous");
      }
    }

// Repeating the same process for another encoder

    if (aState1 != aLastState1) 
    {
    // If the outputB state is different to the outputD state, that means the encoder is rotating clockwise
      if (digitalRead(outputD) != aState1) {
        counter1 ++;
      } else {
        counter1 --;
      } 

      val2 = (counter1 % 40) * 0.5;

//Assigning one position to one device and accorsing to the position set by the user by rotating the rotary encoder we will print which device is selected by the user

      Serial.println("The position of encooder for device control is");
       if(val2==1)
      {
        Serial.println("You may control Audio system now");
      }
      
      else if(val2==2)
      {
        Serial.println("You may control your Television now");
      }

    }
   
    
    aLastState = aState; // Updates the previous state of the outputA with the current state
    aLastState1 = aState1;

//Now according to the position selected by the user through the rotary encoders we will have to send the correspoding IR signals to the device
    
     if (digitalRead(SW)==0)
      { 
        if(val2==1)                                                       //If the Audio system is selected...
        {
            if(val1==1)                                                 
            { 
              Serial.println("Sending the IR for Power:");
              delay(500);
              mySender.send(NEC, 0x1FE48B7, 32);                          //Send the IR signal corresponding to the power on/off
              delay(1000);
            }
            else if(val1==2)
            {
               Serial.println("Sending the IR for Volume up:");
               delay(500);
               mySender.send(NEC, 0x1FE609F, 32);                        //Send the IR signal corresponding to increase the volume
               delay(1000);
            }
            else if(val1==3)
            {
              Serial.println("Sending the IR for Volume down:");
              delay(500);
              mySender.send(NEC, 0x1FEA05F, 32);                        //Send the IR signal corresponding to decrease the volume
              delay(1000);
            }
            else if(val1==4)
            {
              Serial.println("Sending the IR for Mute:");
              delay(500);
              mySender.send(NEC, 0x1FE7887, 32);                        //Send the IR signal corresponding to Muting the device
              delay(1000);
            }
            else if(val1==5)
            {
              Serial.println("Sending the IR for next song:");
              delay(500);
              mySender.send(NEC, 0x1FE7887, 32);                        //Send the IR signal corresponding to changing to next song
              delay(1000);
            }
            else if(val1==6)
            {
              Serial.println("Sending the IR for previous song:");
              delay(500);
              mySender.send(NEC, 0x1FE7887, 32);                        //Send the IR signal corresponding to changing to previous song
              delay(1000);
            }
            
            
            
        }

         if(val2==2)                                                          //If television is selected
        {
            if(val1==1)                                                           
            { 
              Serial.println("Sending the IR for Power:");
              delay(500);
              mySender.send(NEC, 0x4FBF00F, 32);                              //Send the IR signal corresponding to the power on/of
              delay(1000);
            }
            else if(val1==2)
            {
               Serial.println("Sending the IR for Volume up:");
               delay(500);
               mySender.send(NEC, 0x4FBE01F, 32);                             //Send the IR signal corresponding to incresing the volume
               delay(1000);
            }
            else if(val1==3)
            {
              Serial.println("Sending the IR for Volume down:");
              delay(500);
              mySender.send(NEC, 0x4FBD02F, 32);                             //Send the IR signal corresponding to decresing the volume
              delay(1000);
            }
            else if(val1==5)
            {
              Serial.println("Sending the IR for Channel Next:");
              delay(500);
              mySender.send(NEC, 0x4FB48B7, 32);                             //Send the IR signal corresponding to changing to next channel
              delay(1000);
            }
             else if(val1==6)
            {
              Serial.println("Sending the IR for Channel Prev:");
              delay(500);
              mySender.send(NEC, 0x4FB08F7, 32);                              //Send the IR signal corresponding to changing to previous channel
              delay(1000);
            }
        }
      }
 }
