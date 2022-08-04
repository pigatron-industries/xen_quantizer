#ifndef TextComponent_h
#define TextComponent_h

#include <inttypes.h>
#include "../Component.h"

#define MAX_TEXT_LENGTH 32

template<class G>
class TextComponent : public Component<G> {

public:
    TextComponent() {}
    virtual void render(G& graphicsContext);

    void setText(const char* text);

protected:
    char text[MAX_TEXT_LENGTH];

};


template<class G>
void TextComponent<G>::render(G& graphicsContext) {
    graphicsContext.text(&text[0], Component<G>::top, Component<G>::left);
}

template<class G>
void TextComponent<G>::setText(const char* text) {
    strncpy(this->text, text, MAX_TEXT_LENGTH);
}

#endif
