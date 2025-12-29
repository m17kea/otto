#include <Arduino.h>
//-----------------------------------------------------------------
//-- This Otto uses a touch sensor to switch three modes
//-- Mode 1: Otto avoid obstacles
//-- Mode 2: Otto follow the hand
//-- Mode 3: Otto dances!
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
#include <Otto.h>
Otto ottoBot;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*             -------- 
              |  O  O  |
              |--------|
  RIGHT LEG 3 |        | LEFT LEG 2
               -------- 
               ||     ||
RIGHT FOOT 5 |---     ---| LEFT FOOT 4  
*/
#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  12 
#define Trigger 8 // ultrasonic sensor trigger pin
#define Echo 9 // ultrasonic sensor echo pin

const int sensorPin = A0;

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
int movement = 0;
boolean izqder = true; // TEMPO: 97 BPM
bool obstacleDetected = false;
///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  ottoBot.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  pinMode(sensorPin, INPUT);
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT);
  ottoBot.home();
  ottoBot.sing(S_happy); // a happy Otto :)
}
// touch sensor is in "toggle mode", initial value LOW
// program expects HIGH value for first touch
// and then expects LOW value for second touch
// and then again HIGH and LOW etc.
//
  int estado = HIGH; //first expected touch value
  
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  
   if (digitalRead(sensorPin) == estado)
   {
     if (estado == HIGH)
     {
     estado = LOW; //toggle expect value
     }
     else
     {
      estado = HIGH; //toggle expect value
     }
     ottoBot.sing(S_buttonPushed);
     movement = movement + 1;
     delay(500);
   }
   if (movement == 1)
   {
        if(obstacleDetected){
          Serial.println("OBJETO DETECTADO"); 
          ottoBot.sing(S_OhOoh);
          
          if (izqder == true)
          {
            ottoBot.walk(2,1000,-1); 
            ottoBot.turn(2,1000,1);//2 steps turning RIGHT   
            izqder = false;
          }
          else
          {
            ottoBot.walk(2,1000,-1); 
            ottoBot.turn(2,1000,-1);//2 steps turning LEFT   
            izqder = true;
          }
          
          //ottoBot.home(); 
          delay(50); 
          obstacleDetector();
        } 
        else
        {
          ottoBot.walk(1,500,1); 
          delay(50);
          //ottoBot.home();
          obstacleDetector();
        }
   }

   if (movement == 2)
   {
      if(obstacleDetected){ 
        Serial.println("Object detected");  
        ottoBot.walk(2,1000,1);
        ottoBot.home(); 
        //delay(60);
        obstacleDetector();
        //delay(10) ;
        }        
        else{ 
            obstacleDetector(); 
        } 
   }

   if (movement == 3)
   {
      ottoBot.jitter(10,500,40); 
      ottoBot.home();
      ottoBot.moonwalker(2,1000,30,1);
      ottoBot.home();
      ottoBot.ascendingTurn(2,500,50); 
      ottoBot.home();
      ottoBot.tiptoeSwing(2,1000,30); 
      ottoBot.home();
      ottoBot.flapping(2,500,40,1);
      ottoBot.home();
      ottoBot.crusaito(2,3000,40,1);
      ottoBot.home();
      ottoBot.shakeLeg(2,1000,1);  
      ottoBot.home();
      ottoBot.sing(S_disconnection);
      movement = 0;
   }
}

///////////////////////////////////////////////////////////////////
//-- Function to read distance sensor & to update obstacleDetected variable
void obstacleDetector(){
   int distance = ultrasound();
        if(distance<15){
          obstacleDetected = true;
        }else{
          obstacleDetected = false;
        }
}
