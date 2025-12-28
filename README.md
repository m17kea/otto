# Otto DIY Robot

Code and notes for building and programming the Otto DIY robot.

## Structure
- `src/` PlatformIO sketch (primary)
- `arduino/` Arduino IDE sketch
- `docs/` build notes and calibration
- `hardware/` CAD, wiring, and parts

## Build with PlatformIO
1. Install PlatformIO (VS Code extension or CLI).
2. Update `platformio.ini` with your board if needed.
3. Build and upload:
   - `pio run`
   - `pio run -t upload`

## Libraries
- PlatformIO pulls the OttoDIY library via `lib_deps` in `platformio.ini`.
- Arduino IDE: install `OttoDIYLib` from Library Manager or from https://github.com/OttoDIY/OttoDIYLib

## Build with Arduino IDE
1. Open `arduino/otto.ino` in Arduino IDE.
2. Select the correct board and port.
3. Upload to the robot.
