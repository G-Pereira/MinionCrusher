#include "RenderElement.h"


RenderElement::RenderElement(SDL_Rect quad, SDL_Renderer * rend, SDL_Texture * text) : quad(quad), renderer(rend), background(text) {

}
RenderElement::RenderElement(SDL_Rect quad, SDL_Renderer * rend) :RenderElement(quad,rend, nullptr){

}

RenderElement::~RenderElement()
{
	close();
}

void RenderElement::preRender()
{
}

void RenderElement::postRender()
{
}

void RenderElement::loadTexture(std::string path)
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

void RenderElement::setQuad(SDL_Rect new_quad)
{
	quad = new_quad;
}

SDL_Rect RenderElement::getQuad()
{
	return quad;
}


bool RenderElement::hasTexture()
{
	return background ? true : false;
}

void RenderElement::close()
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

void RenderElement::Render()
{
	preRender();
	//Render texture to screen
	SDL_RenderCopy(renderer, background, nullptr, &quad);

	postRender();
}

SDL_Renderer * RenderElement::getRenderer() const
{
	return renderer;
}
