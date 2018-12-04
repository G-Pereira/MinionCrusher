#include "UIView.h"

UIView::UIView(int x, int y, int w, int h) : quad{x,y,w,h} {
	renderer = nullptr;
	background = nullptr;

}

UIView::UIView(int w, int h):quad{ 0,0,w,h }
{
}

UIView::UIView(SDL_Rect viewport): quad(viewport)
{
}

UIView::~UIView()
{
	close();
}

void UIView::init()
{
}

void UIView::loadTexture(std::string path)
{	
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	background = newTexture;
}

void UIView::setQuad(SDL_Rect new_quad)
{
	quad = new_quad;
}

void UIView::addChild(UIView * new_child)
{
	children.push_back(new_child);
}

std::vector<UIView*> UIView::getChildren()
{
	return children;
}

void UIView::HandleEvents(SDL_Event & e)
{
	for (UIView* child : children) {
		child->HandleEvents(e);
	}
}

void UIView::close()
{
	//Free loaded images
	SDL_DestroyTexture(background);
	background = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

void UIView::Render()
{
	//Render texture to screen
	SDL_RenderCopy(renderer, background, nullptr, &quad);

	// render children recursively
	for (UIView* child : children) {
		child->Render();
	}
}

SDL_Renderer * UIView::getRenderer() const
{
	return renderer;
}

