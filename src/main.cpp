#include <Arduino.h>
#include <Otto.h>
#include <otto_robot_config.h>

Otto ottoBot;

long readUltrasonicCm() {
  digitalWrite(otto_cfg::ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(otto_cfg::ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(otto_cfg::ULTRASONIC_TRIG_PIN, LOW);

  long duration = pulseIn(otto_cfg::ULTRASONIC_ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    return -1;
  }
  return duration / 58;
}

void applyServoTrims() {
  ottoBot.setTrims(otto_cfg::TRIM_LEFT_HIP, otto_cfg::TRIM_RIGHT_HIP,
                   otto_cfg::TRIM_LEFT_FOOT, otto_cfg::TRIM_RIGHT_FOOT);
}

void neutralPose() {
  ottoBot.home();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(otto_cfg::ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(otto_cfg::ULTRASONIC_ECHO_PIN, INPUT);

  Serial.begin(115200);
  delay(200);

  ottoBot.init(otto_cfg::SERVO_LEFT_HIP_PIN, otto_cfg::SERVO_RIGHT_HIP_PIN,
               otto_cfg::SERVO_LEFT_FOOT_PIN, otto_cfg::SERVO_RIGHT_FOOT_PIN,
               false, otto_cfg::BUZZER_PIN);
  applyServoTrims();
  neutralPose();
  ottoBot.sing(S_connection);

  Serial.println("Otto robot starting...");
}

void loop() {
  delay(1000);
}
