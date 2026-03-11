# Otto In The Classroom

This guide is for children, teachers, and parents who want to use Otto with an
AI helper.

## What The AI Is Good At

An AI helper can:
- tell you which command to run
- help you choose the right sketch
- explain what a robot move means
- help you calibrate Otto step by step
- help you understand what to look for physically

An AI helper cannot:
- see your robot unless you tell it what Otto looks like
- feel whether a servo is mounted correctly
- automatically know whether your physical robot matches the demo build

That means the best way to work is:
1. Run one small step.
2. Look at Otto.
3. Tell the AI exactly what you see.
4. Let the AI suggest the next step.

## What To Look At Physically

When Otto is in the `home()` position, check:
- is Otto standing level?
- is one leg twisted out?
- is one foot turned more than the other?
- does Otto lean left or right?
- does Otto drift when it tries to walk forward?
- does it buzz, shake, or reset when it moves?

Useful descriptions for the AI:
- "His right leg is turned out."
- "She leans to the left when standing still."
- "Otto walks in a curve instead of straight."
- "One foot points down more than the other."
- "The serial port changed after I unplugged it."

## Best First Questions To Ask An AI

These are good copy-paste prompts.

1. `I have this Otto repo open. Help me detect the board, find the serial port, and decide if I should calibrate before uploading anything.`
2. `Please explain the difference between the main sketch, all-moves demo, custom demo, and calibration sketch in simple words.`
3. `Put Otto into calibration mode and tell me what to look for when he stands on a flat table.`
4. `Otto is standing unevenly. Ask me one thing at a time and tell me which trim key to press next.`
5. `I want to upload the shortest fun demo for a classroom. Which sketch should I use and what command should I run?`
6. `Otto walks in a curve. Help me work out if this is a calibration problem, a wiring problem, or a servo horn problem.`
7. `Please explain these trim values to me like I am new to robots: Trims (LL, RL, LF, RF): 18, -23, 0, -10`
8. `I want to learn with Otto and AI. Give me three safe experiments to try, one at a time.`

## A Safe Learning Loop

Use this loop every time:

1. Ask the AI what sketch to use.
2. Find the serial port.
3. Upload one sketch only.
4. Watch Otto closely.
5. Describe the result in simple words.
6. Let the AI suggest the next step.

Do not change lots of things at once.

Good:
- change one trim value
- upload one sketch
- test one movement

Not good:
- remount servos, change wiring, change trims, and upload a different sketch all
  at the same time

## When You Should Calibrate First

Calibrate before trusting the demos if:
- your robot is built differently from the demo robot
- your servo horns were moved
- your board is different
- Otto does not stand level
- Otto walks strangely right away

The AI can help you with calibration, but a person must still look at the robot
and say what seems wrong.

## For Teachers And Parents

The easiest classroom flow is:
- have one known-good robot ready
- let children compare their Otto to the known-good robot
- use the AI as a guided assistant, not as a replacement for observation
- encourage children to describe the robot in plain language before touching any
  commands

Good learning outcomes from this project:
- following a feedback loop
- understanding that software and hardware affect each other
- learning that AI is strongest when the human gives good observations

## Quick Command Reminder

These commands are useful when an adult or an experienced student is helping.

Find the port:
```bash
ls /dev/cu.*
```

Upload calibration:
```bash
pio run -e nano_calibrate_new -t upload --upload-port <PORT>
```

Open calibration monitor:
```bash
pio device monitor -b 9600 -p <PORT>
```

Upload the full movement demo:
```bash
pio run -e nano_allmoves_new -t upload --upload-port <PORT>
```
