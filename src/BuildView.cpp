#include "BuildView.h"


BuildView::BuildView(SDL_Rect quad, UIElement * parent) :UIElement(quad, parent)
{
}

BuildView::~BuildView()
{
	SDL_DestroyTexture(background);
}

void BuildView::preRender()
{
	//SDL_RenderSetViewport(renderer, &quad);
}

