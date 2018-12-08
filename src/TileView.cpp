#include "TileView.h"

TileView::TileView(SDL_Rect quad, MapSlots type, UIElement *parent) : UIElement(quad, parent), type(type) {
}


TileView::~TileView() {
}

void TileView::Render(SDL_Renderer * renderer) {

	preRender(renderer);
    //Render texture to screen
    SDL_RendererFlip flip = (SDL_RendererFlip) 0;
    double angle = 0.0;
	SDL_Rect quad_rotated = quad;
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
    SDL_RenderCopyEx(renderer, background, nullptr, &quad_rotated, angle, nullptr, flip);

	for (UIElement* child : children) {
		SDL_RenderSetViewport(renderer, &quad_rotated);
		child->Render(renderer);
	}
	postRender(renderer);
}
