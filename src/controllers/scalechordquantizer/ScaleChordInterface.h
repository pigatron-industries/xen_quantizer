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
        void setChord(ChordDef* chordDef);

        void focusTuning();
        void focusScale();
        void focusChord();

    private:
        FocusManager<TFTDisplay> focusManager;

        VerticalContainer<TFTDisplay, 5> page;
        TextComponent<TFTDisplay> title = TextComponent<TFTDisplay>(TFTDisplay::WIDTH, "CHORD QUANTIZER", 2, TFT_ORANGE);
        FieldComponent<TFTDisplay> tuningField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 40, "TUNING:");
        FieldComponent<TFTDisplay> scaleField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 40, "SCALE:");
        FieldComponent<TFTDisplay> chordField = FieldComponent<TFTDisplay>(TFTDisplay::WIDTH, 40, "CHORD:");

        NoteVisualiser<TFTDisplay> noteVisualiser = NoteVisualiser<TFTDisplay>(TFTDisplay::WIDTH, 10);
};

#endif
