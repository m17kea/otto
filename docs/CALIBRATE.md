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

## OttoDIY calibration sketch (recommended)
This uses the OttoDIY calibration example and saves trims into EEPROM.

Steps:
1. In Arduino IDE, open:
   File > Examples > OttoDIYLib > Otto_CalibrationWalk
2. Update the pins to match this project:
   - Left leg: 2
   - Right leg: 3
   - Left foot: 4
   - Right foot: 5
   - Buzzer: 12
3. Upload to the Nano.
4. Open Serial Monitor at 9600.
5. Use the keys printed in the sketch to adjust trims.
6. The sketch saves trims in EEPROM.

After calibration:
- To use EEPROM trims in this repo, set `load_calibration` to `true` in
  `otto.init(...)` inside `src/main.cpp` or `arduino/otto.ino`.
- If you prefer fixed trims, keep `load_calibration` as `false` and copy the
  final values into the `TRIM_*` constants.
