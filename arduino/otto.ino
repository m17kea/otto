#include <Otto.h>

constexpr uint8_t SERVO_LEFT_HIP_PIN = 2;
constexpr uint8_t SERVO_RIGHT_HIP_PIN = 3;
constexpr uint8_t SERVO_LEFT_FOOT_PIN = 4;
constexpr uint8_t SERVO_RIGHT_FOOT_PIN = 5;
constexpr uint8_t ULTRASONIC_TRIG_PIN = 8;
constexpr uint8_t ULTRASONIC_ECHO_PIN = 9;
constexpr uint8_t BUZZER_PIN = 12;

constexpr int TRIM_LEFT_HIP = 18;
constexpr int TRIM_RIGHT_HIP = -23;
constexpr int TRIM_LEFT_FOOT = 0;
constexpr int TRIM_RIGHT_FOOT = -10;

constexpr long OBSTACLE_STOP_CM = 15;
constexpr unsigned long MOVE_INTERVAL_MS = 1600;

Otto ottoBot;
bool avoiding = false;
int avoidDir = RIGHT;

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

void applyServoTrims() {
  ottoBot.setTrims(TRIM_LEFT_HIP, TRIM_RIGHT_HIP, TRIM_LEFT_FOOT,
                   TRIM_RIGHT_FOOT);
}

void neutralPose() {
  ottoBot.home();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);

  Serial.begin(115200);
  delay(200);
  randomSeed(analogRead(A0));

  ottoBot.init(SERVO_LEFT_HIP_PIN, SERVO_RIGHT_HIP_PIN, SERVO_LEFT_FOOT_PIN,
               SERVO_RIGHT_FOOT_PIN, false, BUZZER_PIN);
  applyServoTrims();
  neutralPose();
  ottoBot.sing(S_connection);

  Serial.println("Otto robot starting...");
}

void loop() {
  static unsigned long lastMoveMs = 0;

  if (millis() - lastMoveMs < MOVE_INTERVAL_MS) {
    return;
  }
  lastMoveMs = millis();

  long distance = readUltrasonicCm();
  Serial.print("Ultrasonic (cm): ");
  Serial.println(distance);

  if (distance > 0 && distance < OBSTACLE_STOP_CM) {
    if (!avoiding) {
      avoiding = true;
      avoidDir = (random(0, 2) == 0) ? LEFT : RIGHT;
      digitalWrite(LED_BUILTIN, HIGH);
      ottoBot.sing(S_surprise);
      ottoBot.walk(1, 700, BACKWARD);
    }
    ottoBot.turn(2, 1200, avoidDir);
    return;
  }

  if (avoiding) {
    avoiding = false;
    digitalWrite(LED_BUILTIN, LOW);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  ottoBot.walk(1, 900, FORWARD);
  digitalWrite(LED_BUILTIN, LOW);
}
