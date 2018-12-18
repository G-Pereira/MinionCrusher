#ifndef MINIONCRUSHER_TEXTFIELD_H
#define MINIONCRUSHER_TEXTFIELD_H


#include "UIElement.h"

class UIText : public UIElement {
public:
    UIText(SDL_Rect quad, UIElement *parent);
	/**
	 * Load an image from a link and turn it into a texture
	 * @param path path to the file containing a bitmap
	 */
	void loadTexture(std::string path) override;

    ~UIText();
};


#endif //MINIONCRUSHER_TEXTFIELD_H
