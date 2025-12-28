//----------------------------------------------------------------
// Otto All Moves demo (adapted for this repo's wiring).
//----------------------------------------------------------------
#include <Otto.h>

Otto ottoBot;

constexpr uint8_t LEFT_LEG_PIN = 2;
constexpr uint8_t RIGHT_LEG_PIN = 3;
constexpr uint8_t LEFT_FOOT_PIN = 4;
constexpr uint8_t RIGHT_FOOT_PIN = 5;
constexpr uint8_t BUZZER_PIN = 12;

// 8x8 LED matrix pins (optional).
constexpr uint8_t MATRIX_DIN_PIN = A3;
constexpr uint8_t MATRIX_CS_PIN = A2;
constexpr uint8_t MATRIX_CLK_PIN = A1;
constexpr int MATRIX_ORIENTATION = 1; // 1=Top, 2=Bottom, 3=Left, 4=Right.

void setup() {
  ottoBot.init(LEFT_LEG_PIN, RIGHT_LEG_PIN, LEFT_FOOT_PIN, RIGHT_FOOT_PIN, true,
               BUZZER_PIN);
  ottoBot.initMATRIX(MATRIX_DIN_PIN, MATRIX_CS_PIN, MATRIX_CLK_PIN,
                     MATRIX_ORIENTATION);
  ottoBot.sing(S_connection);
  ottoBot.home();
  delay(50);
  ottoBot.playGesture(OttoHappy);
}

void loop() {
  ottoBot.walk(2, 1000, 1);
  ottoBot.walk(2, 1000, -1);
  ottoBot.turn(2, 1000, 1);
  ottoBot._tone(10, 3, 1);
  ottoBot.bendTones(100, 200, 1.04, 10, 10);
  ottoBot.home();
  delay(100);
  ottoBot.turn(2, 1000, -1);
  ottoBot.bend(1, 500, 1);
  ottoBot.bend(1, 2000, -1);
  ottoBot.shakeLeg(1, 1500, 1);
  ottoBot.home();
  delay(100);
  ottoBot.shakeLeg(1, 2000, -1);
  ottoBot.moonwalker(3, 1000, 25, 1);
  ottoBot.moonwalker(3, 1000, 25, -1);
  ottoBot.crusaito(2, 1000, 20, 1);
  ottoBot.crusaito(2, 1000, 20, -1);
  delay(100);
  ottoBot.flapping(2, 1000, 20, 1);
  ottoBot.flapping(2, 1000, 20, -1);
  delay(100);
  ottoBot.swing(2, 1000, 20);
  ottoBot.tiptoeSwing(2, 1000, 20);
  ottoBot.jitter(2, 1000, 20);
  ottoBot.updown(2, 1500, 20);
  ottoBot.ascendingTurn(2, 1000, 50);
  ottoBot.jump(1, 500);
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
  ottoBot.putMouth(21);
  delay(100);
  ottoBot.putMouth(27);
  delay(100);
  ottoBot.putMouth(23);
  delay(100);
  ottoBot.putMouth(24);
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
  ottoBot.putAnimationMouth(littleUuh, 0);
  delay(1000);
  ottoBot.putAnimationMouth(dreamMouth, 0);
  delay(1000);
  ottoBot.putAnimationMouth(dreamMouth, 1);
  delay(1000);
  ottoBot.putAnimationMouth(dreamMouth, 2);
  delay(1000);
}
