#include "InfoView.h"

InfoView::InfoView(SDL_Rect textfield, UIElement *parent) : UIElement(textfield, parent){

}

InfoView::~InfoView() {
    SDL_DestroyTexture(background);
}

void InfoView::preRender() {

}
