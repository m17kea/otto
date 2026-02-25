# Calibration

This guide helps you find the servo trim offsets (the `TRIM_*` values) so Otto
stands level with all servos at 90 degrees.

## Quick manual method (edit + upload)
1. Set all trim constants to `0` in `src/main.cpp` (or `arduino/otto.ino`).
2. Upload and place Otto on a flat surface.
3. Identify which limb is off-level.
4. Adjust only that trim by small steps (plus or minus 1 or 2).
5. Upload again and repeat until the neutral pose is level.

Notes:
- If a positive trim makes it worse, flip the sign.
- The final values are the offsets to keep.

## Current known-good trims
- Left leg (LL): `18`
- Right leg (RL): `-23`
- Left foot (LF): `0`
- Right foot (RF): `-10`

## OttoDIY calibration sketch (recommended)
This uses the OttoDIY calibration example and saves trims into EEPROM.

Steps:
1. In Arduino IDE, open:
   `arduino/otto_calibrate/otto_calibrate.ino`
2. Update the pins to match this project:
   - Left leg: 2
   - Right leg: 3
   - Left foot: 4
   - Right foot: 5
   - Buzzer: 12
3. Upload to the Nano.
4. Open Serial Monitor at 9600.
5. Use the keys printed in the sketch to adjust trims.
6. Press `p` to print the current trims.
7. The sketch saves trims in EEPROM after each change.

Key map:
- `a` / `z`: left leg plus / minus
- `s` / `x`: left foot plus / minus
- `k` / `m`: right leg plus / minus
- `j` / `n`: right foot plus / minus
- `f`: test walk
- `h`: return home
- `p`: print trims

## Sync trims into firmware constants
All runtime firmware reads trim values from:
- `include/otto_robot_config.h`

Use the skill helper script with the printed serial line:
- `skills/otto-flash-calibrate/scripts/sync-trims.sh "Trims (LL, RL, LF, RF): 18, -23, 0, -10"`

Then run a quick compile check:
- `pio run -e nanoatmega328new`
- `pio run -e nano_avoid_new`

### Run without Arduino IDE (PlatformIO CLI)
Prereqs:
- Install PlatformIO CLI (for example, `brew install platformio`).
- On macOS with CH340-based Nano clones, install the WCH driver:
  `brew install --cask wch-ch34x-usb-serial-driver`
  Then allow it in System Settings -> General -> Login Items & Extensions ->
  Driver Extensions, and reboot.

1. Plug in the Nano and note its serial port (for example, `/dev/tty.usbserial-*`).
2. Upload the calibration sketch:
   `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`
3. Open a serial monitor at 9600:
   `pio device monitor -b 9600 -p <PORT>`
4. Use the keys printed in the sketch to adjust trims and press `p` to print.

Troubleshooting:
- Close any serial monitor before uploading; open ports can cause sync errors.
- Garbled serial output means the baud rate is wrong (calibration uses 9600).
- CH340 ports usually show up as `/dev/cu.wchusbserial*` on macOS.

If a trim changes sign dramatically between sessions (for example, right hip
from negative to positive), check mechanics before trusting the number:
- Servo horn was re-seated on a different spline index (or 180 degrees off)
- Servo orientation was flipped during reassembly
- Left/right servo wiring was swapped (D2 vs D3)

After calibration:
- To use EEPROM trims in this repo, set `load_calibration` to `true` in
  `otto.init(...)` inside `src/main.cpp` or `arduino/otto.ino`.
- If you prefer fixed trims, keep `load_calibration` as `false` and copy the
  final values into the `TRIM_*` constants.
