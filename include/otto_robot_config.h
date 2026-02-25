#ifndef OTTO_ROBOT_CONFIG_H
#define OTTO_ROBOT_CONFIG_H

#include <Arduino.h>

namespace otto_cfg {
constexpr uint8_t SERVO_LEFT_HIP_PIN = 2;
constexpr uint8_t SERVO_RIGHT_HIP_PIN = 3;
constexpr uint8_t SERVO_LEFT_FOOT_PIN = 4;
constexpr uint8_t SERVO_RIGHT_FOOT_PIN = 5;
constexpr uint8_t ULTRASONIC_TRIG_PIN = 8;
constexpr uint8_t ULTRASONIC_ECHO_PIN = 9;
constexpr uint8_t BUZZER_PIN = 12;

// Known-good calibration for the current mechanical build.
constexpr int TRIM_LEFT_HIP = 18;
constexpr int TRIM_RIGHT_HIP = -23;
constexpr int TRIM_LEFT_FOOT = 0;
constexpr int TRIM_RIGHT_FOOT = -10;

constexpr long OBSTACLE_STOP_CM = 15;
constexpr unsigned long MOVE_INTERVAL_MS = 1600;
}  // namespace otto_cfg

#endif  // OTTO_ROBOT_CONFIG_H
