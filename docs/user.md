---
order: 2
---
# User Manual

{% include img.html src="images/quantizer_panel.png" height="640" %}

Change the mode by holding down the left encoder switch and turning clockwise or anticlockwise.

## 1. Scale and Chord Quantizer

---

## 2. Harmonic Walk

---

## 3 & 4. Generative Decoder for Notes and Percussion

A generative decoder for musical notes and percussion.

### Inputs:

**Buttons:**
1. Pauses the clock signal until next reset trgger is received
2. 
3. Hold to put into manual inference mode. 
   In manual inference mode, inference will only be performed when a trigger is recieved or the button is pressed.
   In auto inference mode, inference will always happen on a reset or after each sequence

**CV Inputs and knobs:**
1. Latent X value.
2. Latent Y value.
3. Latent X value.

**Trigger Inputs:**
1. Clock trigger. Each clock pulse advances the sequence by one.
2. Reset trigger. Resets the sequence back to the beginning. The sequence is automatically reset by the clock at the end of the sequence so this is only needed if resetting before the end of the sequence.
3. Inference. In manual inference mode a trigger in this input performs inference.

### Outputs:

**Musical Note mode:**

* **TOP ROW**: Trigger outputs
* **BOTTOM ROW**: 1 volt per octave outputs

**Percussion Mode:**

Actual output mapping depends on percussion map built into selected decoder model file but in general:

* **TOP ROW**: Triggers for Bass Drum / Tom Drum / Hi Hat / Cymbal
* **BOTTOM ROW**: Trigger for Snare / Accent values for Tom Drum / Hi Hat / Cymbal

---

## 4. Calibration

