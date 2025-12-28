//----------------------------------------------------------------
// Otto DIY calibration helper
// Uses OttoDIYLib and saves trims to EEPROM.
//----------------------------------------------------------------
#include <Arduino.h>
#include <EEPROM.h>
#include <Otto.h>

const int LEFT_LEG_PIN = 2;
const int RIGHT_LEG_PIN = 3;
const int LEFT_FOOT_PIN = 4;
const int RIGHT_FOOT_PIN = 5;
const int BUZZER_PIN = 12;

Otto ottoBot;

int trimLeftLeg;
int trimRightLeg;
int trimLeftFoot;
int trimRightFoot;

void calibHome() {
  int servoPos[4] = {90, 90, 90, 90};
  ottoBot._moveServos(500, servoPos);
  ottoBot.detachServos();
}

void applyTrims() {
  ottoBot.setTrims(trimLeftLeg, trimRightLeg, trimLeftFoot, trimRightFoot);
  ottoBot.saveTrimsOnEEPROM();
}

void printTrims() {
  Serial.print("Trims (LL, RL, LF, RF): ");
  Serial.print(trimLeftLeg);
  Serial.print(", ");
  Serial.print(trimRightLeg);
  Serial.print(", ");
  Serial.print(trimLeftFoot);
  Serial.print(", ");
  Serial.println(trimRightFoot);
}

void setup() {
  Serial.begin(9600);

  ottoBot.init(LEFT_LEG_PIN, RIGHT_LEG_PIN, LEFT_FOOT_PIN, RIGHT_FOOT_PIN, true,
               BUZZER_PIN);

  trimLeftLeg = EEPROM.read(0);
  if (trimLeftLeg > 128) trimLeftLeg -= 256;
  trimRightLeg = EEPROM.read(1);
  if (trimRightLeg > 128) trimRightLeg -= 256;
  trimLeftFoot = EEPROM.read(2);
  if (trimLeftFoot > 128) trimLeftFoot -= 256;
  trimRightFoot = EEPROM.read(3);
  if (trimRightFoot > 128) trimRightFoot -= 256;

  calibHome();

  Serial.println("OTTO CALIBRATION PROGRAM");
  Serial.println("PRESS a/z for left leg");
  Serial.println("PRESS s/x for left foot");
  Serial.println("PRESS k/m for right leg");
  Serial.println("PRESS j/n for right foot");
  Serial.println("PRESS f to test walk");
  Serial.println("PRESS h to return home");
  Serial.println("PRESS p to print trims");
  Serial.println();
  printTrims();
}

void loop() {
  if (Serial.available() == 0) {
    return;
  }

  const int charRead = Serial.read();

  if (charRead == 'a') {
    trimLeftLeg++;
  } else if (charRead == 'z') {
    trimLeftLeg--;
  } else if (charRead == 's') {
    trimLeftFoot++;
  } else if (charRead == 'x') {
    trimLeftFoot--;
  } else if (charRead == 'k') {
    trimRightLeg++;
  } else if (charRead == 'm') {
    trimRightLeg--;
  } else if (charRead == 'j') {
    trimRightFoot++;
  } else if (charRead == 'n') {
    trimRightFoot--;
  } else if (charRead == 'f') {
    ottoBot.walk(1, 1000, 1);
    return;
  } else if (charRead == 'h') {
    ottoBot.home();
    return;
  } else if (charRead == 'p') {
    printTrims();
    return;
  } else {
    return;
  }

  applyTrims();
  calibHome();
  printTrims();
}
