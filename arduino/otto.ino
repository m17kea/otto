#include <Otto.h>
#include "../include/otto_robot_config.h"

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
  static unsigned long lastMoveMs = 0;

  if (millis() - lastMoveMs < otto_cfg::MOVE_INTERVAL_MS) {
    return;
  }
  lastMoveMs = millis();

  long distance = readUltrasonicCm();
  Serial.print("Ultrasonic (cm): ");
  Serial.println(distance);

  if (distance > 0 && distance < otto_cfg::OBSTACLE_STOP_CM) {
    digitalWrite(LED_BUILTIN, HIGH);
    ottoBot.sing(S_surprise);
    ottoBot.turn(1, 900, RIGHT);
    digitalWrite(LED_BUILTIN, LOW);
    return;
  }

  digitalWrite(LED_BUILTIN, HIGH);
  ottoBot.walk(1, 900, FORWARD);
  digitalWrite(LED_BUILTIN, LOW);
}
