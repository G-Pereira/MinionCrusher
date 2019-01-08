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
	enum class info_types {
		kills,
		health,
	} type;

    /**
    * \brief Element that spawns a text element in the User interface
    * @param: quad Text field boundaries and position
    * @param: parent Entity that holds this User Interface Element
    */
    UIText(SDL_Rect quad, UIElement *parent, UIText::info_types type);

    ~UIText();
	
	void postRender() override;

	float prev_health = -1;
	int prev_kills = -1;
};


#endif //MINIONCRUSHER_TEXTFIELD_H
