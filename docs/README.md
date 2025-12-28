# Docs

Notes, calibration steps, and build logs for the Otto DIY robot.

## Hardware notes
- Board: Nano mini v3
- Shield: V3.0 I/O Expansion Breakout Sensor Module Board for Nano

## Pin map (default)
- D2: left hip servo
- D3: right hip servo
- D4: left foot servo
- D5: right foot servo
- D8: ultrasonic trig
- D9: ultrasonic echo
- D12: buzzer
- D13: status LED (on-board)

## Calibration
- Adjust `TRIM_*` constants in `src/main.cpp` or `arduino/otto.ino` until neutral pose is level.
- Positive values push the servo angle higher, negative values lower.
- After trimming, power-cycle to confirm the neutral pose looks stable.
