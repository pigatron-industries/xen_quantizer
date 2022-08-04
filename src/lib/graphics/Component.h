#ifndef Component_h
#define Component_h

#include <inttypes.h>
#include "GraphicsContext.h"

template<class G>
class Component {

public:
    Component() {}
    virtual void render(G& graphicsContext);

    int16_t getTop() { return top; }
    int16_t getLeft() { return left; }
    uint16_t getHeight() { return height; }
    uint16_t getWidth() { return width; }
    bool isVisibile() { return visible; }
    bool isFocusable() { return focusable; }

    void setTop(int16_t top) { this->top = top; }
    void setLeft(int16_t left) { this->left = left; }
    void setHeight(uint16_t height) { this->height = height; }
    void setWidth(uint16_t width) { this->width = width; }
    void setVisibility(bool visible) { this->visible = visible; }
    void setFocusable(bool focusable) { this->focusable = focusable; }

protected:
    int16_t top;
    int16_t left;
    uint16_t height;
    uint16_t width;
    bool visible = true;
    bool focusable = false;

};




#endif
