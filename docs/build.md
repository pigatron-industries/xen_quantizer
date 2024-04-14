---
order: 3
---
# Build Guide

## Base Board

1. Solder surface mount components onto base board. The components highlighted in red below do NOT need to be soldered.

    {% include img.html src="images/quantizer_baseboard_brd.drawio.png" height=1100 %}

2. Solder the power header (male header pins).

3. Solder the teensy header (female header).

4. Solder the through hole voltage regulator.

5. Solder the male header pins on the opposite side of the board. Headers marked in red above do not need to be soldered.

## Control Board

1. Solder surface mount components on the back of the control board.

    {% include img.html src="images/quantizer_controls_brd.drawio.png" height=1100 %}

2. Solder the female header rows. Headers marked in red above do not need to be soldered.

3. Use the spacers and screws to mount the OLED screen so the pins fit through the holes. Do not solder it yet.

4. Place the potentiometers, rotary encoders, and jacks onto the board but do not solder them yet.

5. Solder the controls onto the pcb.

6. Push the oled screen towards the front panel so that it is touching it, then solder the OLED pins.


## Teensy

1. With a knife, cut the trace for powering via USB. Check there is no continuity with a meter.

2. Solder the PSRAM to the back of the Teensy.

2. Solder the male headers pin onto the Teensy.
