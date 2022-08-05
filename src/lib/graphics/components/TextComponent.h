#ifndef TextComponent_h
#define TextComponent_h

#include <inttypes.h>
#include "../Component.h"


template<class G>
class TextComponent : public Component<G> {

public:
    static const int MAX_LENGTH = 32;
    static const int DEFAULT_HEIGHT = 10;

    TextComponent() {}
    TextComponent(const char* text);
    virtual void render(G& graphicsContext);

    void setText(const char* text);

protected:
    char text[MAX_LENGTH];

};


template<class G>
TextComponent<G>::TextComponent() { 
    this->setHeight(DEFAULT_HEIGHT);
    setText("");
}

template<class G>
TextComponent<G>::TextComponent(const char* text) {
    this->setHeight(DEFAULT_HEIGHT);
    setText(text);
}

template<class G>
void TextComponent<G>::render(G& graphicsContext) {
    graphicsContext.text(&text[0], this->left, this->top);
}

template<class G>
void TextComponent<G>::setText(const char* text) {
    strncpy(this->text, text, MAX_LENGTH);
}

#endif
