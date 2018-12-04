#include "TileView.h"

TileView::TileView(SDL_Rect quad, MapSlots type):UIView(quad), type(type)
{
}


TileView::~TileView()
{
}

void TileView::Render()
{
	//Render texture to screen
	//SDL_RenderCopy(renderer, background, nullptr, &quad);

	//cout << fillRect.x << " " << fillRect.y << " " << fillRect.w << " " << fillRect.h << " " << endl;

	if (!background) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &quad);//SDL_RenderCopy(renderer, map_object.texture, nullptr, &fillRect);
	}
	else {
		SDL_RendererFlip flip = (SDL_RendererFlip)0;
		double angle = 0.0;
		switch (type) {
		case (MapSlots)1:
			break;
		case (MapSlots)2:
			angle = 90.0;
			break;
		case (MapSlots)3:
			angle = -90.0;
			break;
		case (MapSlots)4:
			flip = (SDL_RendererFlip)2;
			break;
		}
		SDL_RenderCopyEx(renderer, background, nullptr, &quad, angle, nullptr, flip);
	}
	// render children recursively
	for (UIView* child : children) {
		child->Render();
	}
}
