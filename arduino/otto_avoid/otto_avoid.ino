#include <Arduino.h>
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Otto avoid obstacles with ultrasonic sensor sample sketch code
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <Otto.h>
Otto ottoBot;  //This is Otto!
//----------------------------------------------------------------------
#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  12 
#define Trigger 8 // ultrasonic sensor trigger pin
#define Echo 9 // ultrasonic sensor echo pin

long ultrasound() {
   long duration, distance;
   digitalWrite(Trigger,LOW);
   delayMicroseconds(2);
   digitalWrite(Trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(Trigger, LOW);
   duration = pulseIn(Echo, HIGH);
   distance = duration/58;
   return distance;
}


void setup() {
  ottoBot.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT); 

}

void loop() {
    if (ultrasound() <= 15) {
      ottoBot.sing(S_surprise);
      ottoBot.playGesture(OttoConfused);
      ottoBot.walk(2,1000,-1); // BACKWARD x2
      ottoBot.turn(3,1000,1); // LEFT x3
    }
    ottoBot.walk(1,1000,1); // FORWARD x1

}
