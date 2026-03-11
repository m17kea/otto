# Otto DIY Robot

Otto is a small walking robot that is ideal for learning three things together:
electronics, firmware, and how to work with an AI helper on a real physical
project.

This repo is written as a public starting point. It includes firmware, adapted
OttoDIY example sketches, calibration tools, and agent guidance so a new person
or a new AI agent can get from "board plugged in" to "robot moving" quickly.

## Start Here

If you are a person:
1. Read the recalibration check below.
2. Find the serial port for your board.
3. If your build differs from the known demo build, calibrate first.
4. Upload the sketch you want to run.

If you are an AI agent:
1. Detect the serial port.
2. Identify the board and bootloader family.
3. Compare the physical build to the known build assumptions in this repo.
4. If anything important differs, calibrate before trusting motion demos.

Useful docs:
- Classroom guide: [`docs/CLASSROOM.md`](docs/CLASSROOM.md)
- Full build tutorial: [`docs/TUTORIAL.md`](docs/TUTORIAL.md)
- Calibration guide: [`docs/CALIBRATE.md`](docs/CALIBRATE.md)

## Do I Need To Recalibrate?

Use this rule:

Calibrate first if **any** of these are true:
- your board is not an Arduino Nano ATmega328P with the new bootloader
- your USB adapter or serial device name differs from what you expect and you
  are not yet sure the board setup matches the original build
- your servo model changed
- a servo horn was removed, re-mounted, or looks one spline off
- left/right wiring might be swapped
- the robot body, legs, feet, or wiring differ from the known demo build
- Otto does not stand level in `home()`
- Otto drifts, twists, or turns unexpectedly when it should walk straight
- trim values differ dramatically in sign from the baseline for no clear
  mechanical reason

You can usually keep the committed trim values if **all** of these are true:
- the board and bootloader match
- the wiring matches the documented pin map
- the servo horns were centered and mounted the same way
- Otto stands level in `home()`
- Otto walks and turns as expected

Important:
- The firmware cannot reliably infer whether a physical robot needs
  recalibration.
- Calibration is a human-in-the-loop physical check.
- The committed trims are a **baseline for Michael's demo robot**, not universal
  defaults for every Otto build.

## What An AI Agent Should Detect First

Before uploading a normal sketch, an agent should determine:
- which serial device is currently active
- which board and bootloader family are connected
- whether the physical build appears to match the known demo build
- whether calibration is required before trusting existing trim values

The recommended sequence is:
1. Detect the serial port:
   - `ls /dev/cu.*`
2. Confirm the board family and use the correct PlatformIO environment.
3. If the build differs or Otto looks physically wrong, upload calibration:
   - `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`
4. Place Otto on a flat surface and check the neutral pose visually.
5. Adjust trims only if posture or gait is visibly wrong.
6. Print the final trims from the calibration sketch.
7. Sync the final trims into [`include/otto_robot_config.h`](include/otto_robot_config.h):
   - `./skills/otto-flash-calibrate/scripts/sync-trims.sh "Trims (LL, RL, LF, RF): <LL>, <RL>, <LF>, <RF>"`
8. Rebuild and upload the runtime sketch you actually want.

## Known Demo Build Assumptions

These settings describe the robot used for the original live demo and the
current committed firmware defaults:

- Board: Arduino Nano ATmega328P
- Bootloader: new bootloader
- USB on macOS example: CH340-style serial adapter, often
  `/dev/cu.wchusbserial*`
- Servo pins:
  - D2: left hip
  - D3: right hip
  - D4: left foot
  - D5: right foot
- Ultrasonic sensor:
  - D8: trig
  - D9: echo
- Buzzer:
  - D12
- Baseline trims for Michael's demo robot:
  - Left hip (LL): `18`
  - Right hip (RL): `-23`
  - Left foot (LF): `0`
  - Right foot (RF): `-10`

Do not assume those trim values are correct for another Otto build without a
physical posture check.

## Quick PlatformIO Workflow

1. Install PlatformIO.
2. Plug the robot in.
3. Find the port:
   - `ls /dev/cu.*`
4. Decide whether to calibrate first using the checklist above.
5. Upload the sketch you want.

Common commands:

- Main sketch:
  - `pio run -e nanoatmega328new -t upload --upload-port <PORT>`
- Full all-moves demo:
  - `pio run -e nano_allmoves_new -t upload --upload-port <PORT>`
- Custom classroom demo:
  - `pio run -e nano_custom_demo_new -t upload --upload-port <PORT>`
- Obstacle avoid:
  - `pio run -e nano_avoid_new -t upload --upload-port <PORT>`
- Calibration:
  - `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`

Serial monitor:
- Main and movement demos:
  - `pio device monitor -b 115200 -p <PORT>`
- Calibration:
  - `pio device monitor -b 9600 -p <PORT>`

If upload fails:
- close any serial monitor first
- run `ls /dev/cu.*` again
- retry with the current port

## Repo Structure

- `src/`: PlatformIO shims and firmware entrypoints
- `arduino/`: Arduino-style sketches
- `docs/`: setup, calibration, and classroom material
- `hardware/`: printables and physical build assets
- `include/otto_robot_config.h`: shared pin map, trims, and movement constants
- `skills/otto-flash-calibrate/`: repeatable agent workflow for upload and
  calibration

## Included Sketches

Main runtime sketches:
- `nanoatmega328new`: simple main sketch
- `nano_allmoves_new`: full OttoDIY movement demo
- `nano_custom_demo_new`: shorter custom demo used for live classroom
  demonstration
- `nano_avoid_new`: obstacle avoidance
- `nano_calibrate_new`: calibration sketch

Adapted OttoDIY examples are also available:
- `otto_app`
- `otto_calibrationwalk`
- `otto_happybirthday`
- `otto_photoresistor_test`
- `otto_singleladies`
- `otto_smoothcriminal`
- `otto_testsensor`
- `otto_touchmodes`

## Hardware Config Source

Shared settings live in
[`include/otto_robot_config.h`](include/otto_robot_config.h).

That file centralizes:
- pin mapping
- committed trim constants
- obstacle distance threshold
- movement timing constants

If you finish calibration for a new physical build, sync the final trims back to
that shared config so future uploads match the robot you just tuned.

## Libraries

- PlatformIO installs `OttoDIYLib` and `Servo` from `platformio.ini`
- Arduino IDE users should install `OttoDIYLib` manually if needed

## Serial And USB Notes

On macOS with CH340-based Nano clones:
- install the driver with
  `brew install --cask wch-ch34x-usb-serial-driver`
- approve it in System Settings if prompted
- reboot if the driver does not appear immediately

Typical serial naming:
- CH340 Nano: `/dev/cu.wchusbserial*`
- Other boards may differ, which is one signal that you should re-check whether
  the build matches the baseline assumptions

## Build With Arduino IDE

1. Open the sketch you want in `arduino/`.
2. Select the correct board and serial port.
3. Upload the sketch.
4. If posture is wrong, switch to the calibration sketch before continuing.

## Public Workshop Site

A companion public workshop site can be built from the sibling project at
`../otto-site` and published to `otto.armitage.cloud`.

That site is intended to give children, parents, and teachers:
- a friendly introduction to Otto
- a quick AI-first getting started path
- a classroom-safe recalibration checklist
- prompt ideas and troubleshooting help
