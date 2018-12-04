#include "UIView.h"


UIView::UIView(SDL_Rect viewport, UIView  *parent, SDL_Renderer * rend):quad(viewport), parent(parent), renderer(rend)
{
	//if no renderer is created try to inherit from parent
	if (!renderer) {
		try {
			renderer = parent->renderer;
		}
		catch (std::exception& e) {
			std::cout << "first UIView must be initialized with a renderer\n";
			std::cout << e.what();
		}
	}
	background = nullptr;
}

UIView::UIView(int x, int y, int w, int h, UIView *parent) : UIView(SDL_Rect{ x, y, w,  h }, parent, nullptr)
{
}

UIView::UIView(SDL_Rect viewport, UIView  *parent): UIView(viewport, parent, nullptr)
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

SDL_Rect UIView::getQuad()
{
	return quad;
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

UIView * UIView::getParent()
{
	return parent;
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


void UIView::preRender()
{
}

void UIView::postRender()
{
}

void UIView::Render()
{
	preRender();
	//Render texture to screen
	SDL_RenderCopy(renderer, background, nullptr, &quad);
	// render children recursively
	for (UIView* child : children) {
		SDL_RenderSetViewport(renderer, &quad);
		child->Render();
	}
	postRender();
}

SDL_Renderer * UIView::getRenderer() const
{
	return renderer;
}

