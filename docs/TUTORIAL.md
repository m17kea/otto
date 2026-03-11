# Otto DIY Build + Setup Tutorial

This tutorial covers the full build from printed parts to firmware setup, plus
instructions to use a code agent to build and upload sketches.

The canonical build reference is now [`docs/BUILD.md`](BUILD.md). Use that
guide for:
- the recommended classroom build
- exact STL links
- required and optional components
- example Amazon UK and AliExpress buying links

## 1) Parts list

For the full bill of materials and shopping links, see [`docs/BUILD.md`](BUILD.md).

Short version for the baseline robot:
- Arduino Nano (ATmega328P)
- Nano shield style head build
- 4x micro servos (SG90 or MG90S class)
- HC-SR04 ultrasonic sensor
- 5V active buzzer
- stable 5V power setup
- jumper wires

Useful optional add-ons:
- MAX7219 8x8 LED matrix
- Bluetooth module
- photoresistor module
- touch sensor module

## 2) Print the parts

The exact baseline STL list is documented in [`docs/BUILD.md`](BUILD.md).

Short version:
- base robot STLs live in `hardware/printables/otto_diy/`
- humanoid expansion STLs live in `hardware/printables/otto_diy_humanoid/`
- the recommended baseline head is `ottodiyheadv13_nanoshield.stl`

Tip: print a spare power button and confirm the body variant matches your power
switch plan before printing.

## 3) Assemble the robot

High-level steps:
1. Center servos to 90 degrees (use a quick test sketch).
2. Mount servos into the body/legs/feet.
3. Attach legs and feet to the body.
4. Route wires through the body and into the head.
5. Mount the Nano (or Nano + shield) in the head.
6. Add the ultrasonic sensor to the front.
7. Add the buzzer and optional LED matrix.
8. Close the head and check wire clearance.

## 4) Wiring (default pin map)

Servos:
- D2: left hip
- D3: right hip
- D4: left foot
- D5: right foot

Sensors and outputs:
- D8: ultrasonic trig
- D9: ultrasonic echo
- D12: buzzer
- D13: on-board LED

Optional:
- 8x8 LED matrix (MAX7219): A3 (DIN), A2 (CS), A1 (CLK)
- Photoresistor: A0
- Touch sensor: A0
- Bluetooth (for `otto_app`): RX 11, TX 7 (to avoid the buzzer pin)

Power note:
- Servos draw a lot of current. Use a dedicated 5V supply when possible and
  connect grounds together.

## 5) Software setup

PlatformIO (recommended):
1. Install PlatformIO CLI: `brew install platformio`
2. Connect the Nano and note the port (macOS example: `/dev/cu.wchusbserial*`).
3. Build/upload (new bootloader):
   - `pio run -e nanoatmega328new -t upload --upload-port <PORT>`

macOS CH340 driver (Nano clones):
- `brew install --cask wch-ch34x-usb-serial-driver`
- Approve in System Settings -> General -> Login Items & Extensions ->
  Driver Extensions, then reboot.

Serial monitor:
- Main sketch: `pio device monitor -b 115200 -p <PORT>`
- Calibration: `pio device monitor -b 9600 -p <PORT>`

## 6) Calibration

Run the calibration sketch:
- `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`

Use the keys shown in the serial monitor to adjust trims.
The final values can be used two ways:
- EEPROM trims: set `load_calibration` to `true`
- Fixed trims: set `load_calibration` to `false` and copy `TRIM_*` values

Details: `docs/CALIBRATE.md`

## 7) Example sketches

All OttoDIYLib examples are included and wired for this build. Each has
PlatformIO envs `nano_<example>_new`.

Examples:
- `otto_allmoves` (uses LED matrix if installed)
- `otto_app`
- `otto_avoid`
- `otto_calibrationwalk`
- `otto_happybirthday`
- `otto_photoresistor_test`
- `otto_singleladies`
- `otto_smoothcriminal`
- `otto_testsensor`
- `otto_touchmodes`

Example upload:
`pio run -e nano_allmoves_new -t upload --upload-port <PORT>`

## 8) Build this repo from scratch using a code agent

You can ask a code agent (like Codex CLI) to run the steps for you. Example
workflow:
1. Clone:
   - `git clone git@github.com:m17kea/otto.git`
   - `cd otto`
2. Install PlatformIO:
   - `brew install platformio`
3. Find the Nano port:
   - `pio device list` or `ls /dev/cu.*`
4. Upload a sketch:
   - `pio run -e nanoatmega328new -t upload --upload-port <PORT>`
5. Open serial:
   - `pio device monitor -b 115200 -p <PORT>`
6. Calibrate (optional):
   - `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`
   - `pio device monitor -b 9600 -p <PORT>`

If uploads fail with sync errors:
- Close any serial monitor.
- Replug the board or press reset.

## 9) Troubleshooting quick hits

- Garbled serial output: wrong baud rate.
- No serial port: wrong cable/driver, or board not powered.
- Servo jitter or resets: power supply too weak.
- Obstacle detection not working: check ultrasonic wiring and pins (D8/D9).
