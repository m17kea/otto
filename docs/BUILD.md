# Otto Build Guide

This is the main build guide for the baseline Otto robot used by this repo.

If you are building Otto for a classroom or for first-time AI-assisted setup,
start here. This guide is the canonical source for:
- which STL files to print
- which components are required
- which add-ons are optional
- example Amazon UK and AliExpress buying links

For firmware and calibration after the physical build, use:
- [`README.md`](../README.md)
- [`CALIBRATE.md`](CALIBRATE.md)
- [`TUTORIAL.md`](TUTORIAL.md)

## Recommended Classroom Build

This repo is tuned for a simple Nano-based Otto with:
- Arduino Nano ATmega328P
- new bootloader
- Nano shield style head
- four 9g servos
- HC-SR04 ultrasonic sensor
- active buzzer

Recommended print set for the baseline robot:
- Head: [`ottodiyheadv13_nanoshield.stl`](../hardware/printables/otto_diy/ottodiyheadv13_nanoshield.stl)
- Body: [`ottodiybodyv11_booster-square-switch.stl`](../hardware/printables/otto_diy/ottodiybodyv11_booster-square-switch.stl)
- Legs: 2x [`ottodiylegv13.stl`](../hardware/printables/otto_diy/ottodiylegv13.stl)
- Left foot: [`ottodiyfootlv13.stl`](../hardware/printables/otto_diy/ottodiyfootlv13.stl)
- Right foot: [`ottodiyfootrv13.stl`](../hardware/printables/otto_diy/ottodiyfootrv13.stl)
- Power button: [`power_switch_button.stl`](../hardware/printables/otto_diy/power_switch_button.stl)

Source model packs:
- Base Otto DIY pack: [Printables source](https://www.printables.com/model/31955-otto-diy-build-your-own-robot/files)
- Humanoid expansion pack: [Printables source](https://www.printables.com/model/132407-otto-diy-humanoid-robot/files)

Important:
- The committed trim values in this repo are a baseline for Michael's demo
  robot.
- If you use different servos, a different board, a different head/body, or a
  different mechanical assembly, assume recalibration may be required.

## Choose One: Body And Head Variants

### Recommended Head

- Default classroom choice:
  [`ottodiyheadv13_nanoshield.stl`](../hardware/printables/otto_diy/ottodiyheadv13_nanoshield.stl)
  for an Arduino Nano plus Nano I/O expansion shield.
- Alternative heads if you intentionally use different electronics:
  - [`ottodiyhead_esp8266.stl`](../hardware/printables/otto_diy/ottodiyhead_esp8266.stl)
  - [`ottodiyhead_ninjaboard.stl`](../hardware/printables/otto_diy/ottodiyhead_ninjaboard.stl)

### Choose One Body

- Recommended baseline:
  [`ottodiybodyv11_booster-square-switch.stl`](../hardware/printables/otto_diy/ottodiybodyv11_booster-square-switch.stl)
  for a switched boosted-supply style build.
- Alternative if your switch hardware differs:
  [`ottodiybody_booster-toggle-switch.stl`](../hardware/printables/otto_diy/ottodiybody_booster-toggle-switch.stl)
- Alternative if you intentionally want a rectangular 9V battery layout:
  [`ottodiybody_9vbattery.stl`](../hardware/printables/otto_diy/ottodiybody_9vbattery.stl)

### Standard Leg And Foot Parts

- Print 2x legs:
  [`ottodiylegv13.stl`](../hardware/printables/otto_diy/ottodiylegv13.stl)
- Left foot:
  [`ottodiyfootlv13.stl`](../hardware/printables/otto_diy/ottodiyfootlv13.stl)
- Right foot:
  [`ottodiyfootrv13.stl`](../hardware/printables/otto_diy/ottodiyfootrv13.stl)
- Power button:
  [`power_switch_button.stl`](../hardware/printables/otto_diy/power_switch_button.stl)

## Optional STL Files

These are not required for the baseline classroom build.

Humanoid expansion:
- [`Ottoexpand_Humanoid_ringV13.stl`](../hardware/printables/otto_diy_humanoid/Ottoexpand_Humanoid_ringV13.stl)
- [`Ottoexpand_ArmL13.stl`](../hardware/printables/otto_diy_humanoid/Ottoexpand_ArmL13.stl)
- [`Ottoexpand_ArmR13.stl`](../hardware/printables/otto_diy_humanoid/Ottoexpand_ArmR13.stl)
- [`Ottoexpand_Armhammer.stl`](../hardware/printables/otto_diy_humanoid/Ottoexpand_Armhammer.stl)
- [`Ottoexpand_matrixV13.stl`](../hardware/printables/otto_diy_humanoid/Ottoexpand_matrixV13.stl)

Use these only if you are intentionally extending the robot beyond the baseline
build used by this repo.

## Required Components

These parts are enough for the baseline build that this repo assumes.

| Component | Recommended spec | Required/Optional | Notes | Amazon UK | AliExpress |
|---|---|---|---|---|---|
| Arduino Nano | ATmega328P, 5V, 16 MHz, new bootloader, CH340 acceptable | Required | This repo assumes Nano pin numbering and the new bootloader. If you buy a different board, recalibration and firmware changes are more likely. | [Example search](https://www.amazon.co.uk/s?k=arduino+nano+atmega328p+ch340+new+bootloader) | [Example search](https://www.aliexpress.com/wholesale?SearchText=arduino+nano+atmega328p+ch340) |
| Nano expansion shield | Nano I/O sensor shield or expansion shield | Required for recommended head | The default head STL is the Nano shield head. If you skip the shield, use a different head and expect more manual wiring. | [Example search](https://www.amazon.co.uk/s?k=arduino+nano+sensor+shield) | [Example search](https://www.aliexpress.com/wholesale?SearchText=arduino+nano+sensor+shield) |
| Micro servos | 4x SG90 or MG90S, 9g class | Required | Four servos drive the hips and feet. Different servo models can change neutral alignment and may require recalibration. | [Example search](https://www.amazon.co.uk/s?k=sg90+servo+4+pack) | [Example search](https://www.aliexpress.com/wholesale?SearchText=sg90+servo+4+pack) |
| Ultrasonic sensor | HC-SR04, 5V | Required | Used by obstacle-avoid sketches. Pins in this repo assume a standard HC-SR04 style module. | [Example search](https://www.amazon.co.uk/s?k=hc-sr04+ultrasonic+sensor) | [Example search](https://www.aliexpress.com/wholesale?SearchText=hc-sr04+ultrasonic+sensor) |
| Active buzzer | 5V active buzzer module or 2-pin buzzer | Required | This repo expects a buzzer on D12 for sounds and startup feedback. | [Example search](https://www.amazon.co.uk/s?k=5v+active+buzzer+module) | [Example search](https://www.aliexpress.com/wholesale?SearchText=5v+active+buzzer+module) |
| Power setup | Stable 5V supply for a Nano plus 4 micro servos | Required | A weak supply causes jitter and resets. Use a proper 5V source or a tested battery-plus-booster setup. | [Example search](https://www.amazon.co.uk/s?k=5v+usb+power+bank+switch+module) | [Example search](https://www.aliexpress.com/wholesale?SearchText=5v+boost+module+switch+battery) |
| Power switch | Switch that matches your chosen body STL | Required | Pick a switch style that matches the body variant you print. | [Example search](https://www.amazon.co.uk/s?k=latching+push+button+switch+panel+mount) | [Example search](https://www.aliexpress.com/wholesale?SearchText=latching+push+button+switch+panel+mount) |
| Jumper wires | Dupont jumper wires, mixed pack | Required | Needed for ultrasonic, buzzer, shield, and add-on wiring. | [Example search](https://www.amazon.co.uk/s?k=dupont+jumper+wires+kit) | [Example search](https://www.aliexpress.com/wholesale?SearchText=dupont+jumper+wires+kit) |
| USB cable | Cable that matches your Nano clone | Required | Nano clones are often Mini-USB, but not always. Check before you buy. | [Example search](https://www.amazon.co.uk/s?k=mini+usb+cable+arduino+nano) | [Example search](https://www.aliexpress.com/wholesale?SearchText=mini+usb+cable+arduino+nano) |

## Optional Components

These are useful add-ons, but not required for the baseline robot.

| Component | Recommended spec | Required/Optional | Notes | Amazon UK | AliExpress |
|---|---|---|---|---|---|
| 8x8 LED matrix | MAX7219 module | Optional | Used for mouth and expressions in some demos. | [Example search](https://www.amazon.co.uk/s?k=max7219+8x8+matrix+module) | [Example search](https://www.aliexpress.com/wholesale?SearchText=max7219+8x8+matrix+module) |
| Bluetooth module | HC-05 or HC-06 style | Optional | Used by `otto_app`. Wiring differs slightly from the default buzzer-safe serial arrangement described in the repo. | [Example search](https://www.amazon.co.uk/s?k=hc-05+bluetooth+module) | [Example search](https://www.aliexpress.com/wholesale?SearchText=hc-05+bluetooth+module) |
| Photoresistor kit | LDR + resistor module or simple light sensor kit | Optional | Used by the photoresistor test sketch. | [Example search](https://www.amazon.co.uk/s?k=photoresistor+module+arduino) | [Example search](https://www.aliexpress.com/wholesale?SearchText=photoresistor+module+arduino) |
| Touch sensor | Capacitive or digital touch module | Optional | Used by touch-mode experiments. | [Example search](https://www.amazon.co.uk/s?k=arduino+touch+sensor+module) | [Example search](https://www.aliexpress.com/wholesale?SearchText=arduino+touch+sensor+module) |

## Tools And Consumables

These are not robot electronics, but they make the build much easier.

| Item | Recommended spec | Required/Optional | Notes | Amazon UK | AliExpress |
|---|---|---|---|---|---|
| 3D printer filament | PLA is the simplest starting point | Required | PLA is easiest for classroom or hobby use. | [Example search](https://www.amazon.co.uk/s?k=pla+filament+1.75mm) | [Example search](https://www.aliexpress.com/wholesale?SearchText=pla+filament+1.75mm) |
| Small screwdriver | Precision Phillips set | Required | Needed for servo screws and assembly. | [Example search](https://www.amazon.co.uk/s?k=precision+phillips+screwdriver+set) | [Example search](https://www.aliexpress.com/wholesale?SearchText=precision+phillips+screwdriver+set) |
| Cable management | Zip ties or double-sided tape | Optional | Helps keep wiring tidy inside the body and head. | [Example search](https://www.amazon.co.uk/s?k=small+zip+ties+double+sided+tape) | [Example search](https://www.aliexpress.com/wholesale?SearchText=small+zip+ties+double+sided+tape) |

## Buying Links And Affiliate Disclosure

Some links in this guide may be replaced with affiliate-enabled links later.
At the moment, the marketplace links below are standard example links unless you
manually swap them for your own tracked versions.

If you want a kickback from Amazon UK or AliExpress:
- replace the example marketplace links with your own affiliate-ready URLs
- keep the same component/spec guidance so the build advice stays stable even if
  a listing changes

### Shopping Notes

- These are **spec + example** links, not promises that one exact listing will
  remain the best option forever.
- Amazon UK is the first choice in this guide for simpler ordering and returns.
- AliExpress is included as a price-conscious alternative.
- Always check voltage, board type, servo count, and connector style before
  buying.
- If you intentionally buy different parts, assume you may need to recalibrate.

### Affiliate Disclosure

If affiliate-enabled URLs are added later, purchases made through those links
may earn a small commission at no extra cost to the buyer.

## Last Verified

- STL file paths in this repo verified: `2026-03-11`
- Printables source pages verified: `2026-03-11`
- Example Amazon UK and AliExpress search links verified for component intent:
  `2026-03-11`
