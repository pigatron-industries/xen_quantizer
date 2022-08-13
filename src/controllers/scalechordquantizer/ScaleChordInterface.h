#ifndef ScaleChordInterface_h
#define ScaleChordInterface_h

#include "Hardware.h"
#include "lib/graphics/containers/VerticalContainer.h"
#include "lib/graphics/components/FieldComponent.h"
#include "lib/graphics/manager/FocusManager.h"
#include "NoteVisualiser.h"

class ScaleChordInterface {
    public:
        ScaleChordInterface() {}
        void init();
        void render();

        void setTuning(Tuning* tuning);
        void setScale(Scale* scale);
        void setChordDef(ChordDef* chordDef);
        void setChord(Chord* chord);

        void focusTuning();
        void focusScale();
        void focusChord();
        void focusOffset();

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 6> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CHORD QUANTIZER", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> tuningField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "TUNING:");
        FieldComponent<TFTDisplay> scaleField  = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "SCALE:");
        FieldComponent<TFTDisplay> chordField  = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "CHORD:");
        FieldComponent<TFTDisplay> offsetField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 50, "OFFSET:");

        NoteVisualiser<TFTDisplay> noteVisualiser = NoteVisualiser<TFTDisplay>(TFTDisplay::WIDTH, 10);
};

#endif
