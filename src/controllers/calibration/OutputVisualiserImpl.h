#include "OutputVisualiser.h"

template<class G>
OutputVisualiser<G>::OutputVisualiser(uint16_t width, uint16_t height) {
    this->setWidth(width);
    this->setHeight(height);
    this->outputWidth = width / 4;
    this->outputHeight = height / 2;
}

template<class G>
void OutputVisualiser<G>::render() {
    this->graphicsContext->fillRectangle(this->getLeft(), this->getTop(), this->getWidth(), this->getHeight(), TFT_BLACK);
    // uint16_t noteLeft = this->getLeft();
    for(int i = 0; i < 8; i++) {
        renderOutput(i);
        // noteLeft += noteWidth;
        // noteLeft %= tuningWidth;
    }
}

template<class G>
void OutputVisualiser<G>::renderOutput(uint8_t output) {
    uint16_t colour = TFT_NAVY;
    if(output == this->selectedOutput) {
        colour = TFT_MAROON;
    }

    uint8_t outputLeft = this->getLeft() + (output % 4) * outputWidth;
    uint8_t outputTop = this->getTop() + (output / 4) * outputHeight;
    this->graphicsContext->fillRectangle(outputLeft, outputTop, outputWidth-1, outputHeight-1, colour);
}

template<class G>
void OutputVisualiser<G>::setSelectedOutput(uint8_t output) { 
    this->selectedOutput = output; 
    this->render();
}

template<class G>
void OutputVisualiser<G>::setOutputVoltage(float voltage) { 
    this->outputVoltage = voltage;
    this->render();
}
