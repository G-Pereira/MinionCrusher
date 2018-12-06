#include "TileView.h"

TileView::TileView(SDL_Rect quad, MapSlots type, UIElement *parent) : UIElement(quad, parent), type(type) {
}


TileView::~TileView() {
}

void TileView::postRender() {
    //Render texture to screen
    SDL_RendererFlip flip = (SDL_RendererFlip) 0;
    double angle = 0.0;
    switch (type) {
        case (MapSlots) 0:
            break;
        case (MapSlots) 1:
            flip = (SDL_RendererFlip) 1;
            break;
        case (MapSlots) 2:
            angle = 90.0;
            break;
        case (MapSlots) 3:
            angle = -90.0;
            break;
        case (MapSlots) 4:
            break;
    }
    SDL_RenderCopyEx(renderer, background, nullptr, &quad, angle, nullptr, flip);
}
