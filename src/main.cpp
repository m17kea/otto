#include <Arduino.h>
#include <Servo.h>

constexpr uint8_t SERVO_LEFT_HIP_PIN = 2;
constexpr uint8_t SERVO_RIGHT_HIP_PIN = 3;
constexpr uint8_t SERVO_LEFT_FOOT_PIN = 4;
constexpr uint8_t SERVO_RIGHT_FOOT_PIN = 5;
constexpr uint8_t ULTRASONIC_TRIG_PIN = 8;
constexpr uint8_t ULTRASONIC_ECHO_PIN = 9;
constexpr uint8_t BUZZER_PIN = 12;

Servo servoLeftHip;
Servo servoRightHip;
Servo servoLeftFoot;
Servo servoRightFoot;

long readUltrasonicCm() {
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

  long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    return -1;
  }
  return duration / 58;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  servoLeftHip.attach(SERVO_LEFT_HIP_PIN);
  servoRightHip.attach(SERVO_RIGHT_HIP_PIN);
  servoLeftFoot.attach(SERVO_LEFT_FOOT_PIN);
  servoRightFoot.attach(SERVO_RIGHT_FOOT_PIN);

  servoLeftHip.write(90);
  servoRightHip.write(90);
  servoLeftFoot.write(90);
  servoRightFoot.write(90);

  Serial.begin(115200);
  delay(200);
  Serial.println("Otto robot starting...");
}

void loop() {
  static unsigned long lastLogMs = 0;

  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);

  if (millis() - lastLogMs >= 1000) {
    lastLogMs = millis();
    long distance = readUltrasonicCm();
    Serial.print("Ultrasonic (cm): ");
    Serial.println(distance);
  }
}
