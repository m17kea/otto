---
name: otto-flash-calibrate
description: Use when working in the Otto robot repo to upload main/avoid/calibration firmware, check the active serial port, and apply calibration trims consistently across sketches.
---

# Otto Flash Calibrate

## Overview

This skill provides a repeatable upload and calibration workflow for Otto on a
Nano ATmega328 new bootloader. It minimizes failed uploads and trim drift
across firmware by writing trims to `include/otto_robot_config.h`.

## Trigger phrases

Use this skill when the user asks to:
- upload or flash Otto firmware
- switch between `main.cpp`, `otto_avoid`, or calibration firmware
- recalibrate and update `TRIM_*` values
- diagnose upload failures related to serial monitor or changing `/dev/cu.*` ports

## Workflow

1. Detect current port:
   - `ls /dev/cu.*`
   - Prefer `/dev/cu.wchusbserial*` when present.
2. Ensure no monitor is attached before upload.
3. Upload the requested firmware:
   - Main sketch:
     `pio run -e nanoatmega328new -t upload --upload-port <PORT>`
   - Avoid sketch:
     `pio run -e nano_avoid_new -t upload --upload-port <PORT>`
   - Calibration sketch:
     `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`
4. If upload fails due to missing port:
   - Re-run `ls /dev/cu.*`
   - Use the new port and retry once.
5. For calibration:
   - Open monitor: `pio device monitor -b 9600 -p <PORT>`
   - Use keys: `a/z`, `s/x`, `k/m`, `j/n`, `f`, `h`, `p`
   - Capture `Trims (LL, RL, LF, RF)` values.
6. Sync fixed trims from the printed line:
   - `skills/otto-flash-calibrate/scripts/sync-trims.sh "Trims (LL, RL, LF, RF): <LL>, <RL>, <LF>, <RF>"`
7. Verify the shared config diff:
   - `git diff -- include/otto_robot_config.h`
8. Quick compile check when firmware files changed:
   - `pio run -e nanoatmega328new`
   - `pio run -e nano_avoid_new` (if avoid flow changed)

## Notes

- If the user says "upload main" or "upload avoid," run the upload directly.
- If the user says "recalibrate," upload calibration first and then provide the
  key map at 9600 baud.
- Prefer updating `include/otto_robot_config.h` over editing trim constants in
  individual sketches.
- If behavior is circling or drifting, verify trim signs and confirm servo/pin
  mapping before changing gait logic.
