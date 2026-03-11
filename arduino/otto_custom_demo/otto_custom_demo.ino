#include <Arduino.h>
#include <Otto.h>
#include "../../include/otto_robot_config.h"

Otto ottoBot;

void applyServoTrims() {
  ottoBot.setTrims(otto_cfg::TRIM_LEFT_HIP, otto_cfg::TRIM_RIGHT_HIP,
                   otto_cfg::TRIM_LEFT_FOOT, otto_cfg::TRIM_RIGHT_FOOT);
}

void setup() {
  Serial.begin(115200);
  delay(200);

  ottoBot.init(otto_cfg::SERVO_LEFT_HIP_PIN, otto_cfg::SERVO_RIGHT_HIP_PIN,
               otto_cfg::SERVO_LEFT_FOOT_PIN, otto_cfg::SERVO_RIGHT_FOOT_PIN,
               false, otto_cfg::BUZZER_PIN);
  applyServoTrims();
  ottoBot.home();
  ottoBot.sing(S_connection);  // Hello

  Serial.println("Otto custom demo starting...");
}

void loop() {
  ottoBot.home();
  delay(300);

  ottoBot.sing(S_OhOoh2);          // Big ooh-ooh
  ottoBot.moonwalker(3, 900, 22, 1);
  ottoBot.sing(S_happy_short);     // Giggle
  ottoBot.swing(3, 850, 20);
  ottoBot.sing(S_fart1);           // Toot
  ottoBot.jump(2, 500);
  ottoBot.home();
  delay(250);

  ottoBot.sing(S_OhOoh2);           // Big ooh-ooh
  ottoBot.moonwalker(3, 900, 22, -1);
  ottoBot.sing(S_happy_short);      // Giggle
  ottoBot.swing(2, 850, 18);
  ottoBot.sing(S_fart1);            // Toot
  ottoBot.jump(1, 500);
  ottoBot.home();
  delay(700);
}
