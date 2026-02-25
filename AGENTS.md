# Otto Agent Notes

## Skills

- `otto-flash-calibrate`: Upload Otto sketches, handle serial-port detection,
  and run calibration/trim sync workflow.
  File: `/Users/michael.armitage/Documents/dev.nosync/otto/skills/otto-flash-calibrate/SKILL.md`

## Otto upload protocol

- Always discover the current serial device before uploading:
  `ls /dev/cu.*`
- Use new-bootloader environments only:
  - main: `nanoatmega328new`
  - avoid: `nano_avoid_new`
  - calibrate: `nano_calibrate_new`
- If upload fails, first close any serial monitor and retry once after
  re-running `ls /dev/cu.*`.
- Keep trim constants synchronized in both files:
  - `include/otto_robot_config.h`

## Firmware pre-commit check

- Before committing changes to Otto firmware (`src/*.cpp`, `arduino/*.ino`, or
  `include/otto_robot_config.h`), run:
  - `pio run -e nanoatmega328new`
- If obstacle-avoid behavior was changed, also run:
  - `pio run -e nano_avoid_new`
