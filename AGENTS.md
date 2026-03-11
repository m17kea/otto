# Otto Agent Notes

This repo is meant to be operable by a new AI agent without prior knowledge of
the specific robot used in the original demo.

The most important rule is:

Do not assume the committed trim values are correct for the robot in front of
you. They are reference values for Michael's demo robot, not universal values.

## Skills

- `otto-flash-calibrate`: Upload Otto sketches, handle serial-port detection,
  and run calibration/trim sync workflow.
  File: `skills/otto-flash-calibrate/SKILL.md`

## First Look Checklist

Before uploading a normal runtime sketch:
1. Detect the active serial device:
   - `ls /dev/cu.*`
2. Confirm the board/bootloader family if possible.
3. Compare the physical build to the known build assumptions below.
4. Decide whether calibration is required before trusting motion behavior.

## Required Calibration Triage

Calibrate first if **any** of these are true:
- the board is not a Nano ATmega328P with the new bootloader
- the serial device naming or USB adapter suggests a different board setup
- servo horns were remounted or look misaligned
- the servo model differs from the known build
- the wiring may differ from the documented pin map
- the body, legs, or feet were rebuilt or replaced
- Otto does not stand level in `home()`
- Otto drifts, twists, or turns unexpectedly
- left/right movement appears inverted
- trim values differ dramatically in sign from the baseline without a clear
  mechanical explanation

If any mismatch is true, use calibration before trusting demos.

## Standard Human-In-The-Loop Calibration Sequence

1. Detect the current serial port.
2. Upload the calibration sketch:
   - `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`
3. Open the calibration monitor:
   - `pio device monitor -b 9600 -p <PORT>`
4. Ask the human to place Otto on a flat surface.
5. Check the neutral pose visually.
6. Adjust trims only when posture or gait is visibly wrong.
7. Print the final trim line with `p`.
8. Sync the final values into `include/otto_robot_config.h`:
   - `./skills/otto-flash-calibrate/scripts/sync-trims.sh "Trims (LL, RL, LF, RF): <LL>, <RL>, <LF>, <RF>"`
9. Rebuild and upload the runtime sketch the user actually wants.

## Known Build Assumptions

These assumptions describe the original demo robot only:

- Board: Arduino Nano ATmega328P
- Bootloader: new bootloader
- macOS USB example: CH340 serial adapter, often `/dev/cu.wchusbserial*`
- Pin map:
  - D2 left hip
  - D3 right hip
  - D4 left foot
  - D5 right foot
  - D8 ultrasonic trig
  - D9 ultrasonic echo
  - D12 buzzer
- Current committed baseline trims:
  - LL `18`
  - RL `-23`
  - LF `0`
  - RF `-10`

Treat those trim values as a baseline reference only.

## Upload Protocol

- Always discover the current serial device before uploading:
  - `ls /dev/cu.*`
- Use new-bootloader environments only:
  - main: `nanoatmega328new`
  - custom demo: `nano_custom_demo_new`
  - all moves: `nano_allmoves_new`
  - avoid: `nano_avoid_new`
  - calibrate: `nano_calibrate_new`
- If upload fails, first close any serial monitor and retry once after
  re-running `ls /dev/cu.*`.

## Preferred Runtime Targets

- `nanoatmega328new`: simple main sketch
- `nano_custom_demo_new`: short classroom-friendly demo
- `nano_allmoves_new`: full movement demo
- `nano_avoid_new`: obstacle avoid mode

If the robot is newly built or mechanically uncertain, do not start with a long
demo sketch. Calibrate first or use a simpler target.

## Classroom-Friendly Behavior

When helping children:
- ask for one physical observation at a time
- use plain language before using robot jargon
- prefer short commands and short feedback loops
- explain that the AI cannot see the robot unless the child describes it

Recommended child-friendly doc:
- `docs/CLASSROOM.md`

## Firmware Pre-Commit Check

Before committing changes to Otto firmware (`src/*.cpp`, `arduino/*.ino`, or
`include/otto_robot_config.h`), run:
- `pio run -e nanoatmega328new`

If obstacle-avoid behavior changed, also run:
- `pio run -e nano_avoid_new`
