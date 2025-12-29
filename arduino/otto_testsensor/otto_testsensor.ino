#include <Arduino.h>

const uint8_t BUZZER_PIN = 12;
const uint8_t LED_PIN = LED_BUILTIN;

//----------------------------------------------------------------
//-- Otto All moves test
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------


///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  pinMode( BUZZER_PIN , OUTPUT);    
  pinMode(LED_PIN, OUTPUT);
    tone(  BUZZER_PIN,523 ,125);
   delay(125);
  tone(  BUZZER_PIN, 587 ,125);
   delay(125);
  tone(  BUZZER_PIN, 659 ,125);
   delay(125);
  tone(  BUZZER_PIN, 698 ,125);
   delay(125);
  tone(  BUZZER_PIN, 784 ,125);
   delay(125);
  tone(  BUZZER_PIN,880,125);
   delay(125);
  tone(  BUZZER_PIN,261,125);
   delay(125);

}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////

void loop() {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LIGHT:");
    Serial.print(analogRead(A0));
    if (1==1) {
      digitalWrite(LED_PIN, HIGH);
      tone(  BUZZER_PIN,440,125);
       delay(125);
    }

}
