#include <Arduino.h>
//----------------------------------------------------------------
//-- Otto All moves test
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
#include <Otto.h>
Otto ottoBot;  //This is Otto!

#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  12 
#define DIN A3 // Data In pin
#define CS A2  // Chip Select pin
#define CLK A1 // Clock pin
#define Orientation 1 // 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4 

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  ottoBot.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  ottoBot.initMATRIX( DIN, CS, CLK, Orientation);
  ottoBot.sing(S_connection); //Otto wake up!
  ottoBot.home();
    delay(50);
  ottoBot.playGesture(OttoHappy);
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() { 
  ottoBot.walk(2,1000,1); //2 steps, "TIME". IF HIGHER THE VALUE THEN SLOWER (from 600 to 1400), 1 FORWARD
  ottoBot.walk(2,1000,-1); //2 steps, T, -1 BACKWARD 
  ottoBot.turn(2,1000,1);//3 steps turning LEFT
  ottoBot._tone(10, 3, 1);
  ottoBot.bendTones (100, 200, 1.04, 10, 10);
    ottoBot.home();
    delay(100);  
  ottoBot.turn(2,1000,-1);//3 steps turning RIGHT 
  ottoBot.bend (1,500,1); //usually steps =1, T=2000
  ottoBot.bend (1,2000,-1);     
  ottoBot.shakeLeg (1,1500, 1);
    ottoBot.home();
    delay(100);
  ottoBot.shakeLeg (1,2000,-1);
  ottoBot.moonwalker(3, 1000, 25,1); //LEFT
  ottoBot.moonwalker(3, 1000, 25,-1); //RIGHT  
  ottoBot.crusaito(2, 1000, 20,1);
  ottoBot.crusaito(2, 1000, 20,-1);
    delay(100); 
  ottoBot.flapping(2, 1000, 20,1);
  ottoBot.flapping(2, 1000, 20,-1);
    delay(100);        
  ottoBot.swing(2, 1000, 20);
  ottoBot.tiptoeSwing(2, 1000, 20);
  ottoBot.jitter(2, 1000, 20); //(small T)
  ottoBot.updown(2, 1500, 20);  // 20 = H "HEIGHT of movement"T 
  ottoBot.ascendingTurn(2, 1000, 50);
  ottoBot.jump(1,500); // It doesn't really jumpl ;P
  ottoBot.home();
     delay(100); 
  ottoBot.sing(S_cuddly);
  ottoBot.sing(S_OhOoh);
  ottoBot.sing(S_OhOoh2);
  ottoBot.sing(S_surprise);
  ottoBot.sing(S_buttonPushed);       
  ottoBot.sing(S_mode1);        
  ottoBot.sing(S_mode2);         
  ottoBot.sing(S_mode3);  
  ottoBot.sing(S_sleeping);
  ottoBot.sing(S_fart1);
  ottoBot.sing(S_fart2);
  ottoBot.sing(S_fart3);
  ottoBot.sing(S_happy);
  ottoBot.sing(S_happy_short);                   
  ottoBot.sing(S_superHappy);   
  ottoBot.sing(S_sad);               
  ottoBot.sing(S_confused);
  ottoBot.sing(S_disconnection);
    delay(100);  
  ottoBot.playGesture(OttoHappy);
  ottoBot.playGesture(OttoSuperHappy);
  ottoBot.playGesture(OttoSad);
  ottoBot.playGesture(OttoVictory); 
  ottoBot.playGesture(OttoAngry); 
  ottoBot.playGesture(OttoSleeping);
  ottoBot.playGesture(OttoFretful);
  ottoBot.playGesture(OttoLove);
  ottoBot.playGesture(OttoConfused);        
  ottoBot.playGesture(OttoFart);
  ottoBot.playGesture(OttoWave);
  ottoBot.playGesture(OttoMagic);
  ottoBot.playGesture(OttoFail);
    ottoBot.home();
    delay(100);  
  ottoBot.putMouth(zero);
  delay(100);
  ottoBot.putMouth(one);
  delay(100);
  ottoBot.putMouth(two);
  delay(100);
  ottoBot.putMouth(three);
  delay(100);
  ottoBot.putMouth(four);
  delay(100);
  ottoBot.putMouth(five);
  delay(100);
  ottoBot.putMouth(6);
  delay(100);
  ottoBot.putMouth(7);
  delay(100);
  ottoBot.putMouth(8);
  delay(100);
  ottoBot.putMouth(9);
  delay(100);
  ottoBot.putMouth(smile);
  delay(100);
  ottoBot.putMouth(happyOpen);
  delay(100);
  ottoBot.putMouth(happyClosed);
  delay(100);
  ottoBot.putMouth(heart);
  delay(100);
  ottoBot.putMouth(angry);
  delay(100);
  ottoBot.putMouth(smallSurprise);
  delay(100);
  ottoBot.putMouth(bigSurprise);
  delay(100);
  ottoBot.putMouth(tongueOut);
  delay(100);
  ottoBot.putMouth(confused);
  delay(100);
  ottoBot.putMouth(21); //diagonal
  delay(100);
  ottoBot.putMouth(27); //interrogation
  delay(100);
  ottoBot.putMouth(23); //sad open
  delay(100);
  ottoBot.putMouth(24); //sad closed
  delay(100);
  ottoBot.putMouth(vamp1);
  delay(100);
  ottoBot.putMouth(vamp2);
  delay(100);
  ottoBot.putMouth(xMouth);
  delay(100);
  ottoBot.putMouth(okMouth);
  delay(100);
  ottoBot.putMouth(thunder);
  delay(100);
  ottoBot.putMouth(lineMouth);
  delay(100);
  ottoBot.putMouth(culito);
    delay(100); 
  ottoBot.putAnimationMouth(littleUuh,0);
  delay(1000); 
  ottoBot.putAnimationMouth(dreamMouth, 0);
  delay(1000); 
  ottoBot.putAnimationMouth(dreamMouth, 1);
  delay(1000); 
  ottoBot.putAnimationMouth(dreamMouth, 2);
  delay(1000); 
}
