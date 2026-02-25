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

### Quick field workflow (macOS + CH340)
1. Find the active Nano port:
   - `ls /dev/cu.*`
2. Upload the main sketch:
   - `pio run -e nanoatmega328new -t upload --upload-port <PORT>`
3. Upload obstacle avoid:
   - `pio run -e nano_avoid_new -t upload --upload-port <PORT>`
4. Upload calibration sketch:
   - `pio run -e nano_calibrate_new -t upload --upload-port <PORT>`
5. Open serial monitor:
   - Main/avoid: `pio device monitor -b 115200 -p <PORT>`
   - Calibration: `pio device monitor -b 9600 -p <PORT>`

If upload fails, close any serial monitor first, then re-check the port with
`ls /dev/cu.*` and retry.

### PlatformIO environments
- `nanoatmega328new`: main sketch (new bootloader)
- `nano_calibrate_new`: calibration sketch (9600 baud)
- Example sketches use `nano_<example>_new`.

### OttoDIY example sketches (adapted)
Arduino sketches live in `arduino/` with matching PlatformIO envs:
- `otto_allmoves` (8x8 LED matrix on A3/A2/A1 if installed)
- `otto_app`
- `otto_avoid`
- `otto_calibrationwalk`
- `otto_happybirthday`
- `otto_photoresistor_test`
- `otto_singleladies`
- `otto_smoothcriminal`
- `otto_testsensor`
- `otto_touchmodes`

Adaptations:
- Servo pins: 2/3/4/5, buzzer: 12, ultrasonic: 8/9.
- `otto_app` moves Bluetooth serial to pins 11/7 to avoid the buzzer pin.

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
- If distance is under 15 cm, it plays the surprise sound and turns right.

## Build with Arduino IDE
1. Open `arduino/otto.ino` in Arduino IDE.
2. Select the correct board and port.
3. Upload to the robot.
