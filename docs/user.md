---
order: 2
---
# User Manual

{% include img.html src="images/quantizer_panel_guide.drawio.png" height="640" %}

Change the mode by holding down the left encoder switch and turning clockwise or anticlockwise.

Parameters are changed by first selecting it with left encoder, then changing the value with the right encoder. 
Some parameters need to be set by pressing down on the right encoder.

## 1. Scale and Chord Quantizer

Quantize incoming analog voltages to selected scale and chord.

### Menu:

### Inputs:

**Buttons:**

**CV Inputs and knobs:**

1. **Offset.** 
2. 
3. 
4. **No Quantize.** While this input is high, quantization is disabled and inputs are passed through to outputs unchanged.

**Inputs:**
1. **Select root.** A trigger on this input will quantize the signal on analog input 1 to the nearest note in the selected scale. This will be used as the root note for a chord.
2. **Chord note 2.** Quantized to nearest note in selected chord starting from root note on input 1.
3. **Chord note 3.** Quantized to nearest note in selected chord starting from root note on input 1.
4. **Chord note 4.** Quantized to nearest note in selected chord starting from root note on input 1.


---

## 2. Harmonic Walk

---

## 3. Sequencer

---

## 4 & 5. Generative Decoder for Notes and Percussion

A generative decoder for musical notes and percussion. This is the decoder part of a pretrained variational autoencoder, where the inputs map to a location in the latent space of the model.

Pretrained decoder models are stored on the SD card. 
Percussion models go in the **/models/perc** folder, and musical note models in the **/models/note** folder.

See [VAE Musical Sequence Generation](https://pigatron-industries.github.io/2023/10/27/VAE-Musical-Sequence-Generation.html) for more technical details about how this works.

### Menu:

### Inputs:

**Buttons:**
1. Pauses the clock signal until next reset trigger is received
2. 
3. Hold to put into manual inference mode. 
   In manual inference mode, inference will only be performed when a trigger is recieved or the button is pressed.
   In auto inference mode, inference will always happen on a reset or after each sequence

**CV Inputs and knobs:**
1. Latent X value.
2. Latent Y value.
3. Latent Z value.

**Trigger Inputs:**
1. **Clock trigger.** Each clock pulse advances the sequence by one.
2. **Reset trigger.** Resets the sequence back to the beginning. The sequence is automatically reset by the clock at the end of the sequence so this is only needed if resetting before the end of the sequence.
3. **Inference.** In manual inference mode a trigger in this input performs inference.

### Outputs:

**Musical Note mode:**
* **TOP ROW**: Trigger outputs
* **BOTTOM ROW**: 1 volt per octave outputs

**Percussion Mode:**
Actual output mapping depends on percussion map built into selected decoder model file but in general:
* **TOP ROW**: Triggers for Bass Drum / Tom Drum / Hi Hat / Cymbal
* **BOTTOM ROW**: Trigger for Snare / Accent values for Tom Drum / Hi Hat / Cymbal

---

## 6. MIDI

---

## 7. Calibration

