#include "controllers/scalechordquantizer/ScaleChordController.h"
#include "controllers/quantizer/HarmonicWalkController.h"
#include "controllers/generativedecoder/NoteSequenceDecoderController.h"
#include "controllers/generativedecoder/DrumSequenceDecoderController.h"
#include "controllers/midi/MidiController.h"
#include "controllers/calibration/CalibrationController.h"

#define CONTROLLERS \
ScaleChordController, \
HarmonicWalkController, \
NoteSequenceDecoderController, \
DrumSequenceDecoderController, \
MidiController, \
CalibrationController
