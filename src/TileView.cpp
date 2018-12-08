#include "TileView.h"

TileView::TileView(SDL_Rect quad, MapSlots type, UIElement *parent) : UIElement(quad, parent), type(type) {
}


TileView::~TileView() {
}

template <class T> void swap(T& a, T& b)
{
	T c(std::move(a)); a = std::move(b); b = std::move(c);
}

void TileView::Render(SDL_Renderer * renderer) {

	preRender(renderer);
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
			//swap(quad.x, quad.y);
            break;
        case (MapSlots) 3:
            angle = -90.0;
            break;
        case (MapSlots) 4:
            break;
    }
    SDL_RenderCopyEx(renderer, background, nullptr, &quad, angle, nullptr, flip);

	for (UIElement* child : children) {
		SDL_RenderSetViewport(renderer, &quad);
		child->Render(renderer);
	}
	postRender(renderer);
}
