#ifndef Container_h
#define Container_h

#include "../Component.h"

template<class G, int N>
class Container : public Component<G> {

public:
    Container() {}
    virtual void render(G& graphicsContext);
    void addComponent(Component<G>* component);

protected:
    Array<Component<G>*, N> components;

};


template<class G, int N>
void Container<G, N>::render(G& graphicsContext) {
    for(Component<G>* component : components) {
        component->render(graphicsContext);
    }
}

template<class G, int N>
void Container<G, N>::addComponent(Component<G>* component) {
    components.add(component);
}

#endif
