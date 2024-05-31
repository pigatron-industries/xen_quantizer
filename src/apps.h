#include "controllers/scalechordquantizer/ScaleChordController.h"
#include "controllers/quantizer/HarmonicWalkController.h"
#include "controllers/generativedecoder/NoteSequenceDecoderController.h"
#include "controllers/generativedecoder/DrumSequenceDecoderController.h"
#include "controllers/midi/MidiController.h"
#include "controllers/sequencer/SequencerController.h"
#include "controllers/calibration/CalibrationController.h"

#define CONTROLLERS \
ScaleChordController, \
HarmonicWalkController, \
SequencerController, \
NoteSequenceDecoderController, \
DrumSequenceDecoderController, \
MidiController, \
CalibrationController
