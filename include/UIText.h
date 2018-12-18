/**
 * Author: Gonçalo Pereira
 * Created on: 10-12-18
 * Last Modified: 17-12-18
 */

#ifndef MINIONCRUSHER_TEXTFIELD_H
#define MINIONCRUSHER_TEXTFIELD_H


#include "UIElement.h"

class UIText : public UIElement {
public:

    /**
    * \brief Element that spawns a text element in the User interface
    * @param: quad Text field boundaries and position
    * @param: parent Entity that holds this User Interface Element
    */
    UIText(SDL_Rect quad, UIElement *parent);

    ~UIText();
};


#endif //MINIONCRUSHER_TEXTFIELD_H
