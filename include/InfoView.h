#ifndef MINIONCRUSHER_INFOVIEW_H
#define MINIONCRUSHER_INFOVIEW_H

#include "UIElement.h"
#include "UIText.h"

/**
 * Displays a panel info information about the game
 */
class InfoView : public UIElement {
public:
    /**
     * Information panel
     * @param quad Rectangular shape of the panel
     * @param parent Container in which the panel should be placed
     */
    InfoView(SDL_Rect quad, UIElement *parent);

    ~InfoView();
};


#endif //MINIONCRUSHER_INFOVIEW_H
