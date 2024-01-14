#ifndef OutputVisualiser_h
#define OutputVisualiser_h

#include <inttypes.h>
#include <eurorack_graphics.h>
#include "lib/quantizer/model/Scale.h"


template<class G>
class OutputVisualiser : public Component<G> {

public:
    OutputVisualiser(uint16_t width, uint16_t height);
    // virtual void layout();
    virtual void render();

    void setSelectedOutput(uint8_t output);
    void setOutputVoltage(float voltage);

protected:
    uint16_t outputWidth;
    uint16_t outputHeight;

    uint8_t selectedOutput = 0;
    float outputVoltage = 0;

    void renderOutput(uint8_t output);
};

#include "OutputVisualiserImpl.h"
#endif