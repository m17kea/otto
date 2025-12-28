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

### PlatformIO environments
- `nanoatmega328`: main sketch, old bootloader
- `nanoatmega328new`: main sketch, new bootloader
- `nano_calibrate`: calibration sketch, old bootloader (9600 baud)
- `nano_calibrate_new`: calibration sketch, new bootloader (9600 baud)

## Libraries
- PlatformIO pulls the OttoDIY library via `lib_deps` in `platformio.ini`.
- Arduino IDE: install `OttoDIYLib` from Library Manager or from https://github.com/OttoDIY/OttoDIYLib

## Serial and USB notes (macOS + CH340 clones)
- Install the WCH CH34x driver: `brew install --cask wch-ch34x-usb-serial-driver`
- Approve the driver in System Settings -> General -> Login Items & Extensions ->
  Driver Extensions, then reboot.
- The port usually appears as `/dev/cu.wchusbserial*`.
- Close any serial monitor before uploading or avrdude may fail.
- Calibration uses 9600 baud; the main sketch uses 115200.

## Obstacle avoidance behavior
- Reads the ultrasonic sensor on pins 8 (TRIG) and 9 (ECHO).
- If distance is under 15 cm, it backs up and turns.
- Turn direction is chosen randomly once per obstacle, then kept until clear.

## Build with Arduino IDE
1. Open `arduino/otto.ino` in Arduino IDE.
2. Select the correct board and port.
3. Upload to the robot.
