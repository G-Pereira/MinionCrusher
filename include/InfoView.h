#ifndef MINIONCRUSHER_INFOVIEW_H
#define MINIONCRUSHER_INFOVIEW_H

#include "UIElement.h"

class InfoView : public UIElement {
        public:
        InfoView(SDL_Rect quad, UIElement *parent);

        ~InfoView();

        void preRender();
};


#endif //MINIONCRUSHER_INFOVIEW_H
