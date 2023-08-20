#include "controllers/scalechordquantizer/ScaleChordController.h"
#include "controllers/quantizer/HarmonicWalkController.h"
#include "controllers/generativedecoder/NoteSequenceDecoderController.h"
#include "controllers/generativedecoder/DrumSequenceDecoderController.h"
#include "controllers/calibration/CalibrationController.h"

#define CONTROLLERS \
ScaleChordController, \
HarmonicWalkController, \
NoteSequenceDecoderController, \
DrumSequenceDecoderController, \
CalibrationController
