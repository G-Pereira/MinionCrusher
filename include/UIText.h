#ifndef MINIONCRUSHER_TEXTFIELD_H
#define MINIONCRUSHER_TEXTFIELD_H


#include "UIElement.h"

class UIText : public UIElement {
public:
    UIText(SDL_Rect quad, UIElement *parent);

    ~UIText();
};


#endif //MINIONCRUSHER_TEXTFIELD_H
