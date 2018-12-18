#include "InfoView.h"

InfoView::InfoView(SDL_Rect quad, UIElement *parent) : UIElement(quad, parent){

}

InfoView::~InfoView() {
    SDL_DestroyTexture(background);
}
