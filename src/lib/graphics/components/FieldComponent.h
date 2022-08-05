#ifndef FieldComponent_h
#define FieldComponent_h

#include <inttypes.h>
#include "TextComponent.h"
#include "../Component.h"


template<class G>
class FieldComponent : public Component<G> {

public:
    static const int MAX_LABEL_LENGTH = 32;
    static const int MAX_VALUE_LENGTH = 32;

    FieldComponent(uint16_t width, uint16_t labelWidth, const char* label = "");
    virtual void layout();
    virtual void render();

    void setLabel(const char* text);
    void setValue(const char* value);
    void setValue(int value);

protected:
    char label[MAX_LABEL_LENGTH];
    char value[MAX_VALUE_LENGTH];

    uint16_t labelWidth;

    uint16_t valueLeft;

    void renderLabel();
    void renderValue();
};


template<class G>
FieldComponent<G>::FieldComponent(uint16_t width, uint16_t labelWidth, const char* label) {
    this->setHeight(TextComponent<G>::DEFAULT_HEIGHT);
    this->setLabel(label);
    this->setWidth(width);
    this->labelWidth = labelWidth;
}

template<class G>
void FieldComponent<G>::layout() {
    valueLeft = this->left + labelWidth;
}

template<class G>
void FieldComponent<G>::render() {
    renderLabel();
    renderValue();
}

template<class G>
void FieldComponent<G>::renderLabel() {
    this->graphicsContext->text(&label[0], this->left, this->top);
}

template<class G>
void FieldComponent<G>::renderValue() {
    // this->graphicsContext->fillRectangle(0, 0, 40, 10, 0);
    this->graphicsContext->fillRectangle(this->valueLeft, this->top, 40, 10, 0);
    this->graphicsContext->text(&value[0], this->valueLeft, this->top);
    //this->graphicsContext->text("test", this->valueLeft, this->top);
}

template<class G>
void FieldComponent<G>::setLabel(const char* label) {
    strncpy(this->label, label, MAX_LABEL_LENGTH);
}

template<class G>
void FieldComponent<G>::setValue(const char* value) {
    strncpy(this->value, value, MAX_VALUE_LENGTH);
    renderValue();
}

template<class G>
void FieldComponent<G>::setValue(int value) {
    snprintf_P(this->value, MAX_VALUE_LENGTH, PSTR("%d"), value);
    renderValue();
}


#endif