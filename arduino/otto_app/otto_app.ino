#include <Arduino.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-- Otto DIY App Firmware Version 13 with standard baudrate of 9600 for Bluetooth BLE modules.
//-- Otto DIY invests time and resources providing open source code and hardware,  
//-- please support by purchasing kits from (https://www.ottodiy.com)
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
//-- If you wish to use this software under Open Source Licensing, you must contribute all your source code to the community and all text above must be included in any redistribution
//-- in accordance with the GPL when your application is distributed. See http://www.gnu.org/copyleft/gpl.html
//---------------------
#include <SerialCommand.h>
SoftwareSerial BTserial = SoftwareSerial(11,7); // RX pin to 11 and TX pin to 7 on the board
SerialCommand SCmd(BTserial);
#include <Otto.h>
Otto ottoBot;

#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  12 
#define DIN A3 // Data In pin
#define CS A2  // Chip Select pin
#define CLK A1 // Clock pin
#define Orientation 1 // 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4 
#define PIN_Button   A0
#define PIN_ASSEMBLY    10

int T = 1000;
int moveId = 0;
int moveSize = 15;
volatile bool buttonPushed=false;
unsigned long int matrix;
void receiveStop() 
{ sendAck(); ottoBot.home(); sendFinalAck(); }
void receiveLED()
{ sendAck(); ottoBot.home(); unsigned long int matrix; char *arg; char *endstr; arg = SCmd.next(); if (arg != NULL) { matrix = strtoul(arg, &endstr, 2); ottoBot.putMouth(matrix, false); } else { ottoBot.putMouth(xMouth); delay(2000); ottoBot.clearMouth(); } sendFinalAck(); }
void recieveBuzzer() 
{ sendAck(); ottoBot.home(); bool error = false; int frec; int duration; char *arg; arg = SCmd.next(); if (arg != NULL) frec = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) duration = atoi(arg); else error = true; if (error == true) { ottoBot.putMouth(xMouth); delay(2000); ottoBot.clearMouth(); } else ottoBot._tone(frec, duration, 1); sendFinalAck(); }
void receiveTrims() 
{ sendAck(); ottoBot.home(); int trim_YL, trim_YR, trim_RL, trim_RR; bool error = false; char *arg; arg = SCmd.next(); if (arg != NULL) trim_YL = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) trim_YR = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) trim_RL = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) trim_RR = atoi(arg); else error = true; if (error == true) { ottoBot.putMouth(xMouth); delay(2000); ottoBot.clearMouth(); } else { ottoBot.setTrims(trim_YL, trim_YR, trim_RL, trim_RR); ottoBot.saveTrimsOnEEPROM(); } sendFinalAck(); }
void receiveServo() 
{ sendAck(); moveId = 30; bool error = false; char *arg; int servo_YL, servo_YR, servo_RL, servo_RR; arg = SCmd.next(); if (arg != NULL) servo_YL = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) servo_YR = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) servo_RL = atoi(arg); else error = true; arg = SCmd.next(); if (arg != NULL) { servo_RR = atoi(arg); } else error = true; if (error == true) { ottoBot.putMouth(xMouth); delay(2000); ottoBot.clearMouth(); } else { int servoPos[4] = {servo_YL, servo_YR, servo_RL, servo_RR}; ottoBot._moveServos(200, servoPos); } sendFinalAck(); }
void receiveMovement() 
{ sendAck(); if (ottoBot.getRestState() == true) ottoBot.setRestState(false); char *arg; arg = SCmd.next(); if (arg != NULL) moveId = atoi(arg); else { ottoBot.putMouth(xMouth); delay(2000); ottoBot.clearMouth(); moveId = 0; } arg = SCmd.next(); if (arg != NULL) T = atoi(arg); else T = 1000; arg = SCmd.next(); if (arg != NULL) moveSize = atoi(arg); else moveSize = 15; }
void move(int moveId) 
{ bool manualMode = false; switch (moveId) { case 0: ottoBot.home(); break; case 1: ottoBot.walk(1, T, 1); break; case 2: ottoBot.walk(1, T, -1); break; case 3: ottoBot.turn(1, T, 1); break; case 4: ottoBot.turn(1, T, -1); break; case 5: ottoBot.updown(1, T, moveSize); break; case 6: ottoBot.moonwalker(1, T, moveSize, 1); break; case 7: ottoBot.moonwalker(1, T, moveSize, -1); break; case 8: ottoBot.swing(1, T, moveSize); break; case 9: ottoBot.crusaito(1, T, moveSize, 1); break; case 10: ottoBot.crusaito(1, T, moveSize, -1); break; case 11: ottoBot.jump(1, T); break; case 12: ottoBot.flapping(1, T, moveSize, 1); break; case 13: ottoBot.flapping(1, T, moveSize, -1); break; case 14: ottoBot.tiptoeSwing(1, T, moveSize); break; case 15: ottoBot.bend(1, T, 1); break; case 16: ottoBot.bend(1, T, -1); break; case 17: ottoBot.shakeLeg(1, T, 1); break; case 18: ottoBot.shakeLeg(1, T, -1); break; case 19: ottoBot.jitter(1, T, moveSize); break; case 20: ottoBot.ascendingTurn(1, T, moveSize); break; default: manualMode = true; break; } if (!manualMode) sendFinalAck(); }
void receiveGesture()
{ sendAck(); ottoBot.home();  int gesture = 0; char *arg; arg = SCmd.next(); if (arg != NULL) gesture = atoi(arg); else     delay(2000); switch (gesture) { case 1: ottoBot.playGesture(OttoHappy); break; case 2: ottoBot.playGesture(OttoSuperHappy); break; case 3: ottoBot.playGesture(OttoSad); break; case 4: ottoBot.playGesture(OttoSleeping); break; case 5: ottoBot.playGesture(OttoFart); break; case 6: ottoBot.playGesture(OttoConfused); break; case 7: ottoBot.playGesture(OttoLove); break; case 8: ottoBot.playGesture(OttoAngry); break; case 9: ottoBot.playGesture(OttoFretful); break; case 10: ottoBot.playGesture(OttoMagic); break; case 11: ottoBot.playGesture(OttoWave); break; case 12: ottoBot.playGesture(OttoVictory); break; case 13: ottoBot.playGesture(OttoFail); break; default: break; } sendFinalAck(); }
void receiveSing() 
{ sendAck(); ottoBot.home(); int sing = 0; char *arg; arg = SCmd.next(); if (arg != NULL) sing = atoi(arg); else     delay(2000); switch (sing) { case 1: ottoBot.sing(S_connection); break; case 2: ottoBot.sing(S_disconnection); break; case 3: ottoBot.sing(S_surprise); break; case 4: ottoBot.sing(S_OhOoh); break; case 5: ottoBot.sing(S_OhOoh2); break; case 6: ottoBot.sing(S_cuddly); break; case 7: ottoBot.sing(S_sleeping); break; case 8: ottoBot.sing(S_happy); break; case 9: ottoBot.sing(S_superHappy); break; case 10: ottoBot.sing(S_happy_short); break; case 11: ottoBot.sing(S_sad); break; case 12: ottoBot.sing(S_confused); break; case 13: ottoBot.sing(S_fart1); break; case 14: ottoBot.sing(S_fart2); break; case 15: ottoBot.sing(S_fart3); break; case 16: ottoBot.sing(S_mode1); break; case 17: ottoBot.sing(S_mode2); break; case 18: ottoBot.sing(S_mode3); break; case 19: ottoBot.sing(S_buttonPushed); break; default: break; } sendFinalAck(); }
void sendAck() 
{ delay(30); Serial.print(F("&&")); Serial.print(F("A")); Serial.println(F("%%")); Serial.flush(); }
void sendFinalAck() 
{ delay(30); Serial.print(F("&&")); Serial.print(F("F")); Serial.println(F("%%")); Serial.flush(); }
void ButtonPushed()
{ if(!buttonPushed){ buttonPushed=true; ottoBot.putMouth(smallSurprise); } }

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  ottoBot.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  ottoBot.initMATRIX( DIN, CS, CLK, Orientation);
  ottoBot.matrixIntensity(7);
  pinMode(PIN_ASSEMBLY, INPUT_PULLUP);
  pinMode(PIN_Button, INPUT);

SCmd.addCommand("S", receiveStop);
SCmd.addCommand("L", receiveLED);
SCmd.addCommand("T", recieveBuzzer);
SCmd.addCommand("M", receiveMovement);
SCmd.addCommand("H", receiveGesture);
SCmd.addCommand("K", receiveSing);
SCmd.addCommand("C", receiveTrims);
SCmd.addCommand("G", receiveServo);
SCmd.addDefaultHandler(receiveStop);

ottoBot.sing(S_connection);
ottoBot.home();
for (int i = 0; i < 2; i++) {
  for (int i = 0; i < 8; i++) {
  ottoBot.putAnimationMouth(littleUuh, i);
  delay(150);
  }
}
ottoBot.putMouth(smile);
ottoBot.sing(S_happy);
delay(200);
ottoBot.putMouth(happyOpen);

while (digitalRead(PIN_ASSEMBLY) == LOW) {
  ottoBot.home();
  ottoBot.sing(S_happy_short);   // sing every 5 seconds so we know OTTO is still working
delay(5000);}
}

void loop() {
  SCmd.readSerial();     
  if (ottoBot.getRestState()==false){ move(moveId); }
}
