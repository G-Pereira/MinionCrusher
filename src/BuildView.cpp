#include "BuildView.h"


BuildView::BuildView(SDL_Rect quad, UIView * parent) :UIView(quad, parent)
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

